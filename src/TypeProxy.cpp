#include "TypeProxy.h"

TypeProxy::TypeProxy( Type *base_type ) : base_type( base_type ) {
}

Variable TypeProxy::find_attribute( const RcString &name, const Variable &self, Variable::Flags flags, const KuSI64 &off ) const {
    P( *self.type, name );
    TODO;
    return {};
}

TypeInSane *TypeProxy::type_in_sane() {
    TODO;
    return 0;
}

Class *TypeProxy::orig_class() const {
    TODO;
    return {};
}

Value TypeProxy::to_Value( const Variable &var ) {
    TODO;
    return {};
}

void TypeProxy::destroy( const Variable &self, bool use_virtual ) {
    base_type->destroy( self, use_virtual );
}

void TypeProxy::write_to_stream( std::ostream &os ) const {
    os << "TypeProxy[" << *base_type << "]";
}

void TypeProxy::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
    TODO;
}

String TypeProxy::c_name() const {
    TODO;
    return {};
}
