#pragma once

#include "CanoVal.h"

RcPtr<CanoInst> make_CanoCst( const void *content, int length );

RcPtr<CanoInst> make_cano_inst( PI64 val );
RcPtr<CanoInst> make_cano_inst( PI32 val );
RcPtr<CanoInst> make_cano_inst( PI16 val );
RcPtr<CanoInst> make_cano_inst( PI8  val );
RcPtr<CanoInst> make_cano_inst( SI64 val );
RcPtr<CanoInst> make_cano_inst( SI32 val );
RcPtr<CanoInst> make_cano_inst( SI16 val );
RcPtr<CanoInst> make_cano_inst( SI8  val );
RcPtr<CanoInst> make_cano_inst( Bool val );

CanoVal make_cano_val( PI64 val );
CanoVal make_cano_val( PI32 val );
CanoVal make_cano_val( PI16 val );
CanoVal make_cano_val( PI8  val );
CanoVal make_cano_val( SI64 val );
CanoVal make_cano_val( SI32 val );
CanoVal make_cano_val( SI16 val );
CanoVal make_cano_val( SI8  val );
CanoVal make_cano_val( Bool val );
