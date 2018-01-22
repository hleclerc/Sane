#include "../src/Inst/Memcpy.h"
#include "../src/Inst/Cst.h"
#include "../src/Vm.h"
#include <gtest/gtest.h>

TEST( Variable, init ) {
    vm = new Vm;

    Variable a = make_Cst( 17 );
    ASSERT_EQ( to_string( a ), "17" );

    // memcpy
    Variable b = make_Cst( 18 );
    memcpy( a.ressource_ref(), b.ressource_ref(), 0, 0, 32 );
    P( a );
}
