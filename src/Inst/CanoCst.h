#pragma once

#include "CanoVal.h"

CanoVal make_CanoCst( const void *content, int length );
CanoVal make_CanoCst( SI64 val );
CanoVal make_CanoCst( SI32 val );
CanoVal make_CanoCst( Bool val );
