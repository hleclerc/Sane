#include "Inst/CanoCst.h"
#include "KuSI64.h"
#include "Class.h"
#include "Type.h"
#include "Vm.h"

Type::Type( const LString &name ) : name( name ) {
    last_attribute     = 0;
    first_attribute    = 0;
    _orig_class        = 0;
    _kv_size           = 0;
    _kv_alig           = 1;
    type_promote_score = -1;
    has_new_vtable     = false;
}

void Type::write_to_stream(std::ostream &os) const {
    os << name;
}

bool Type::has_vtable_at_the_beginning() const {
    if ( has_new_vtable )
        return true;
    if ( Class *cl = orig_class() ) {
        for( const RcString &name : cl->inheritance_names ) {
            Type *inh_type = attributes.find( name )->second.type;
            if ( inh_type->has_vtable_at_the_beginning() )
                return true;
            if ( inh_type->kv_size() )
                break;
        }
    }
    return false;
}

RcString Type::checks_type_constraint( const Variable &self, const Variable &tested_var, TCI &tci ) const {
    vm->add_error( "checks_type_constraint for type {}", *this );
    PE( name );
    TODO;
    return "not equal nor inherited";
}

unsigned Type::get_nb_conversions( const Variable &self ) const {
    PE( name );
    TODO;
    return 0;
}

bool Type::has_a_constructor() const {
    return true;
}


//void Type::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
//    // os << content << "(" << "..." << ")";
//    os << "{";
//    for( TypeContent::Attribute *attr = first_attribute; attr; attr = attr->next ) {
//        if ( attr != first_attribute )
//            os << ",";
//        attr->type->write_cst( os, data + ( offset_mod_8 + attr->off ) / 8, ( offset_mod_8 + attr->off ) % 8 );
//    }
//    os << "}";
//}

void Type::destroy( const Variable &self, bool use_virtual ) {
}


void Type::spread_in( const Variable &self, Vec<Variable> &res, Vec<RcString> &names ) {
    PE( name );
    TODO;
}

void Type::construct( const Variable &self, const Vec<Variable> &args, const Vec<RcString> &names ) {
    Scope new_scope( Scope::ScopeType::BLOCK );
    new_scope.ctor_self = self;

    if ( Variable constructor = self.find_attribute( "construct", false ) )
        constructor.apply( false, args, names );
    else
        vm->add_error( "Found no 'construct' method" );

}

double Type::get_pertinence( const Variable &self ) const {
    PE( name );
    TODO;
    return 0;
}

Type::CondVal Type::get_condition( const Variable &self ) const {
    PE( name );
    TODO;
    return Type::CondVal{ 0, {} };
}

void Type::get_fail_info( const Variable &self, size_t &offset, RcString &source, RcString &msg ) const {
    PE( name );
    TODO;
}

bool Type::destroy_attrs() const {
    return true;
}

void Type::add_attribute( const RcString &name, SI32 off, Type *type, Variable::Flags flags ) {
    Type::Attribute *attr = &attributes.emplace( name, Type::Attribute{ name, type, off, flags, last_attribute, 0 } ).first->second;
    ( last_attribute ? last_attribute->next : first_attribute ) = attr;
    last_attribute = attr;
}

Variable Type::make_sl_trial( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) const {
    PE( name );
    TODO;
    return {};
}

Variable Type::use_sl_trial( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags, const Variable &trial ) const {
    PE( name );
    TODO;
    return {};
}

Variable Type::apply( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) {
    PE( name );
    TODO; return {};
}

Variable Type::chbeba( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names ) {
    Variable op = self.find_attribute( "operator {}", false );
    if ( ! op )
        return vm->add_error( "class {} has no 'operator {}'", *self.type, "{}" );
    return op.apply( want_ret, args, names );
}

Variable Type::select( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names ) {
    Variable op = self.find_attribute( "operator []", false );
    if ( ! op )
        return vm->add_error( "class {} has no 'operator []'", *self.type );
    return op.apply( want_ret, args, names );
}

