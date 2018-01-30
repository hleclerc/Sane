#include "reuse_or_create.h"
#include "CanoConv.h"
#include "CanoVal.h"
#include "BinOp.h"
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
        return type_promote_gen( a.type, b.type )->kv_size();
    }

    Op      op;
    CanoVal a;
    CanoVal b;
};




template<class T>
CanoVal make_CanoBinOp( Type *type, const CanoVal &a, const CanoVal &b ) {
    return { reuse_or_create<CanoBinOp<T>>( a, b ), type };
}

CanoVal make_CanoAdd( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) + make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoAdd( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Add>( a.type, a, b );
}

CanoVal make_CanoSub( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) - make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoSub( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Sub>( a.type, a, b );
}

CanoVal make_CanoMul( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) * make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoMul( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Mul>( a.type, a, b );
}

CanoVal make_CanoDiv( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) / make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoDiv( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Div>( a.type, a, b );
}

CanoVal make_CanoDivInt( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoDivInt( make_CanoConv( a, tp ), make_CanoConv( b, tp ) );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoDivInt( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<DivInt>( a.type, a, b );
}

CanoVal make_CanoMod( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) % make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoMod( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Mod>( a.type, a, b );
}

CanoVal make_CanoInf( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) < make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoInf( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Inf>( vm->type_Bool, a, b );
}

CanoVal make_CanoSup( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) > make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoSup( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Sup>( vm->type_Bool, a, b );
}

CanoVal make_CanoInfEqu( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) <= make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoInfEqu( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<InfEqu>( vm->type_Bool, a, b );
}

CanoVal make_CanoSupEqu( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) >= make_CanoConv( b, tp );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoSupEqu( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<SupEqu>( vm->type_Bool, a, b );
}


CanoVal make_CanoEqu( const CanoVal &a, const CanoVal &b ) {
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

CanoVal make_CanoNotEqu( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return make_CanoConv( a, tp ) != make_CanoConv( b, tp );
    }

    if ( a.inst == b.inst )
        return false;

    if ( a.inst->known_value() && b.inst->known_value() )
        return true;

    return make_CanoBinOp<NotEqu>( vm->type_Bool, a, b );
}

CanoVal make_CanoMin( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return min( make_CanoConv( a, tp ), make_CanoConv( b, tp ) );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoMin( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Min>( a.type, a, b );
}

CanoVal make_CanoMax( const CanoVal &a, const CanoVal &b ) {
    if ( a.type != b.type ) {
        Type *tp = type_promote_gen( a.type, b.type );
        return max( make_CanoConv( a, tp ), make_CanoConv( b, tp ) );
    }
    if ( a.inst->known_value() && b.inst->known_value() )
        return a.type->make_CanoMax( a.inst->known_value(), b.inst->known_value() );

    return make_CanoBinOp<Max>( a.type, a, b );
}

CanoVal make_CanoAndLogical( const CanoVal &a, const CanoVal &b ) {
    TODO;
    return {};
}

CanoVal make_CanoOrLogical( const CanoVal &a, const CanoVal &b ) {
    TODO;
    return {};
}
CanoVal make_CanoAndBitwise( const CanoVal &a, const CanoVal &b ) {
    TODO;
    return {};
}

CanoVal make_CanoOrBitwise( const CanoVal &a, const CanoVal &b ) {
    TODO;
    return {};
}

CanoVal make_CanoXorBitwise( const CanoVal &a, const CanoVal &b ) {
    TODO;
    return {};
}

CanoVal make_CanoShiftRight( const CanoVal &a, const CanoVal &b ) {
    TODO;
    return {};
}

CanoVal make_CanoShiftLeft( const CanoVal &a, const CanoVal &b ) {
    TODO;
    return {};
}


CanoVal operator+ ( const CanoVal &a, const CanoVal &b ) { return make_CanoAdd       ( a, b ); }
CanoVal operator- ( const CanoVal &a, const CanoVal &b ) { return make_CanoSub       ( a, b ); }
CanoVal operator* ( const CanoVal &a, const CanoVal &b ) { return make_CanoMul       ( a, b ); }
CanoVal operator/ ( const CanoVal &a, const CanoVal &b ) { return make_CanoDiv       ( a, b ); }

CanoVal operator% ( const CanoVal &a, const CanoVal &b ) { return make_CanoMod       ( a, b ); }
CanoVal operator< ( const CanoVal &a, const CanoVal &b ) { return make_CanoInf       ( a, b ); }
CanoVal operator> ( const CanoVal &a, const CanoVal &b ) { return make_CanoSup       ( a, b ); }
CanoVal operator<=( const CanoVal &a, const CanoVal &b ) { return make_CanoInfEqu    ( a, b ); }
CanoVal operator>=( const CanoVal &a, const CanoVal &b ) { return make_CanoSupEqu    ( a, b ); }
CanoVal operator==( const CanoVal &a, const CanoVal &b ) { return make_CanoEqu       ( a, b ); }
CanoVal operator!=( const CanoVal &a, const CanoVal &b ) { return make_CanoNotEqu    ( a, b ); }
CanoVal operator||( const CanoVal &a, const CanoVal &b ) { return make_CanoOrLogical ( a, b ); }
CanoVal operator&&( const CanoVal &a, const CanoVal &b ) { return make_CanoAndLogical( a, b ); }
CanoVal operator| ( const CanoVal &a, const CanoVal &b ) { return make_CanoOrBitwise ( a, b ); }
CanoVal operator& ( const CanoVal &a, const CanoVal &b ) { return make_CanoAndBitwise( a, b ); }
CanoVal operator^ ( const CanoVal &a, const CanoVal &b ) { return make_CanoXorBitwise( a, b ); }
CanoVal operator<<( const CanoVal &a, const CanoVal &b ) { return make_CanoShiftRight( a, b ); }
CanoVal operator>>( const CanoVal &a, const CanoVal &b ) { return make_CanoShiftLeft ( a, b ); }
CanoVal min       ( const CanoVal &a, const CanoVal &b ) { return make_CanoMin       ( a, b ); }
CanoVal max       ( const CanoVal &a, const CanoVal &b ) { return make_CanoMax       ( a, b ); }
