#include "CanoCst.h"
#include "../Vm.h"

CanoVal::CanoVal( const RcPtr<CanoInst> &inst, Type *type ) : inst( inst ), type( type ) {
}

CanoVal::CanoVal( const CanoVal &val ) : inst( val.inst ), type( val.type ) {
}

CanoVal::CanoVal() : type( 0 ) {
}

CanoVal::CanoVal( SI64 val ) : CanoVal( make_CanoCst( val ), vm->type_SI64 ) {
}

CanoVal::CanoVal( SI32 val ) : CanoVal( make_CanoCst( val ), vm->type_SI32 ) {
}

CanoVal::CanoVal( Bool val ) : CanoVal( make_CanoCst( val ), vm->type_Bool ) {
}

void CanoVal::write_to_stream( std::ostream &os ) const {
    inst->write_to_stream( os, type );
}


bool always_false( const CanoVal &val ) {
    return val.inst->always_false( val.type );
}

bool always_true( const CanoVal &val ) {
    return val.inst->always_true( val.type );
}
