#include <boost/filesystem.hpp>
#include "System/FileReader.h"
#include "System/Stream.h"

#include "Codegen/Codegen.h"
#include "Ast/AstMaker.h"

#include "AstVisitorVm.h"
#include "Interceptor.h"
#include "Primitives.h"
#include "Import.h"
#include "Ref.h"
#include "Vm.h"

#include "Inst/UninitializedData.h"
#include "Inst/Gatherer.h"
#include "Inst/HostId.h"
#include "Inst/Void.h"
#include "Inst/Cst.h"
#include "Inst/If.h"

#include "TypeCallableWithSelf.h"
#include "TypeSlTrialClass.h"
#include "TypeSlTrialDef.h"
#include "TypeSurdefList.h"
#include "TypeVarargs.h"
#include "TypeInSane.h"
#include "TypeLambda.h"
#include "TypeError.h"
#include "TypeClass.h"
#include "TypeProxy.h"
#include "TypeType.h"
#include "TypeDef.h"
#include "TypeBT.h"

//// nsmake lib_name boost_filesystem

Vm *vm = 0;

Vm::Vm( SI32 sizeof_ptr, bool reverse_endianness ) : main_scope( Scope::ScopeType::ROOT ), sizeof_ptr( sizeof_ptr ), aligof_ptr( sizeof_ptr ), reverse_endianness( reverse_endianness ) {
    error_stream = &std::cerr;
    interceptor  = 0;
    inter_date   = 0;
    init_mode    = true;
    nb_breaks    = 0;
    nb_calls     = 0;

    main_scope.parent = 0;
    scope = &main_scope;

    #define BT( T ) type_##T = 0;
    #include "BaseTypes.h"
    #undef BT

    // arythmetic types
    #define BT( T ) type_##T = reverse_endianness ? (TypeInSane *)new TypeBT<T,true>( #T ) : (TypeInSane *)new TypeBT<T,false>( #T ); type_##T->_kv_size = 8 * sizeof( T );
    BT( Bool )
    BT( SI64 )
    BT( PI64 )
    BT( SI32 )
    BT( PI32 )
    BT( SI16 )
    BT( PI16 )
    BT( SI8  )
    BT( PI8  )
    #undef BT

    type_Bool->_kv_size = 1;

    type_CallableWithSelf = new TypeCallableWithSelf;
    type_SlTrialClass     = new TypeSlTrialClass;
    type_SlTrialDef       = new TypeSlTrialDef;
    type_SurdefList       = new TypeSurdefList;
    type_Varargs          = new TypeVarargs;
    type_Lambda           = new TypeLambda;
    type_Error            = new TypeError;
    type_Class            = new TypeClass;
    type_Type             = new TypeType;
    type_Def              = new TypeDef;

    // type_... not initialized so far
    #define BT( T ) if ( ! type_##T ) type_##T = new TypeInSane( #T );
    #include "BaseTypes.h"
    #undef BT

    // base_types correspondance
    #define BT( T ) base_types[ #T ] = type_##T;
    #include "BaseTypes.h"
    #undef BT

    // correction of type of type_...->content (HostVal)
    //    #define BT( T ) type_##T->content.type = type_Type;
    //    #include "BaseTypes.h"
    //    #undef BT

    for( Primitive_decl *pd = last_Primitive_decl; pd; pd = pd->prev ) {
        TypeInSane *res = pd->func();
        types.push_back_val( res );
        predefs[ RcString( "__primitive_" ) + pd->name ] = make_Void( res );
    }

    for( Primitive_func *pd = last_Primitive_func; pd; pd = pd->prev )
        predeffs[ pd->name ] = pd->func;
}

Variable Vm::import( const String &filename, const String &import_dir, bool display_lexems ) {
    String abso = path( filename, import_dir );
    if ( abso.empty() )
        return add_error( "file '{}' not found", filename ), ref_error;

    // already imported ?
    auto iter = imported.find( abso );
    if ( iter != imported.end() )
        return iter->second;

    // prepare a result variable
    Import *import = new Import;
    Variable res = make_HostId( type_Import, import );

    imported.insert( iter, std::make_pair( abso, res ) );

    import->finished = false;
    import->filename = abso;

    // parse
    FileReader fr( abso );
    AstMaker am( &error_list );
    size_t old_el_size = error_list.size();
    am.parse( fr.data, abso.c_str(), display_lexems );
    AstCrepr ac = am.to_AstCrepr();

    if ( display_lexems ) {
        AstVisitorDisplay ad( std::cout );
        ast_visit( ad, ac.code );
    }

    // if parse error, return an Error var
    if ( old_el_size != error_list.size() ) {
        imported[ abso ] = ref_error;
        return ref_error;
    }

    // exec
    Scope loc( Scope::ScopeType::BLOCK );
    loc.import = import;
    visit( ac, false );

    //
    //    for( Scope::NV *nv = loc.last_var; nv; nv = nv->prev )
    //        if ( nv->flags & Scope::VariableFlags::EXPORT )
    //            import->exports << Import::Export{ String( nv->name ), nv->var };
    //    std::reverse( import->exports.begin(), import->exports.end() );

    import->finished = true;
    return res;
}

