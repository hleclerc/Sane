#include "Variable.h"

RefAncestor::~RefAncestor() {
}

Variable RefAncestor::intercept_find_attribute( const RcString &name, Type *var_type, bool is_const, SI32 var_offset ) const {
    return {};
}

bool RefAncestor::is_shared() const {
    return true;
}
