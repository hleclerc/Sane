#include "TypeProxy.h"
#include "Vm.h"

TypeProxy::TypeProxy( Type *ext_type, Type *int_type ) : ext_type( ext_type ), int_type( int_type ) {
}

Variable TypeProxy::find_attribute( const RcString &name, const Variable &self, Variable::Flags flags, const KuSI64 &off ) const {
    ASSERT( off.is_known() && off.kv() == 0, "..." );
    ASSERT( int( flags ) == 0, "..." );

    Variable internal = to_IntVariable( self );
    if ( Variable res = internal.find_attribute( name ) )
        return res;

    Variable get = internal.find_attribute( "operator get", false );
    if ( ! get )
        return vm->add_error( "Proxy classes must have an 'operator get' method to be read." ), vm->ref_error;
    return get.apply( true ).find_attribute( name );
}

TypeInSane *TypeProxy::type_in_sane() {
    TODO;
    return 0;
}

Class *TypeProxy::orig_class() const {
    return ext_type->orig_class();
}

Value TypeProxy::to_Value( const Variable &var ) {
    Variable internal = to_IntVariable( var );
    Variable get = internal.find_attribute( "operator get", false );
    if ( ! get )
        return vm->add_error( "Proxy classes must have an 'operator get' method to be read." ), vm->ref_error.to_Value();
    return get.apply( true ).to_Value();
}

bool TypeProxy::eq_type( Type *that ) {
    return int_type == that || ext_type == that;
}

void TypeProxy::destroy( const Variable &self, bool use_virtual ) {
    int_type->destroy( to_IntVariable( self ), use_virtual );
}

void TypeProxy::write_to_stream( std::ostream &os ) const {
    os << "TypeProxy[ext=" << *ext_type << ",int=" << *int_type << "]";
}

void TypeProxy::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
    TODO;
}

String TypeProxy::c_name() const {
    TODO;
    return {};
}

Variable TypeProxy::to_IntVariable( const Variable &var ) const {
    return { var.ref, var.offset, var.length, int_type };
}
