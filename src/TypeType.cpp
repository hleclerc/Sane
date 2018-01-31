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
    // types are equal ?
    TypeInSane *nt = self.rcast<TypeInSane>();
    if ( tested_var.type->eq_type( nt ) )
        return {};

    // try recursively inheritance of tested_var
    if ( Class *cl = tested_var.type->orig_class() )
        for( const RcString &inh_name : cl->inheritance_names )
            if ( checks_type_constraint( self, tested_var.find_attribute( inh_name ), tci ).empty() )
                return ++tci.nb_conversions, RcString{};

    //    // try operator "is_also_a"
    //    if ( Variable op = tested_var.find_attribute( "operator is_also_a", false, false ) )
    //        if ( double score = op.apply( true, self ).as_FP64() )
    //             return tci.nb_conversions += score, RcString{};

    // -> fail
    return "not equal nor inherited";
}

