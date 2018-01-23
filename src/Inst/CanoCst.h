#pragma once

#include "CanoVal.h"

RcPtr<CanoInst> make_CanoCst( const void *content, int length );
RcPtr<CanoInst> make_CanoCst( SI64 val );
RcPtr<CanoInst> make_CanoCst( SI32 val );
RcPtr<CanoInst> make_CanoCst( Bool val );
