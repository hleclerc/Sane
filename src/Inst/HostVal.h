#pragma once

#include "../System/Memcpy.h"
#include "../Value.h"

/**
*/
template<class T>
class HostVal : public Inst {
public:
    template<class ...Args>
    HostVal( Type *type, Args&& ...args ) : type( type ), data( std::forward<Args>( args )... ) {}

    virtual void write_dot( std::ostream &os ) const override {

    }

    virtual bool get_bytes( int nout, void *dst, int beg_dst, int beg_src, int len, void *msk ) const override {
        if ( PI32( beg_src ) >= 8 * sizeof( data ) )
            return true;
        if ( PI32( beg_src ) + len > 8 * sizeof( data ) )
            len = 8 * sizeof( data ) - beg_src;
        memcpy_bit( dst, beg_dst, &data, beg_src, len, msk );
        memset_bit( msk, beg_dst, false, len );
        return true;
    }

    virtual void *rcast( SI32 nout ) override {
        return &data;
    }

    virtual CanoVal cano_repr( int nout, const CanoVal &offset, const CanoVal &length, Type *type ) const {
        TODO;
        return {};
    }

    Type *type;
    T     data;
};

template<class T,class ...Args>
Value make_HostVal( Type *type, Args&& ...args ) {
    return { new HostVal<T>( type, std::forward<Args>( args )... ), 0, type };
}

#define MAKE_KV( T, ... ) make_HostVal<T>( gvm->type_##T, ##__VA_ARGS__ )
