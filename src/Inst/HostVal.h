#pragma once

#include "../Variable.h"

/**
*/
template<class T>
class HostVal : public Inst {
public:
    template<class ...Args>
    HostVal( Args&& ...args ) : data( std::forward<Args>( args )... ) {}

    virtual void write_dot( std::ostream &os ) const override {
        os << "HostVal";
    }

    virtual void *rcast( SI32 nout ) override {
        return &data;
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        TODO;
        return 0;
    }

    T     data;
};

template<class T,class ...Args>
Variable make_HostVal( Type *type, Args&& ...args ) {
    HostVal<T> *res = new HostVal<T>( std::forward<Args>( args )... );
    return { res->new_created_output( type, 8 * sizeof( T ) ) };
}

#define MAKE_KV( T, ... ) make_HostVal<T>( vm->type_##T, ##__VA_ARGS__ )
