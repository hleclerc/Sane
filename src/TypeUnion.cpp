#include "TypeUnion.h"
#include "Scope.h"
#include "Vm.h"

TypeUnion::TypeUnion( SI32 size, SI32 alig ) : TypeInSane( "union" ) {
    _kv_size = size;
    _kv_alig = alig;
}

void TypeUnion::construct( const Variable &self, const Vec<Variable> &args, const Vec<RcString> &names ) {
}

void TypeUnion::destroy( const Variable &self, bool use_virtual ) {
}

bool TypeUnion::has_a_constructor() const {
    return false;
}
