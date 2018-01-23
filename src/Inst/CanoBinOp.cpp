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

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << op;
    }

    Op op;
};

struct Equ {
    void write_to_stream ( std::ostream &os ) const { os << "=="; }
};

template<class T>
CanoVal make_CanoBinOp( Type *type, const CanoVal &a, const CanoVal &b ) {
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
