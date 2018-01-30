#pragma once

#include "CanoVal.h"

/**
*/
template<class T>
class CanoHostId : public CanoInst {
public:
    union U {
        T   *p;
        PI64 v;
    };

    CanoHostId( T *p ) {
        u.v = 0;
        u.p = p;
    }

    template<class O>
    static CanoHostId *New( const O *orig ) {
        TODO;
        return 0;
    }

    virtual void write_dot( std::ostream &os, Type *type ) const {
        os << "HostId";
    }

    virtual void attr_visitor( AttrVisitor &visitor ) const {
    }

    virtual KcSI64 length() const {
        return 64;
    }

    U u;
};
