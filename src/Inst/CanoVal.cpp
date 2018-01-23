#include "CanoCst.h"

CanoVal::CanoVal( const RcPtr<CanoInst> &inst, Type *type ) : inst( inst ), type( type ) {
}

CanoVal::CanoVal( const CanoVal &val ) : inst( val.inst ), type( val.type ) {
}

CanoVal::CanoVal() : type( 0 ) {
}

CanoVal::CanoVal( SI64 val ) : CanoVal( make_CanoCst( val ) ) {
}

CanoVal::CanoVal( SI32 val ) : CanoVal( make_CanoCst( val ) ) {
}

CanoVal::CanoVal( Bool val ) : CanoVal( make_CanoCst( val ) ) {
}

void CanoVal::write_to_stream( std::ostream &os ) const {
    inst->write_to_stream( os, type );
}

