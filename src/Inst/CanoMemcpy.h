#pragma once

#include "CanoVal.h"

RcPtr<CanoInst> make_CanoMemcpy( const RcPtr<CanoInst> &dst, const RcPtr<CanoInst> &src, const CanoVal &off_dst, const CanoVal &off_src, const CanoVal &len );

