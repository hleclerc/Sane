#include "Inst/CanoCst.h"
#include "KuSI64.h"
#include "Class.h"
#include "Type.h"
#include "Vm.h"

TypeInSane::TypeInSane( const RcString &name ) : name( name ) {
    last_attribute  = 0;
    first_attribute = 0;
    _orig_class     = 0;
    _kv_size        = 0;
    _kv_alig        = 1;
    has_new_vtable  = false;
}

void TypeInSane::write_to_stream(std::ostream &os) const {
    os << name;
}

bool TypeInSane::has_vtable_at_the_beginning() const {
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


void TypeInSane::spread_in( const Variable &self, Vec<Variable> &res, Vec<RcString> &names ) {
    PE( name );
    TODO;
}

void TypeInSane::construct( const Variable &self, const Vec<Variable> &args, const Vec<RcString> &names ) {
    Scope new_scope( Scope::ScopeType::BLOCK );
    new_scope.ctor_self = self;

    if ( Variable constructor = self.find_attribute( "construct", false ) )
        constructor.apply( false, args, names );
    else
        vm->add_error( "Found no 'construct' method" );

}

void TypeInSane::add_attribute( const RcString &name, SI32 off, Type *type, Variable::Flags flags ) {
    TypeInSane::Attribute *attr = &attributes.emplace( name, TypeInSane::Attribute{ name, type, off, flags, last_attribute, 0 } ).first->second;
    ( last_attribute ? last_attribute->next : first_attribute ) = attr;
    last_attribute = attr;
}

Variable TypeInSane::find_attribute( const RcString &name, const Variable &self, Variable::Flags flags, const KuSI64 &off ) const {
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

Class *TypeInSane::orig_class() const {
    return _orig_class;
}

void TypeInSane::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
    os << "{";
    for( TypeInSane::Attribute *attr = first_attribute; attr; attr = attr->next ) {
        if ( attr != first_attribute )
            os << ",";
        attr->type->write_cst( os, data + ( offset_mod_8 + attr->off ) / 8, ( offset_mod_8 + attr->off ) % 8 );
    }
    os << "}";
}

SI32 TypeInSane::kv_size() const {
    return _kv_size;
}

SI32 TypeInSane::kv_alig() const {
    return _kv_alig;
}

String Type::c_name() const {
    String res = name;
    for( const CanoVal &var : parameters )
        res += to_string( var );
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
