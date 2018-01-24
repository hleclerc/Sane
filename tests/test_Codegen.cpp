#include "../src/Codegen/Codegen_C.h"
#include "../src/Inst/WriteFd.h"
#include "../src/Inst/Memcpy.h"
#include "../src/Inst/Cst.h"
#include "../src/Vm.h"
#include <gtest/gtest.h>

TEST( Codegen, init ) {
    vm = new Vm;

    // write 17 in file descriptor 0
    make_WriteFd( make_Cst( 0 ), make_Cst( 17 ) );

    Vec<Inst *> insts;
    vm->ressource_map.visit_ext_changes( [&]( Ref *ref ) { insts << ref->current.inst.ptr(); } );
    Inst::display_graphviz( insts );

    //
    Codegen_C cg;
    cg.gen_code_for( insts );

    P( cg.code() );
}
