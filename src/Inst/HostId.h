#pragma once

#include "../CanoType.h"
#include "../Type.h"
#include "CanoHostId.h"
#include "Clonable.h"

/**
*/
template<class T>
class HostId : public Clonable<HostId<T>,Inst> {
public:
    union U {
        T   *p;
        PI64 v;
    };

    HostId( TypeInSane *type, T *val ) : type( type ) {
        u.v = 0;
        u.p = val;
    }

    HostId( AttrClone, const HostId *orig ) : type( orig->type ) {
        u.v = orig->u.v;
        u.p = orig->u.p;
    }

    virtual TypeInSane *created_out_type( int nout ) const override {
        return type;
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        TODO;
    }

    virtual void write_to_stream( std::ostream &os, SI32 nout = -1, Type *type = 0, int offset = -1 ) const {
        if ( u.p )
            os << *u.p;
        else
            os << "NULL";
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "HostId";
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        return _make_cano_inst( N<CanoType<T>::unique_ptr>() );
    }

    RcPtr<CanoInst> _make_cano_inst( N<0> ) const {
        return CanoHostId<typename CanoType<T>::CT>::New( u.p );
    }

    RcPtr<CanoInst> _make_cano_inst( N<1> ) const {
        if ( ! u.p->cano_inst )
            u.p->cano_inst = new CanoHostId<T>( u.p );
        return u.p->cano_inst;
    }

    virtual void *rcast( int nout ) override {
        return u.p;
    }


    TypeInSane *type;
    U           u;
};


/// host pointer stored as a PI64
template<class T>
Variable make_HostId( TypeInSane *type, T *ptr ) {
    HostId<T> *res = new HostId<T>( type, ptr );
    return { res->new_created_output(), 0, 64, type };
}
