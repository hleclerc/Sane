#pragma once

#include "../System/TypeConfig.h"
class Variable;
class Type;

/// generic cst
Variable make_Cst( Type *type, int size, void *val = 0, void *kno = 0 );

Variable make_Cst_PI64( PI64 val );
Variable make_Cst_SI64( SI64 val );
Variable make_Cst_PI32( PI32 val );
Variable make_Cst_SI32( SI32 val );
Variable make_Cst_PI16( PI16 val );
Variable make_Cst_SI16( SI16 val );
Variable make_Cst_PI8 ( PI8  val );
Variable make_Cst_SI8 ( SI8  val );
Variable make_Cst_Bool( Bool val );

Variable make_Cst( PI64 val );
Variable make_Cst( SI64 val );
Variable make_Cst( PI32 val );
Variable make_Cst( SI32 val );
Variable make_Cst( PI16 val );
Variable make_Cst( SI16 val );
Variable make_Cst( PI8  val );
Variable make_Cst( SI8  val );
Variable make_Cst( Bool val );
