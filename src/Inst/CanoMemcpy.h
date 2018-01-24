#pragma once

#include "CanoInst.h"
#include "KcSI64.h"

RcPtr<CanoInst> make_CanoMemcpy( const CanoVal &dst, const RcPtr<CanoInst> &src, const KcSI64 &off );