Variable Type::find_attribute( const RcString &name, const Variable &self, Variable::Flags flags, const KuSI64 &off ) const {
    // instance attributes
    auto iter_attr = attributes.find( name );
    if ( iter_attr != attributes.end() ) {
        return { self.ref, off + iter_attr->second.off, iter_attr->second.type->size( self.ref, off + iter_attr->second.off ), iter_attr->second.type, flags };
    }

    // methods
    auto iter_sattr = methods.find( name );
    if ( iter_sattr != methods.end() )
        return self ? iter_sattr->second->type->with_self( *iter_sattr->second, self ) : *iter_sattr->second;

    // static attributes
    iter_sattr = static_attributes.find( name );
    if ( iter_sattr != static_attributes.end() )
        return *iter_sattr->second;

    // template arguments
    if ( Class *cl = orig_class() )
        for( size_t i = 0; i < cl->arg_names.size(); ++i )
            if ( cl->arg_names[ i ] == name )
                TODO; // return *parameters[ i ];

    // try in inheritance (if not looking for a destructor)
    if ( Class *cl = orig_class() ) {
        if ( name != "destroy" ) {
            for( const RcString &inh_name : cl->inheritance_names ) {
                auto iter_attr = attributes.find( inh_name );
                ASSERT( iter_attr != attributes.end(), "" );
                if ( Variable res = iter_attr->second.type->find_attribute( name, self, flags | iter_attr->second.flags, off + iter_attr->second.off ) )
                    return res;
            }
        }
    }

    return {};
}

Variable Type::with_self( Variable &orig, const Variable &new_self ) const {
    PE( name );
    TODO;
    return {};
}

Class *Type::orig_class() const {
    return _orig_class;
}

void Type::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
    os << "{";
    for( Type::Attribute *attr = first_attribute; attr; attr = attr->next ) {
        if ( attr != first_attribute )
            os << ",";
        attr->type->write_cst( os, data + ( offset_mod_8 + attr->off ) / 8, ( offset_mod_8 + attr->off ) % 8 );
    }
    os << "}";
}

bool Type::has_floating_point() const {
    return false;
}

int Type::is_signed() const {
    return -1;
}

SI32 Type::kv_size() const {
    return _kv_size;
}

SI32 Type::kv_alig() const {
    return _kv_alig;
}

int Type::mantissa_len() const {
    return -1;
}

int Type::exponent_len() const {
    return -1;
}

bool Type::error() const {
    return false;
}

KuSI64 Type::size( const RcPtr<Ref> &ref, const KuSI64 &offset ) const {
    return kv_size();
}

bool Type::is_a_TypeBT() const {
    return false;
}

RcPtr<CanoInst> Type::convert_cano_cst( const void *content, Type *target ) {
    return 0;
}

SI64 Type::convert_cst_to_SI64( const void *content ) const {
    ERROR( "..." );
    return 0;
}

String Type::c_name() const {
    String res = name;
    for( const CanoVal &var : parameters )
        res += to_string( var );
    return res;
}

#define BO( NAME ) CanoVal Type::make_Cano##NAME( const void *a, const void *b ) { TODO; return {}; }
#include "decl_bin_op.h"
#undef BO

Type *type_promote_gen( Type *a, Type *b ) {
    if ( a == vm->type_AT )
        return a;

    if ( a->is_a_TypeBT() && b->is_a_TypeBT() ) {
        if ( a->has_floating_point() || b->has_floating_point() ) {
            TODO;
        }

        int m = std::max( a->mantissa_len(), b->mantissa_len() );
        if ( a->is_signed() || b->is_signed() ) {
            if ( m <=  8 ) return vm->type_SI8 ;
            if ( m <= 16 ) return vm->type_SI16;
            if ( m <= 32 ) return vm->type_SI32;
            return                vm->type_SI64;
        }

        if ( m <=  8 ) return vm->type_PI8 ;
        if ( m <= 16 ) return vm->type_PI16;
        if ( m <= 32 ) return vm->type_PI32;
        return                vm->type_PI64;
    }

    TODO;
    return 0;
}
