#pragma once

#include "CanoType.h"
#include "Variable.h"

/**
*/
class CallableWithSelfOrArgs {
public:
    void     write_to_stream( std::ostream &os ) const { os << "CallableWithSelf(" << callable << "," << self << ")"; }

    Variable callable;
    Variable self;
};

/**
*/
struct CanoCallableWithSelfOrArgs {
    CanoCallableWithSelfOrArgs( const CallableWithSelfOrArgs *orig ) : callable( orig->callable.cano() ) {

    }

    CanoVal callable;
    CanoVal self;
};

template<>
struct CanoType<CallableWithSelfOrArgs> {
    enum { unique_ptr = 0 };
    using CT = CanoCallableWithSelfOrArgs;
};

