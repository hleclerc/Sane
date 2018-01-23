#include "../src/Inst/WriteFd.h"
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

TEST( Variable, fd ) {
    vm = new Vm;

    // write 17 in file descriptor 0
    make_WriteFd( make_Cst( 0 ), make_Cst( 17 ) );

    Vec<Inst *> insts;
    vm->ressource_map.visit_ext_changes( [&](Ref *ref) { insts << ref->current.inst.ptr(); } );
    Inst::display_graphviz( insts );

    // ASSERT_EQ( inst );
}
