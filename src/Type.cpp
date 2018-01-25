#include "KuSI64.h"
#include "Class.h"
#include "Type.h"
#include "Vm.h"

Type::Type( const LString &name ) : content( vm ? vm->type_Type : 0 ) {
    content.data.name = name;
}

void Type::write_to_stream(std::ostream &os) const {
    os << content.data.name;
}

bool Type::has_vtable_at_the_beginning() const {
    if ( content.data.has_new_vtable )
        return true;
    if ( Class *cl = orig_class() ) {
        for( const RcString &name : cl->inheritance_names ) {
            Type *inh_type = content.data.attributes.find( name )->second.type;
            if ( inh_type->has_vtable_at_the_beginning() )
                return true;
            if ( inh_type->content.data.kv_size )
                break;
        }
    }
    return false;
}

RcString Type::checks_type_constraint( const Variable &self, const Variable &tested_var, TCI &tci ) const {
    vm->add_error( "checks_type_constraint for type {}", *this );
    PE( content.data.name );
    TODO;
    return "not equal nor inherited";
}

unsigned Type::get_nb_conversions( const Variable &self ) const {
    PE( content.data.name );
    TODO;
    return 0;
}

bool Type::has_a_constructor() const {
    return true;
}


//void Type::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
//    // os << content << "(" << "..." << ")";
//    os << "{";
//    for( TypeContent::Attribute *attr = content.data.first_attribute; attr; attr = attr->next ) {
//        if ( attr != content.data.first_attribute )
//            os << ",";
//        attr->type->write_cst( os, data + ( offset_mod_8 + attr->off ) / 8, ( offset_mod_8 + attr->off ) % 8 );
//    }
//    os << "}";
//}

void Type::destroy( const Variable &self, bool use_virtual ) {
}


void Type::spread_in( const Variable &self, Vec<Variable> &res, Vec<RcString> &names ) {
    PE( content.data.name );
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
    PE( content.data.name );
    TODO;
    return 0;
}

Type::CondVal Type::get_condition( const Variable &self ) const {
    PE( content.data.name );
    TODO;
    return Type::CondVal{ 0, {} };
}

void Type::get_fail_info( const Variable &self, size_t &offset, RcString &source, RcString &msg ) const {
    PE( content.data.name );
    TODO;
}

bool Type::destroy_attrs() const {
    return true;
}

void Type::add_attribute( const RcString &name, SI32 off, Type *type, Variable::Flags flags ) {
    TypeContent::Attribute *attr = &content.data.attributes.emplace( name, TypeContent::Attribute{ name, type, off, flags, content.data.last_attribute, 0 } ).first->second;
    ( content.data.last_attribute ? content.data.last_attribute->next : content.data.first_attribute ) = attr;
    content.data.last_attribute = attr;
}

Variable Type::make_sl_trial( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) const {
    PE( content.data.name );
    TODO;
    return {};
}

Variable Type::use_sl_trial( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags, const Variable &trial ) const {
    PE( content.data.name );
    TODO;
    return {};
}

Variable Type::apply( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) {
    PE( content.data.name );
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

Variable Type::find_attribute( const RcString &name, const Variable &self, Variable::Flags flags, SI32 off ) const {
    // instance attributes
    auto iter_attr = content.data.attributes.find( name );
    if ( iter_attr != content.data.attributes.end() ) {
        TODO;
        return {}; // { self.ref, iter_attr->second.type, off + iter_attr->second.off, flags };
    }

    // methods
    auto iter_sattr = content.data.methods.find( name );
    if ( iter_sattr != content.data.methods.end() )
        return self ? iter_sattr->second->type->with_self( *iter_sattr->second, self ) : *iter_sattr->second;

    // static attributes
    iter_sattr = content.data.static_attributes.find( name );
    if ( iter_sattr != content.data.static_attributes.end() )
        return *iter_sattr->second;

    // template arguments
    if ( Class *cl = orig_class() )
        for( size_t i = 0; i < cl->arg_names.size(); ++i )
            if ( cl->arg_names[ i ] == name )
                return *content.data.parameters[ i ];

    // try in inheritance (if not looking for a destructor)
    if ( Class *cl = orig_class() ) {
        if ( name != "destroy" ) {
            for( const RcString &inh_name : cl->inheritance_names ) {
                auto iter_attr = content.data.attributes.find( inh_name );
                ASSERT( iter_attr != content.data.attributes.end(), "" );
                if ( Variable res = iter_attr->second.type->find_attribute( name, self, flags | iter_attr->second.flags, off + iter_attr->second.off ) )
                    return res;
            }
        }
    }

    return {};
}

Variable Type::with_self( Variable &orig, const Variable &new_self ) const {
    PE( content.data.name );
    TODO;
    return {};
}

Class *Type::orig_class() const {
    return content.data.orig_class;
}

void Type::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
    os << "{";
    for( TypeContent::Attribute *attr = content.data.first_attribute; attr; attr = attr->next ) {
        if ( attr != content.data.first_attribute )
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
    return content.data.kv_size;
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

KuSI64 Type::size( const Variable &var, const KuSI64 &offset ) const {
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
    String res = content.data.name;
    for( Variable *var : content.data.parameters ) {
        res += to_string( *var );
    }
    return res;
}

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
