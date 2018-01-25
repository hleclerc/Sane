#include <boost/filesystem.hpp>
#include "Codegen/Codegen_C.h"
#include <fstream>
#include "Vm.h"

int main( int argc, char **argv ) {
    bool want_graph_only = 0;

    #ifndef INSTALL_DIR
    #define INSTALL_DIR boost::filesystem::path( __FILE__ ).parent_path().parent_path()
    #endif

    // new Vm
    vm = new Vm;
    vm->includes << ( INSTALL_DIR / "lib" ).string();

    // base variables
    if ( want_graph_only == false ) {
        std::string line;
        vm->init_mode = true;
        std::ifstream imports( ( INSTALL_DIR / "lib" / "globals" / "imports" ).string() );
        while ( std::getline( imports, line ) )
            if ( line.empty() == false && line[ 0 ] != '#' )
                vm->import( ( INSTALL_DIR / "lib" / "globals" / line ).string() );
        vm->init_mode = false;
    }

    // user script(s)
    vm->import( argv[ 1 ], {}, want_graph_only );

    // code generation
    Codegen_C cg;
    vm->codegen( cg );

    // compilation
    std::ofstream fout( "res.cpp" );
    fout << cg.code() << std::flush;
    return system( "g++ -o res res.cpp && ./res" );
}
