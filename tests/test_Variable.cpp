#include "../src/Inst/Memcpy.h"
#include "../src/Inst/Cst.h"
#include "../src/Vm.h"
#include <gtest/gtest.h>

TEST( Variable, init ) {
    vm = new Vm;

    // creation of a ressource
    Variable a = make_Cst( 17 );
    ASSERT_EQ( to_string( a ), "17" );

    SI32 val = 0;
    ASSERT_TRUE( a.get_bytes( &val, 0, 0, 32 ) );
    ASSERT_EQ( val, 17 );

    // memcpy
    Variable b = make_Cst( 18 );
    memcpy( a.ref(), b.ref(), 0, 0, 32 );
    ASSERT_EQ( to_string( a ), "Memcpy[0](17,18)" );

    val = 0;
    ASSERT_TRUE( a.get_bytes( &val, 0, 0, 32 ) );
    ASSERT_EQ( val, 18 );

    //
}
