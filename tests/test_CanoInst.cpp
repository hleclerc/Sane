#include "../src/Inst/Memcpy.h"
#include "../src/Inst/Cst.h"
#include "../src/Vm.h"
#include <gtest/gtest.h>

TEST( CanoInst, cst ) {
    vm = new Vm;

    // creation of a ressource
    Variable a = make_Cst( 17 );
    P( a.cano_repr() );
    // Variable b = make_Cst( 17 );

}
