#pragma once

#include "../Codegen/Codegen.h"
#include "../TypeInSane.h"
#include "../Vm.h"
#include "CanoBinOp.h"
#include "Clonable.h"

/**
*/
template<class Op>
class BinOp : public Clonable<BinOp<Op>> {
public:
    BinOp( const Value &a, const Value &b, const Op &op = {} ) : op( op ) {
        this->init_attr( this->a, a );
        this->init_attr( this->b, b );
    }

    BinOp( AttrClone, const BinOp *orig ) : op( orig->op ), a( orig->a ), b( orig->b ) {
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << op;
    }

    virtual Type *created_out_type( int nout ) const override {
        return Op::type( a.type, b.type );
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        ss( Op::prio ) << cg.repr( this->to_Value( a ), Op::prio ) << " " << Op::str() << " " << cg.repr( this->to_Value( b ), Op::prio );
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const {
        return op.make_cano_inst( this->cano_val( a ), this->cano_val( b ) );
    }

    Op      op;
    IiValue a;
    IiValue b;
};

#define DECL_BIN_OP( NAME, PRIO, STR, TYPE ) \
    Variable make_##NAME( const Value &a, const Value &b, int flags = 0 ); \
    struct NAME { \
        enum { prio = PRIO }; \
        void write_to_stream( std::ostream &os ) const { os << name(); } \
        RcPtr<CanoInst> make_cano_inst( const CanoVal &a, const CanoVal &b ) const { return make_Cano##NAME( a, b ).inst; } \
        static const char *str () { return STR; } \
        static const char *name() { return #NAME; } \
        static Variable    make( const Value &a, const Value &b ) { return make_##NAME( a, b ); } \
        static Type       *type( Type *a, Type *b ) { return TYPE; } \
    }

DECL_BIN_OP( Add       , PRIO_Addition             , "+"  , type_promote_gen( a, b ) );
DECL_BIN_OP( Sub       , PRIO_Subtraction          , "-"  , type_promote_gen( a, b ) );
DECL_BIN_OP( Mul       , PRIO_Multiplication       , "*"  , type_promote_gen( a, b ) );
DECL_BIN_OP( Div       , PRIO_Division             , "/"  , type_promote_gen( a, b ) );
DECL_BIN_OP( DivInt   , PRIO_Division             , "/"  , type_promote_gen( a, b ) );
DECL_BIN_OP( Mod       , PRIO_Modulus              , "%"  , type_promote_gen( a, b ) );
DECL_BIN_OP( Inf       , PRIO_Less_than            , "<"  , vm->type_Bool            );
DECL_BIN_OP( Sup       , PRIO_Less_than            , ">"  , vm->type_Bool            );
DECL_BIN_OP( InfEqu    , PRIO_Less_than_or_equal_to, "<=" , vm->type_Bool            );
DECL_BIN_OP( SupEqu    , PRIO_Less_than_or_equal_to, ">=" , vm->type_Bool            );
DECL_BIN_OP( Equ       , PRIO_Equality             , "==" , vm->type_Bool            );
DECL_BIN_OP( NotEqu    , PRIO_Inequality           , "!=" , vm->type_Bool            );
DECL_BIN_OP( OrLogical , PRIO_Logical_OR           , "||" , vm->type_Bool            );
DECL_BIN_OP( AndLogical, PRIO_Logical_AND          , "&&" , vm->type_Bool            );
DECL_BIN_OP( OrBitwise , PRIO_Bitwise_inclusive_OR , "|"  , type_promote_gen( a, b ) );
DECL_BIN_OP( XorBitwise, PRIO_Bitwise_exclusive_OR , "^"  , type_promote_gen( a, b ) );
DECL_BIN_OP( AndBitwise, PRIO_Bitwise_AND          , "&"  , type_promote_gen( a, b ) );
DECL_BIN_OP( ShiftRight, PRIO_Right_shift          , "<<" , a                        );
DECL_BIN_OP( ShiftLeft , PRIO_Left_shift           , ">>" , a                        );

DECL_BIN_OP( Min       , PRIO_Function_call        , "min", type_promote_gen( a, b ) );
DECL_BIN_OP( Max       , PRIO_Function_call        , "max", type_promote_gen( a, b ) );
