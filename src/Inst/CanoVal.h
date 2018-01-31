#pragma once

#include "CanoBinOp.h"
#include "CanoInst.h"
#include "KcSI64.h"

/**
*/
class CanoVal {
public:
    CanoVal( const RcPtr<CanoInst> &inst, TypeInSane *type );
    CanoVal( const CanoVal &val );
    CanoVal( SI64 val );
    CanoVal( SI32 val );
    CanoVal( Bool val );
    CanoVal();

    void            write_to_stream ( std::ostream &os ) const;
    CanoVal         fully_solved    ();
    KcSI64          length          () const { return inst->length(); }

    RcPtr<CanoInst> inst;
    TypeInSane     *type;
};

bool always_false( const CanoVal &val );
bool always_true ( const CanoVal &val );
