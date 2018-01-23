#include "../src/Inst/Memcpy.h"
#include "../src/Inst/Rand.h"
#include "../src/Inst/Cst.h"
#include "../src/Vm.h"
#include <gtest/gtest.h>

TEST( CanoInst, cst ) {
    vm = new Vm;

    // comparison with constants
    Variable a = make_Cst( 17 );
    Variable b = make_Cst( 17 );
    Variable c = make_Cst( 18 );
    ASSERT_EQ( to_string( a.cano_repr() ), "17" );
    ASSERT_EQ( to_string( a.cano_repr() == b.cano_repr() ), "1" );
    ASSERT_EQ( to_string( a.cano_repr() == c.cano_repr() ), "0" );

    // rand
    Variable d = make_Rand( vm->type_SI32, 32 );
    ASSERT_EQ( to_string( d.cano_repr() ), "rand" );
    ASSERT_EQ( to_string( a.cano_repr() == d.cano_repr() ), "==(17,rand)" );
}
