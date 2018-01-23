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

    ASSERT_EQ( to_string   ( a.cano_repr()                  ), "17"           );

    ASSERT_EQ( to_string   ( a.cano_repr() == b.cano_repr() ), "1"            );
    ASSERT_EQ( to_string   ( a.cano_repr() == c.cano_repr() ), "0"            );

    ASSERT_EQ( always_false( a.cano_repr() == b.cano_repr() ), 0              );
    ASSERT_EQ( always_true ( a.cano_repr() == b.cano_repr() ), 1              );

    ASSERT_EQ( always_false( a.cano_repr() == c.cano_repr() ), 1              );
    ASSERT_EQ( always_true ( a.cano_repr() == c.cano_repr() ), 0              );

    // rand
    Variable d = make_Rand( vm->type_SI32, 32 );

    ASSERT_EQ( to_string   ( d.cano_repr()                  ), "rand"         );

    ASSERT_EQ( to_string   ( a.cano_repr() == d.cano_repr() ), "equ(17,rand)" );
    ASSERT_EQ( to_string   ( d.cano_repr() == d.cano_repr() ), "1"            );

    ASSERT_EQ( always_false( a.cano_repr() == d.cano_repr() ), 0              );
    ASSERT_EQ( always_true ( a.cano_repr() == d.cano_repr() ), 0              );

    // add
    CanoVal s1 = a.cano_repr() + d.cano_repr();
    CanoVal s2 = a.cano_repr() + d.cano_repr();

    ASSERT_EQ( to_string( s1                   ), "add(17,rand)"              );
    ASSERT_EQ( to_string( s2                   ), "add(17,rand)"              );
    ASSERT_EQ( to_string( s1 == a.cano_repr()  ), "equ(add(17,rand),17)"      );
    ASSERT_EQ( to_string( s1 == s2             ), "1"                         );

    // factorization (same op should give the same result)
    ASSERT_EQ( to_string   ( a.cano_repr() == b.cano_repr() ), "1"            );

    // memcpy
    //    make_Memcpy( b.ref(), c.ref(), 0, 0, b.length );
    //    ASSERT_EQ( to_string( b ), "Memcpy[0](17,18)" );
    //    ASSERT_EQ( to_string( b.cano_repr() ), "17" );
}
