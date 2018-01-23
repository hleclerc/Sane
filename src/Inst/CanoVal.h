#pragma once

#include "CanoInst.h"

/**
*/
class CanoVal {
public:
    CanoVal( const RcPtr<CanoInst> &inst = 0, Type *type = 0 );

    void            write_to_stream ( std::ostream &os ) const;

    RcPtr<CanoInst> inst;
    Type           *type;
};
