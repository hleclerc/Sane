#include "CanoCst.h"
#include "../Vm.h"

CanoVal::CanoVal( const RcPtr<CanoInst> &inst, TypeInSane *type ) : inst( inst ), type( type ) {
}

CanoVal::CanoVal( const CanoVal &val ) : inst( val.inst ), type( val.type ) {
}

CanoVal::CanoVal() : type( 0 ) {
}

CanoVal::CanoVal( SI64 val ) : CanoVal( make_cano_val( val ) ) {
}

CanoVal::CanoVal( SI32 val ) : CanoVal( make_cano_val( val ) ) {
}

CanoVal::CanoVal( Bool val ) : CanoVal( make_cano_val( val ) ) {
}

void CanoVal::write_to_stream( std::ostream &os ) const {
    inst->write_to_stream( os, type );
}

CanoVal CanoVal::fully_solved() {
    return { inst->fully_solved(), type };
}


bool always_false( const CanoVal &val ) {
    return val.inst->always_false( val.type );
}

bool always_true( const CanoVal &val ) {
    return val.inst->always_true( val.type );
}
