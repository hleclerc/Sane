#pragma once

#include "CanoInst.h"
#include "KcSI64.h"

RcPtr<CanoInst> make_CanoMemcpy( const CanoVal &dst, const CanoVal &src, const KcSI64 &off_dst, const KcSI64 &off_src, const KcSI64 &len );

