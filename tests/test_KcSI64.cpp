#include "../src/Inst/CanoSym.h"
#include "../src/Inst/CanoCst.h"
#include "../src/Inst/KcSI64.h"
#include "../src/Vm.h"
#include <gtest/gtest.h>

TEST( KcSI64, cst ) {
    vm = new Vm;

    // known non null value
    KcSI64 a( 17 );
    ASSERT_TRUE ( a.is_known() );
    ASSERT_EQ   ( a.kv(), 17 );
    ASSERT_FALSE( always_false( a ) );
    ASSERT_TRUE ( always_true ( a ) );

    // known null value
    KcSI64 z( 0 );
    ASSERT_TRUE ( z.is_known() );
    ASSERT_EQ   ( z.kv(), 0 );
    ASSERT_TRUE ( always_false( z ) );
    ASSERT_FALSE( always_true ( z ) );

    // conversion to known value
    KcSI64 b( make_cano_val( 19 ) );
    ASSERT_TRUE ( b.is_known() );
    ASSERT_EQ   ( b.kv(), 19 );

    // unknown value
    KcSI64 c( CanoVal( make_CanoSym( "sym" ), vm->type_SI64 ) );
    ASSERT_EQ   ( to_string( c ), "sym" );
    ASSERT_FALSE( c.is_known() );
    ASSERT_FALSE( always_false( c ) );
    ASSERT_FALSE( always_true ( c ) );

    // operation
    ASSERT_EQ   ( to_string( a + b ), "36" );
    ASSERT_EQ   ( to_string( a + c ), "add(17,sym)" );
    ASSERT_EQ   ( to_string( a < c ), "inf(17,sym)" );
}
