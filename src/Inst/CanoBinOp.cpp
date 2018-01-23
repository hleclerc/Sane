#include "CanoVal.h"
#include "../Vm.h"

/***/
template<class Op>
class CanoBinOp : public CanoInst {
public:
    CanoBinOp( const CanoVal &a, const CanoVal &b ) {
        add_child( a );
        add_child( b );
    }

    bool same( const CanoVal &a, const CanoVal &b ) const {
        return ::always_true( a == children[ 0 ] ) && ::always_true( b == children[ 1 ] );
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << op;
    }

    Op op;
};

struct Equ {
    void write_to_stream( std::ostream &os ) const { os << "equ"; }
};

struct Add {
    void write_to_stream( std::ostream &os ) const { os << "add"; }
};

template<class T>
CanoVal make_CanoBinOp( Type *type, const CanoVal &a, const CanoVal &b ) {
    if ( CanoInst *p = common_parent<CanoBinOp<T>>( a.inst.ptr(), a, b ) )
        return { p, type };
    return { new CanoBinOp<T>( a, b ), type };
}

CanoVal operator==( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type )
        TODO;

    if ( a.inst == b.inst )
        return true;

    if ( a.inst->known_value() && b.inst->known_value() )
        return false;

    return make_CanoBinOp<Equ>( vm->type_Bool, a, b );
}

CanoVal operator+( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type )
        TODO;

    return make_CanoBinOp<Add>( a.type, a, b );
}
