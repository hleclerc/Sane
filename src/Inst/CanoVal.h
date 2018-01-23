#pragma once

#include "CanoBinOp.h"
#include "CanoInst.h"

/**
*/
class CanoVal {
public:
    CanoVal( const RcPtr<CanoInst> &inst, Type *type );
    CanoVal( const CanoVal &val );
    CanoVal( SI64 val );
    CanoVal( SI32 val );
    CanoVal( Bool val );
    CanoVal();

    void            write_to_stream ( std::ostream &os ) const;

    RcPtr<CanoInst> inst;
    Type           *type;
};
