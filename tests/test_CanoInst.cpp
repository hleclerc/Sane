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

    ASSERT_EQ( to_string   ( a.cano_repr()                  )    , "17"                                    );

    ASSERT_EQ( to_string   ( a.cano_repr() == b.cano_repr() )    , "1"                                     );
    ASSERT_EQ( to_string   ( a.cano_repr() == c.cano_repr() )    , "0"                                     );

    ASSERT_EQ( always_false( a.cano_repr() == b.cano_repr() )    , 0                                       );
    ASSERT_EQ( always_true ( a.cano_repr() == b.cano_repr() )    , 1                                       );

    ASSERT_EQ( always_false( a.cano_repr() == c.cano_repr() )    , 1                                       );
    ASSERT_EQ( always_true ( a.cano_repr() == c.cano_repr() )    , 0                                       );
}

TEST( CanoInst, rand ) {
    Variable rnd = make_Rand( vm->type_SI32, 32 );

    ASSERT_EQ( to_string   ( rnd.cano_repr()                    ), "rand(size=32)"                         );
    ASSERT_EQ( to_string   ( rnd.cano_repr() == rnd.cano_repr() ), "1"                                     );

    Variable cst = make_Cst( 17 );
    ASSERT_EQ( to_string   ( cst.cano_repr() == rnd.cano_repr() ), "equ(a=17,b=rand(size=32))"             );

    ASSERT_EQ( always_false( cst.cano_repr() == rnd.cano_repr() ), 0                                       );
    ASSERT_EQ( always_true ( cst.cano_repr() == rnd.cano_repr() ), 0                                       );

    // add
    CanoVal s1 = cst.cano_repr() + rnd.cano_repr();
    CanoVal s2 = cst.cano_repr() + rnd.cano_repr();

    ASSERT_EQ( to_string( s1                    )                , "add(a=17,b=rand(size=32))"             );
    ASSERT_EQ( to_string( s2                    )                , "add(a=17,b=rand(size=32))"             );
    ASSERT_EQ( to_string( s1 == cst.cano_repr() )                , "equ(a=add(a=17,b=rand(size=32)),b=17)" );

    // factorization (same op should give the same result)
    ASSERT_EQ( to_string( s1 == s2              )                , "1"                                     );
}

TEST( CanoInst, memcpy_same_size ) {
    Variable c0 = make_Cst( 17 );
    Variable c1 = make_Cst( 18 );
    ASSERT_EQ( to_string( c0.cano_repr() ), "17" );

    make_Memcpy( c0.ref(), c1.ref(), 0, 0, c1.length );
    ASSERT_EQ( to_string( c1.cano_repr() ), "18" ); // c1 should be unchanged
    ASSERT_EQ( to_string( c0.cano_repr() ), "18" ); // c0 should be changed
}

TEST( CanoInst, memcpy_2_attrs ) {
    Variable cb = make_Cst( vm->type_SI64, 64, 0 );
    Variable c0 = make_Cst( 17 );
    Variable c1 = make_Cst( 18 );

    make_Memcpy( cb.ref(), c0.ref(),  0, 0, 32 );
    make_Memcpy( cb.ref(), c1.ref(), 32, 0, 32 );

    P( cb.cano_repr() );
//    ASSERT_EQ( to_string( cb.cano_repr() ), "17" );

//    make_Memcpy( c0.ref(), c1.ref(), 0, 0, c1.length );
//    ASSERT_EQ( to_string( c1.cano_repr() ), "18" ); // c1 should be unchanged
//    ASSERT_EQ( to_string( c0.cano_repr() ), "18" ); // c0 should be changed
}
