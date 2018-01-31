#pragma once

#include "Ressource.h"
class TypeInSane;
class BoolVec;

/**
*/
class Value {
public:
    Value( const Ressource &ressource, const KuSI64 &offset, const KuSI64 &length, TypeInSane *type ); ///< sub value of `ressource`
    Value( const Ressource &ressource ); ///< entire `ressource` value
    Value( Inst *inst, int nout = 0 ); ///< entire Ressource{ inst, nout } value
    Value( const Value &that ); //
    Value() {} // void value

    Value      &operator=         ( const Value &value );

    bool        operator<         ( const Value &value ) const;
    bool        operator==        ( const Value &value ) const;

    operator    bool              () const { return ressource; }

    void        write_to_stream   ( std::ostream &os ) const;
    CanoVal     cano_val          ( bool fully_solved = false ) const; ///< canonical representation. Enables faster comparisons
    KuSI64      size              () const;

    Ressource   ressource;
    KuSI64      offset;
    KuSI64      length;
    TypeInSane *type;
};

