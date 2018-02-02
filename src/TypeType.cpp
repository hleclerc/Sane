#include "TypeType.h"
#include "Class.h"
#include "Scope.h"
#include "TCI.h"
#include "Vm.h"

TypeType::TypeType() : TypeInSane( "Type" ) {
}

bool TypeType::destroy_attrs() const {
    return false;
}

void TypeType::destroy( const Variable &self, bool use_virtual ) {
    // types are global and unique
}

Variable TypeType::apply( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) {
    TypeInSane *type = self.rcast<TypeInSane>();
    return vm->make_inst( type, args, names, apply_flags );
}

RcString TypeType::checks_type_constraint( const Variable &self, const Variable &tested_var, TCI &tci ) const {
    TypeInSane *nt = self.rcast<TypeInSane>();
    return tested_var.type->isa( nt, tci );
}

