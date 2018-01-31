#pragma once

#include "System/RcString.h"
#include "System/LVec.h"
#include "Variable.h"

/**
*/
struct Import {
    struct Export {
        void     write_to_stream( std::ostream &os ) const { os << name << "=" << var; }

        RcString name;
        Variable var;
    };

    void            write_to_stream( std::ostream &os ) const { os << exports; }

    RcString        filename;
    LVec<Export>    exports;
    bool            finished; ///< useful for recursive imports
    RcPtr<CanoInst> cano_inst;
};
