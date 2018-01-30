#pragma once

#include "Variable.h"

/**
*/
class SurdefList {
public:
    bool            only_contains_defs_named( const RcString &name ) const;
    void            write_to_stream         ( std::ostream &os ) const { os << "SurdefList(" << lst << ")"; }
    RcString        possible_names          () const;
    bool            has_wildcards           () const;
    bool            eq                      ( SurdefList *sl );
    bool            eq                      ( Type *type );

    Vec<Variable>   lst;   // list of definitions (class, def, ...). sorted by (known) decreasing pertinence
    Vec<Variable>   args;  // as in Foo[ arg1, arg2, ... ]
    Vec<RcString>   names;
    RcPtr<CanoInst> cano_inst;
};
