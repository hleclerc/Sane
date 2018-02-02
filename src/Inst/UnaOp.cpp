#include "../System/Cmp.h"
#include "../Type.h"
#include "../Vm.h"
#include "UnaOp.h"
#include "Cst.h"

//#include "(test_known.ts).h"

namespace {

//template<class T> T not_bitwise( T va ) { return ~ va; }
//bool not_bitwise( bool va ) { return ! va; }

}

Variable make_Neg( const Value &a ) {
    //    if ( Value r = test_known( a, []( auto va ) { return make_Cst( - va ); }, Value{} ) )
    //        return r;
    return { ( new UnaOp<Neg>( a ) )->new_created_output() };
}

Variable make_NotLogical( const Value &a ) {
    //    if ( Value r = test_known( a, []( auto va ) { return make_Cst( ! va ); }, Value{} ) )
    //        return r;
    return { ( new UnaOp<NotLogical>( a ) )->new_created_output() };
}

Variable make_NotBitwise( const Value &a ) {
    //    if ( Value r = test_known( a, []( auto va ) { return make_Cst( not_bitwise( va ) ); }, Value{} ) )
    //        return r;
    return { ( new UnaOp<NotBitwise>( a ) )->new_created_output() };
}
