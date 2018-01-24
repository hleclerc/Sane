#include "CanoConv.h"
#include "CanoVal.h"
#include "../Type.h"
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


struct Add    { void write_to_stream( std::ostream &os ) const { os << "add";     } };
struct Sub    { void write_to_stream( std::ostream &os ) const { os << "sub";     } };
struct Mul    { void write_to_stream( std::ostream &os ) const { os << "mul";     } };
struct Div    { void write_to_stream( std::ostream &os ) const { os << "div";     } };
struct Mod    { void write_to_stream( std::ostream &os ) const { os << "mod";     } };

struct Inf    { void write_to_stream( std::ostream &os ) const { os << "inf";     } };
struct Sup    { void write_to_stream( std::ostream &os ) const { os << "sup";     } };
struct InfEqu { void write_to_stream( std::ostream &os ) const { os << "inf_equ"; } };
struct SupEqu { void write_to_stream( std::ostream &os ) const { os << "sup_equ"; } };
struct Equ    { void write_to_stream( std::ostream &os ) const { os << "equ";     } };


template<class T>
CanoVal make_CanoBinOp( Type *type, const CanoVal &a, const CanoVal &b ) {
    if ( CanoInst *p = common_parent<CanoBinOp<T>>( a.inst.ptr(), a, b ) )
        return { p, type };
    return { new CanoBinOp<T>( a, b ), type };
}

CanoVal operator+ ( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) + make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Add>( a.type, a, b );
}

CanoVal operator- ( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) - make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Sub>( a.type, a, b );
}

CanoVal operator* ( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) * make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Mul>( a.type, a, b );
}

CanoVal operator/ ( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) / make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Div>( a.type, a, b );
}

CanoVal operator% ( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) % make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Mod>( a.type, a, b );
}

CanoVal operator< ( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) < make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Inf>( vm->type_Bool, a, b );
}

CanoVal operator> ( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) > make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Sup>( vm->type_Bool, a, b );
}

CanoVal operator<=( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) <= make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<InfEqu>( vm->type_Bool, a, b );
}

CanoVal operator>=( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) >= make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<SupEqu>( vm->type_Bool, a, b );
}


CanoVal operator==( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) == make_CanoConv( b, tp );
    }

    if ( a.inst == b.inst )
        return true;

    if ( a.inst->known_value() && b.inst->known_value() )
        return false;

    return make_CanoBinOp<Equ>( vm->type_Bool, a, b );
}