String Vm::path( const String &filename, const String &import_dir ) {
    // absolute filename
    boost::filesystem::path path = filename;
    if ( import_dir.empty() || path.is_absolute() ) {
        boost::system::error_code ec;
        boost::filesystem::path cano = boost::filesystem::canonical( path, import_dir, ec );
        return ec ? String{} : cano.string();
    }

    // ./... -> relative to import_dir
    if ( import_dir.size() ) {
        auto starts_with = [&]( const char *s ) {
            return filename.size() >= strlen( s ) && strncmp( filename.data(), s, strlen( s ) ) == 0;
        };
        if ( starts_with( "./" ) || starts_with( "../" ) || starts_with( ".\\" ) || starts_with( "..\\" ) ) {
            boost::system::error_code ec;
            boost::filesystem::path cano = boost::filesystem::canonical( path, import_dir, ec );
            return ec ? String{} : cano.string();
        }
    }

    // -> include lookup
    for( const String &include : includes ) {
        boost::system::error_code ec;
        boost::filesystem::path cano = boost::filesystem::canonical( path, include, ec );
        if ( ! ec )
            return cano.string();
    }

    return {};
}

//void Vm::disp_pos( const String &msg ) const {
//    Error_list::Error error;
//    //    bool disp = true;
//    //    for( const Scope *s = this; s; s = s->parent ) {
//    //        if ( s->pos.cur_names && disp ) {
//    //            error.ac( s->src_name( s->pos.cur_src ), s->pos.cur_off );
//    //            disp = false;
//    //        }

//    //        if ( s->type == Scope::Scope_type::CALL )
//    //            disp = true;
//    //    }
//    std::cerr << msg << ": " << error << std::endl;
//}

ErrorList::Error &Vm::prep_Error( int nb_calls_to_skip, const String &msg ) {
    ErrorList::Error &error = error_list.add( msg );
    bool disp = true;
    for( const Scope *s = scope; s; s = s->parent ) {
        if ( s->pos.cur_names && disp ) {
            if ( nb_calls_to_skip ) {
                --nb_calls_to_skip;
                continue;
            }
            error.ac( s->pos.src_name(), s->pos.cur_off );
            // disp = false;
        }

        if ( s->type == Scope::ScopeType::CALL )
            disp = true;
    }
    return error;
}

void Vm::disp_Error( const Error &error ) const {
    *error_stream << error;
}


Variable Vm::visit( const AstCrepr &ac, bool want_ret ) {
    return visit( ac.names, ac.code, want_ret );
}

TypeInSane *Vm::type_AnonymousRoom( int size, int alig ) {
    auto iter = ano_room_type_map.find( std::make_pair( size, alig ) );
    if ( iter == ano_room_type_map.end() ) {
        TypeInSane *res = new TypeInSane( "AnonymousRoom_" + to_string( size ) + "_" + to_string( alig ) );
        iter = ano_room_type_map.emplace_hint( iter, std::make_pair( size, alig ), res );
        types << res;
    }
    return iter->second;
}

Type *Vm::get_proxy_type( Type *ext_type, Type *int_type ) {
    auto iter = map_proxy_type.find( std::make_pair( ext_type, int_type ) );
    if ( iter == map_proxy_type.end() )
        iter = map_proxy_type.emplace_hint( iter, std::make_pair( ext_type, int_type ), new TypeProxy( ext_type, int_type ) );
    return iter->second;
}

Variable Vm::new_Type( Type *type ) {
    TODO;
    return {};
}

Variable Vm::make_inst( TypeInSane *type, const Vec<Variable> &ctor_args, const Vec<RcString> &ctor_names, ApplyFlags apply_flags ) {
    // check that all abstract surdefs are defined
    if ( ! ( apply_flags & ApplyFlags::DONT_CALL_CTOR ) && type->abstract_methods.size() ) {
        std::string am;
        for( const FunctionSignature &fs : type->abstract_methods )
            am += std::string( am.empty() ? "" : ", " ) + fs.name;
        add_error( "{} contains abstract methods ({}) and should not be instantiated", *type, am );
    }

    // make an instance
    if ( type->kv_size() < 0 )
        TODO;
    if ( type->kv_alig() < 0 )
        TODO;
    Variable res = make_UninitializedData( type, type->kv_size(), type->kv_alig() );

    // call constructor if necessary
    if ( apply_flags & ApplyFlags::DONT_CALL_CTOR )
        res.ref->flags |= Ref::Flags::NOT_CONSTRUCTED;
    else
        type->construct( res, ctor_args, ctor_names );

    return res;
}

bool Vm::little_endian() const {
    return ( __BYTE_ORDER ==__LITTLE_ENDIAN ) ^ reverse_endianness;
}

