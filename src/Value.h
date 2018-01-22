#pragma once

#include "Ressource.h"
class BoolVec;
class Type;

/**
*/
class Value {
public:
    Value( const Ressource &ressource, const KuSI64 &offset, const KuSI64 &length, Type *type ); ///< sub value of `ressource`
    Value( const Ressource &ressource ); ///< entire `ressource` value
    Value( Inst *inst, int nout = 0 ); ///< entire Ressource{ inst, nout } value
    Value( const Value &value ); //
    Value() {} // void value

    Value      &operator=      ( const Value &value );

    bool        operator<      ( const Value &value ) const;
    bool        operator==     ( const Value &value ) const;

    operator    bool           () const { return ressource; }

    void        write_to_stream( std::ostream &os ) const;

    bool        get_bytes      ( void *dst, PI32 beg_dst = 0 ) const;
    bool        get_bytes      ( void *dst, PI32 beg_dst, void *msk ) const;

    bool        is_not_equal   ( const Value &that ) const; ///< works for a very limited number of cases (SI32, ...).
    bool        is_equal       ( const Value &that ) const; ///< works for a very limited number of cases (SI32, ...).

    bool        is_non_null    () const;
    bool        is_null        () const;

    // Ressource
    Ressource   ressource;
    KuSI64      offset;
    KuSI64      length;
    Type       *type;
};

