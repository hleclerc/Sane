#pragma once

#include "CanoVal.h"

RcPtr<CanoInst> make_CanoMemcpy( const CanoVal &dst, const CanoVal &src, const CanoVal &off_dst, const CanoVal &off_src, const CanoVal &len );

