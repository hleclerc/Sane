#include "../System/Cmp.h"
#include "../Type.h"
#include "../Vm.h"
#include "BinOp.h"
#include "Cst.h"

// #include "(test_known.ts).h"

Variable make_Add( const Value &a, const Value &b, int flags ) {
    //    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va + vb ); }, Value{} ) )
    //        return r;

    //    // a + 0, 0 + b
    //    if ( b.is_zero() )
    //        return make_Conv( type_promote( a.type(), b.type() ), a );
    //    if ( a.is_zero() )
    //        return make_Conv( type_promote( a.type(), b.type() ), b );

    //    // ( a + k_0 ) + k_1
    //    if ( const Bin_op<Add> *add_0 = dynamic_cast<const Bin_op<Add> *>( a.inst.ptr() ) ) {
    //        if ( Value res = test_known<Value>( add_0->children[ 1 ], b, [&]( auto c, auto b ) { return make_Add( add_0->children[ 0 ], make_Value( c + b ) ); } ) )
    //            return res;
    //    }

    //    // ( a - k_0 ) + k_1
    //    if ( const Bin_op<Sub> *sub_0 = dynamic_cast<const Bin_op<Sub> *>( a.inst.ptr() ) ) {
    //        if ( Value res = test_known<Value>( sub_0->children[ 1 ], b, [&]( auto c, auto b ) { return make_Add( sub_0->children[ 0 ], make_Value( b - c ) ); } ) )
    //            return res;
    //    }

    return { ( new BinOp<Add>( a, b ) )->new_created_output() };
}

Variable make_Sub( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va - vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<Sub>( a, b ) )->new_created_output() };
}

Variable make_Mul( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va * vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<Mul>( a, b ) )->new_created_output() };
}

Variable make_Mod( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va % vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<Mod>( a, b ) )->new_created_output() };
}

Variable make_Div( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va / vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<Div>( a, b ) )->new_created_output() };
}

Variable make_DivInt( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va / vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<DivInt>( a, b ) )->new_created_output() };
}

Variable make_OrBitwise( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va | vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<OrBitwise>( a, b ) )->new_created_output() };
}

Variable make_XorBitwise( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va ^ vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<XorBitwise>( a, b ) )->new_created_output() };
}

Variable make_AndBitwise( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va & vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<AndBitwise>( a, b ) )->new_created_output() };
}

Variable make_ShiftRight( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va >> vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<ShiftRight>( a, b ) )->new_created_output() };
}

Variable make_ShiftLeft( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( va << vb ); }, Value{} ) )
//        return r;
    return { ( new BinOp<ShiftLeft>( a, b ) )->new_created_output() };
}

Variable make_Inf( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( Cmp<Signed<decltype(va)>::val,Signed<decltype(vb)>::val>::my_inf( va, vb ) ); }, Value{} ) )
//        return r;
    return { ( new BinOp<Inf>( a, b ) )->new_created_output() };
}

Variable make_Sup( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( Cmp<Signed<decltype(va)>::val,Signed<decltype(vb)>::val>::my_sup( va, vb ) ); }, Value{} ) )
//        return r;
    return { ( new BinOp<Sup>( a, b ) )->new_created_output() };
}

Variable make_InfEqu( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( Cmp<Signed<decltype(va)>::val,Signed<decltype(vb)>::val>::my_inf_equ( va, vb ) ); }, Value{} ) )
//        return r;
    return { ( new BinOp<InfEqu>( a, b ) )->new_created_output() };
}

Variable make_SupEqu( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( Cmp<Signed<decltype(va)>::val,Signed<decltype(vb)>::val>::my_sup_equ( va, vb ) ); }, Value{} ) )
//        return r;
    return { ( new BinOp<SupEqu>( a, b ) )->new_created_output() };
}

Variable make_NotEqu( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( Cmp<Signed<decltype(va)>::val,Signed<decltype(vb)>::val>::my_not_equ( va, vb ) ); }, Value{} ) )
//        return r;
    return { ( new BinOp<NotEqu>( a, b ) )->new_created_output() };
}

Variable make_Equ( const Value &a, const Value &b, int flags ) {
//    if ( Value r = test_known( a, b, []( auto va, auto vb ) { return make_Cst( Cmp<Signed<decltype(va)>::val,Signed<decltype(vb)>::val>::my_equ( va, vb ) ); }, Value{} ) )
//        return r;
    return { ( new BinOp<Equ>( a, b ) )->new_created_output() };
}
