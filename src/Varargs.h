#pragma once

#include "Variable.h"

/**
*/
struct Varargs {
    void          write_to_stream( std::ostream &os ) const { os << values << " names=" << names; }

    Vec<Variable> values;
    Vec<String>   names;
};

/**
*/
struct CanoVarargs {
    CanoVarargs( const Varargs *orig ) {
        TODO;
    }

    Vec<CanoVal> values;
    Vec<CanoVal> names;
};

template<>
struct CanoType<Varargs> {
    enum { unique_ptr = 0 };
    using CT = CanoVarargs;
};

