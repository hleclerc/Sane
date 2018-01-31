#include "System/BoolVec.h"
#include "Inst/Memcpy.h"
#include "TypeInSane.h"
#include "Variable.h"
#include "Ref.h"
#include "Vm.h"

Variable::Variable( const RcPtr<Ref> &ref, const KuSI64 &offset, const KuSI64 &length, Type *type, Variable::Flags flags ) : ref( ref ), offset( offset ), length( length ), type( type ), flags( flags ) {
}

Variable::Variable( const RcPtr<Ref> &ref, Variable::Flags flags ) : Variable( ref, 0, ref->creator.size(), ref->creator.type(), flags ) {
}

Variable::Variable( const Variable &that ) : ref( that.ref ), offset( that.offset ), length( that.length ), type( that.type ), flags( that.flags  ) {
}

Variable &Variable::operator=( const Variable &that ) {
    ref     = that.ref   ;
    offset  = that.offset;
    length  = that.length;
    type    = that.type  ;
    flags   = that.flags ;
    return *this;
}

CanoVal Variable::cano( bool fully_solved ) const {
    return to_Value().cano_val( fully_solved );
}

bool Variable::error() const {
    return type == 0 || type->error();
}

bool Variable::is_shared() const {
    return ref->is_shared();
}

bool Variable::is_false() const {
    if ( type != vm->type_Bool )
        return vm->scope->find_variable( "Bool" ).apply( true, *this ).is_false();
    return always_false( cano() );
}

bool Variable::is_true() const {
    if ( type != vm->type_Bool )
        return vm->scope->find_variable( "Bool" ).apply( true, *this ).is_true();
    return always_true( cano() );
}

Variable Variable::to_Bool() const {
    if ( type != vm->type_Bool ) {
        TODO;
        //        Variable cond_func = vm->scope->find_variable( "Bool" );
        //        Variable cond_res = cond_func.apply( true, *this );
        //        ASSERT( cond_res.type == vm->type_Bool, "..." );
        //        return cond_res;
    }

    return *this;
}

Value Variable::to_Value() const {
    return type->to_Value( *this );
}

void Variable::write_to_stream( std::ostream &os ) const {
    if ( ref )
        os << *ref;
    else
        os << "NULL";
}

RcString Variable::valid_constraint_for( const Variable &tested_var, TCI &tci ) const {
    return type->checks_type_constraint( *this, tested_var, tci );
}

Variable Variable::find_attribute( const RcString &name, bool ret_err, bool msg_if_err ) const {
    // data from the type
    if ( Variable res = type->find_attribute( name, *this, flags, offset )  )
        return res;

    // look for a 'self' function (external method), from the current scope to the deeper ones
    for( Scope *s = vm->scope; s; s = s->parent_for_vars() ) {
        auto iter = s->variables.find( name );
        if ( iter != s->variables.end() && iter->second.flags & Scope::VariableFlags::SELF_AS_ARG )
            return iter->second.var.type->with_self( iter->second.var, *this );
    }

    //    // try with get_, set_, mod_, typeof_, or 'operator .'
    //    if ( name.begins_with( "get_" ) == false && name.begins_with( "set_" ) == false && name.begins_with( "mod_" ) == false && name.begins_with( "typeof_" ) == false && name != "operator ." ) {
    //        Variable g = find_attribute( "get_" + name, false );
    //        Variable s = find_attribute( "set_" + name, false );
    //        Variable m = find_attribute( "mod_" + name, false );
    //        if ( g || s || m ) {
    //            RefGetsetter *rf = new RefGetsetter( g, s, m, find_attribute( "typeof_" + name, false ) );
    //            return { rf, rf->type };
    //        }

    //        if ( Variable op = find_attribute( "operator .", false ) ) {
    //            TODO;
    //            //            Variable str( scope->vm, scope->vm->type_String );
    //            //            reinterpret_cast<String *>( str.ptr() )->init( name );
    //            //            return op.apply( scope, true, str );
    //        }
    //    }

    if ( msg_if_err )
        vm->add_error( "{} has no attribute {}", *type, name );
    return ret_err ? vm->ref_error : Variable{};
}

void Variable::setup_vtables() {
    // TODO;
}

Variable Variable::constify( bool deep ) {
    flags |= Flags::CONST;

    if ( deep )
        ref->constify();

    return *this;
}

Variable Variable::chbeba( bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names ) {
    return type->chbeba( *this, want_ret, args, names );
}

Variable Variable::select( bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names ) {
    return type->select( *this, want_ret, args, names );
}

Variable Variable::apply( bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, ApplyFlags apply_flags, const Vec<size_t> &spreads ) {
    if ( spreads.size() ) {
        Vec<RcString> v_names( Rese(), names.size() );
        Vec<Variable> v_args( Rese(), args.size() );
        bool has_err = false;
        for( size_t i = 0, n = args.size() - names.size(); i < args.size(); ++i ) {
            if ( spreads.contains( i ) ) {
                if ( args[ i ].error() )
                    has_err = true;
                else
                    args[ i ].type->spread_in( args[ i ], v_args, v_names );
            } else {
                if ( i < n )
                    v_args.insert( v_args.size() - v_names.size(), args[ i ] );
                else {
                    v_names << names[ i - n ];
                    v_args << args[ i ];
                }
            }
        }
        return has_err ? vm->ref_error : apply( want_ret, v_args, v_names, apply_flags );
    }

    return type->apply( *this, want_ret, args, names, {}, apply_flags );
}

String Variable::as_String() const {
    TODO;
    return {};
}

FP64 Variable::as_FP64() const {
    TODO;
    return {};
}

SI32 Variable::as_SI32() const {
    TODO;
    return {};
}

//Value Variable::get() const {
//    Value res = ref->get();
//    return { res.inst, res.nout, type, res.offset + offset };
//}

//bool Variable::get_value( SI32 &val ) const {
//    #define TPT( BA, SI ) if ( type == vm->type_##BA##SI ) { BA##SI v; if ( ! get_bytes( &v, 0, 0, SI ) ) return false; if ( vm->reverse_endianness ) TODO; val = v; return true; }
//    TPT( PI,  8 )
//    TPT( SI,  8 )
//    TPT( PI, 16 )
//    TPT( SI, 16 )
//    TPT( PI, 32 )
//    TPT( SI, 32 )
//    TPT( PI, 64 )
//    TPT( SI, 64 )
//    #undef TPT

//    if ( type == vm->type_PT ) { TODO; return true; }
//    if ( type == vm->type_ST ) { TODO; return true; }

//    return vm->scope->find_variable( "SI32" ).get_value( val );
//}

void Variable::set_bv( const Value &src_val, int cst ) {
    TODO;
    //    if ( flags & Flags::CONST ) {
    //        vm->add_error( "Const variable, should not be modified" );
    //        return;
    //    }
    //    ASSERT( ref, "..." );
    //    ref->set( src_val, cst );
}

void Variable::memcpy( const Variable &src, int cst ) {
    if ( ( flags & Flags::CONST ) && cst >= 0 ) {
        vm->add_error( "Const variable, should not be modified" );
        return;
    }
    make_Memcpy( ref.ptr(), src.ref.ptr(), offset, src.offset, src.length );
}

Variable Variable::sub_part( Type *new_type, SI32 add_off ) const {
    return { ref, offset + add_off, new_type->size( ref, offset + add_off ), new_type, flags };
}

