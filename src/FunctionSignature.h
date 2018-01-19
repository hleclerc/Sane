#pragma once

#include "System/RcString.h"
class Def;

/**
*/
class FunctionSignature {
public:
    FunctionSignature( Def *def );

    void      write_to_stream( std::ostream &os ) const;
    bool      operator<      ( const FunctionSignature &b ) const { return name < b.name; }

    RcString  name;
};