TypeInSane *Vm::type_ptr_for( const RcString &name, const Vec<Variable> &args ) {
    if ( init_mode ) {
        auto iter = base_types.find( name );
        if ( iter != base_types.end() )
            return iter->second;
    }
    TypeInSane *res = new TypeInSane( name );
    types.push_back_val( res );
    for( const Variable &arg : args )
        res->parameters << arg.cano( true );
    return res;
}

void Vm::display_graph( const char *fn ) {
    Vec<Inst *> to_disp;
    ressource_map.visit_ext_changes( [&]( Ref *ref ) {
        to_disp << ref->current.inst.ptr();
    } );

    Inst::display_graphviz( to_disp, [](std::ostream &, const Inst *) {}, fn );
}

void Vm::codegen( Codegen &cg ) {
    Vec<Inst *> targets;
    ressource_map.visit_ext_changes( [&]( Ref *ref ) {
        targets << ref->current.inst.ptr();
    } );

    cg.gen_code_for( targets );
}

void Vm::if_else( const Variable &cond_var, const std::function<void ()> &ok, const std::function<void ()> &ko ) {
    add_error("pouet");
    TODO;
//    // conversion to bool
//    if ( cond_var.type != type_Bool ) {
//        Variable n_cond_var = scope->find_variable( "Bool" ).apply( true, cond_var );
//        if ( n_cond_var.type != type_Bool ) {
//            if ( ! n_cond_var.error() )
//                add_error( "conv to Bool should give a Bool" );
//            return;
//        }
//        return if_else( n_cond_var, ok, ko );
//    }

//    // is value of cond is known
//    if ( cond_var.is_true() )
//        return ok();
//    if ( cond_var.is_false() )
//        return ko();

//    // else, execute ok and ko codes in sandboxes
//    Interceptor inter_ok;
//    inter_ok.run( ok );

//    Interceptor inter_ko;
//    inter_ko.run( ko );

//    //
//    RcPtr<IfInp> inp_ok = new IfInp;
//    RcPtr<IfInp> inp_ko = new IfInp;

//    // save new values in out instructions
//    Vec<Value> out_ok, out_ko;
//    for( auto &p : inter_ok.mod_refs ) {
//        out_ok << p.second.n;
//        auto iter_out_ko = inter_ko.mod_refs.find( p.first );
//        if ( iter_out_ko == inter_ko.mod_refs.end() )
//            out_ko << p.second.o;
//        else
//            out_ko << iter_out_ko->second.n;
//    }

//    for( auto &p : inter_ko.mod_refs ) {
//        if ( inter_ok.mod_refs.count( p.first ) )
//            continue;
//        int num = out_ok.size();
//        out_ok << Value( { inp_ok, num }, p.second.o.type );
//        out_ko << p.second.n;
//    }

//    // new If inst
//    RcPtr<If> inst_if = new If( cond_var.get(), inp_ok, new IfOut( out_ok ), inp_ko, new IfOut( out_ko ) );

//    // variables modified by the the if instruction
//    int num = 0;
//    for( auto &p : inter_ok.mod_refs )
//        p.first->set( Value{ { inst_if, num++ }, p.second.o.type }, -1 );
//    for( auto &p : inter_ko.mod_refs )
//        if ( inter_ok.mod_refs.count( p.first ) == 0 )
//            p.first->set( Value{ { inst_if, num++ }, p.second.o.type }, -1 );

//    // update RefLeaf::breaks
//    //    if ( breaks_ok.size() || breaks_ko.size() )
//    //        ++Ref::inter_date;
//    //    for( const Ref::Break &br : breaks_ok )
//    //        Ref::breaks << Ref::Break{ br.nb_l, Ref::inter_date, make_And_log( br.cond, cond_val ) };
//    //    for( const Ref::Break &br : breaks_ko )
//    //        Ref::breaks << Ref::Break{ br.nb_l, Ref::inter_date, make_And_log( br.cond, make_Not_log( cond_val ) ) };
}

Variable Vm::visit( const RcString &names, const RcString &code, bool want_ret ) {
    auto _ = raii_save( scope->pos );

    AstVisitorVm av( names, want_ret );
    ast_visit( av, code );
    return av.ret;
}

Variable Vm::visit( const RcString &names, const Vec<RcString> &code, bool want_ret ) {
    if ( code.size() ) {
        for( size_t i = 0; i < code.size() - 1; ++i )
            visit( names, code[ i ], false );
        return visit( names, code.back(), want_ret );
    }
    ASSERT( want_ret == false, "..." );
    return {};
}

Variable Vm::visit( const Vec<AstCrepr> &creps, bool want_ret ) {
    if ( creps.size() ) {
        for( size_t i = 0; i < creps.size() - 1; ++i )
            visit( creps[ i ], false );
        return visit( creps.back(), want_ret );
    }
    ASSERT( want_ret == false, "..." );
    return {};
}
