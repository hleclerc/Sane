#include "CanoVal.h"

CanoVal::CanoVal( const RcPtr<CanoInst> &inst, Type *type ) : inst( inst ), type( type ) {
}

void CanoVal::write_to_stream( std::ostream &os ) const {
    inst->write_to_stream( os, type );
}
