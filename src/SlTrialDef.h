#pragma once

#include "Type.h"
#include "TCI.h"

/**
*/
struct SlTrialDef {
    void          write_to_stream( std::ostream &os ) const { os << "SlTrialDef(...)"; }

    Vec<Variable> args;
    Variable      def;
    RcString      msg;
    TCI           tci;
    Type::CondVal condition;
};

/**
*/
struct CanoSlTrialDef {
    CanoSlTrialDef( const SlTrialDef *orig ) {
        TODO;
    }
};

template<>
struct CanoType<SlTrialDef> {
    enum { unique_ptr = 0 };
    using CT = CanoSlTrialDef;
};

