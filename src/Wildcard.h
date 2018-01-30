#pragma once

#include "System/RcString.h"
#include "Variable.h"

/**
*/
struct Wildcard {
    Wildcard( const RcString &name ) : name( name ) {}

    void     write_to_stream( std::ostream &os ) const { os << "Wildcard(" << name << ")"; }

    RcString name;
};

/**
*/
struct CanoWildcard {
    CanoWildcard( const Wildcard *orig ) {
        TODO;
    }
};

template<>
struct CanoType<Wildcard> {
    enum { unique_ptr = 0 };
    using CT = CanoWildcard;
};

