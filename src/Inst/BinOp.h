#pragma once

#include "../Codegen/Codegen.h"
#include "Clonable.h"
#include "../Type.h"
#include "../Vm.h"

/**
*/
template<class Op>
class BinOp : public Clonable<BinOp<Op>> {
public:
    BinOp( const Value &a, const Value &b ){
        this->init_attr( this->a, a );
        this->init_attr( this->b, b );
    }
    BinOp( AttrClone, const BinOp *orig ) {
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << Op::name();
    }

    virtual Type *created_out_type( int nout ) const override {
        return Op::type( a.type, b.type );
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        ss( Op::prio ) << cg.repr( this->to_Value( a ), Op::prio ) << " " << Op::str() << " " << cg.repr( this->to_Value( b ), Op::prio );
    }

    IiValue a;
    IiValue b;
};

#define DECL_BIN_OP( NAME, PRIO, STR, TYPE ) \
    Variable make_##NAME( const Value &a, const Value &b, int flags = 0 ); \
    struct NAME { \
        enum { prio = PRIO }; \
        static const char *str () { return STR; } \
        static const char *name() { return #NAME; } \
        static Variable    make( const Value &a, const Value &b ) { return make_##NAME( a, b ); } \
        static Type       *type( Type *a, Type *b ) { return TYPE; } \
    }

DECL_BIN_OP( Add        , PRIO_Addition             , "+" , type_promote_gen( a, b ) );
DECL_BIN_OP( Sub        , PRIO_Subtraction          , "-" , type_promote_gen( a, b ) );
DECL_BIN_OP( Mul        , PRIO_Multiplication       , "*" , type_promote_gen( a, b ) );
DECL_BIN_OP( Div        , PRIO_Division             , "/" , type_promote_gen( a, b ) );
DECL_BIN_OP( Div_int    , PRIO_Division             , "/" , type_promote_gen( a, b ) );
DECL_BIN_OP( Mod        , PRIO_Modulus              , "%" , type_promote_gen( a, b ) );
DECL_BIN_OP( Inf        , PRIO_Less_than            , "<" , vm->type_Bool            );
DECL_BIN_OP( Sup        , PRIO_Less_than            , ">" , vm->type_Bool            );
DECL_BIN_OP( Inf_equ    , PRIO_Less_than_or_equal_to, "<=", vm->type_Bool            );
DECL_BIN_OP( Sup_equ    , PRIO_Less_than_or_equal_to, ">=", vm->type_Bool            );
DECL_BIN_OP( Equ        , PRIO_Equality             , "==", vm->type_Bool            );
DECL_BIN_OP( Not_equ    , PRIO_Inequality           , "!=", vm->type_Bool            );
DECL_BIN_OP( Or_logical , PRIO_Logical_OR           , "||", vm->type_Bool            );
DECL_BIN_OP( And_logical, PRIO_Logical_AND          , "&&", vm->type_Bool            );
DECL_BIN_OP( Or_bitwise , PRIO_Bitwise_inclusive_OR , "|" , type_promote_gen( a, b ) );
DECL_BIN_OP( Xor_bitwise, PRIO_Bitwise_exclusive_OR , "^" , type_promote_gen( a, b ) );
DECL_BIN_OP( And_bitwise, PRIO_Bitwise_AND          , "&" , type_promote_gen( a, b ) );
DECL_BIN_OP( Shift_right, PRIO_Right_shift          , "<<", a                        );
DECL_BIN_OP( Shift_left , PRIO_Left_shift           , ">>", a                        );
