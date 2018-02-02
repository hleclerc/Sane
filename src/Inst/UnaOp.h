#pragma once

#include "../Codegen/Codegen.h"
#include "Clonable.h"
#include "../Vm.h"

/**
*/
template<class Op>
class UnaOp : public Clonable<UnaOp<Op>> {
public:
    UnaOp( const Value &a ) {
        this->init_attr( this->a, a );
    }

    UnaOp( AttrClone, const UnaOp *orig ) : a( orig->a ) {
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << Op::name();
    }

    virtual TypeInSane *created_out_type( int nout ) const override {
        return Op::type( a.type );
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        ss( Op::prio ) << Op::str() << " " << cg.repr( this->to_Value( a ), Op::prio );
    }

    IiValue a;
};

#define DECL_UNA_OP( NAME, PRIO, STR, TYPE ) \
    Variable make_##NAME( const Value &a ); \
    struct NAME { \
        enum { prio = PRIO }; \
        static const char *str () { return STR; } \
        static const char *name() { return #NAME; } \
        static Variable    make( const Value &a ) { return make_##NAME( a ); } \
        static TypeInSane *type( TypeInSane *a ) { return TYPE; } \
    }

DECL_UNA_OP( Neg       , PRIO_Unary_negation, "-", a );
DECL_UNA_OP( NotLogical, PRIO_Logical_not   , "!", vm->type_Bool );
DECL_UNA_OP( NotBitwise, PRIO_Logical_not   , "~", a );
