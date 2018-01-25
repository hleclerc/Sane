#include "reuse_or_create.h"
#include "CanoConv.h"
#include "CanoVal.h"
#include "../Type.h"
#include "../Vm.h"

/***/
template<class Op>
class CanoBinOp : public CanoInst {
public:
    CanoBinOp( const CanoVal &a, const CanoVal &b ) : a( a ), b( b ) {
    }

    bool same( const CanoVal &a, const CanoVal &b ) const {
        return ::always_true( this->a == a ) && ::always_true( this->b == b );
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << op;
    }

    virtual void attr_visitor( AttrVisitor &visitor ) const override {
        CANO_INST_ATTR_VISIT( a );
        CANO_INST_ATTR_VISIT( b );
    }

    virtual KcSI64 length() const override {
        return type_promote_gen( a.type, b.type )->content.data.kv_size;
    }

    Op      op;
    CanoVal a;
    CanoVal b;
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

struct Min    { void write_to_stream( std::ostream &os ) const { os << "min";     } };
struct Max    { void write_to_stream( std::ostream &os ) const { os << "max";     } };


template<class T>
CanoVal make_CanoBinOp( Type *type, const CanoVal &a, const CanoVal &b ) {
    return { reuse_or_create<CanoBinOp<T>>( a, b ), type };
}

CanoVal operator+( const CanoVal &a, const CanoVal &b ) {
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

CanoVal min( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return min( make_CanoConv( a, tp ), make_CanoConv( b, tp ) );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Min>( a.type, a, b );
}

CanoVal max( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return max( make_CanoConv( a, tp ), make_CanoConv( b, tp ) );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        TODO;

    return make_CanoBinOp<Max>( a.type, a, b );
}
