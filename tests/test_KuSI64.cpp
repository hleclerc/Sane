#include "../src/Inst/Rand.h"
#include "../src/Inst/Cst.h"
#include "../src/KuSI64.h"
#include "../src/Vm.h"
#include <gtest/gtest.h>

TEST( KuSI64, known_value ) {
    vm = new Vm;

    // known value
    KuSI64 a( 17 );
    ASSERT_TRUE ( a.is_known() );
    ASSERT_EQ   ( a.kv(), 17 );
    ASSERT_FALSE( bool( ! a ) );
    ASSERT_TRUE ( bool( a ) );

    // known value
    KuSI64 z( 0 );
    ASSERT_TRUE ( z.is_known() );
    ASSERT_EQ   ( z.kv(), 0 );
    ASSERT_TRUE ( bool( ! z ) );
    ASSERT_FALSE( bool( z ) );

    // conversion to known value
    KuSI64 b( make_Cst_SI64( 19 ) );
    ASSERT_TRUE ( b.is_known() );
    ASSERT_EQ   ( b.kv(), 19 );

    // unknown value
    KuSI64 c( make_Rand( vm->type_SI64 ) );
    ASSERT_FALSE( c.is_known() );
    // ASSERT_FALSE( z );
}

