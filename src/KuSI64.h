#pragma once

#include "System/byte_swaped.h"
#include "System/Stream.h"
class Value;

/**
  Known or unknown value

  If known, stored directly.

  If not, stored as an instruction reference (of type vm->type_#T)
*/
class KuSI64 {
public:
    KuSI64( SI64 kno = 0 ) : val( 0 ), kno( kno ) {}
    KuSI64( const Value &value );
    KuSI64( const KuSI64 &ku );

    ~KuSI64();

    KuSI64      &operator=( const KuSI64 &ku );
    bool         is_known () const { return val == 0; }
    const Value &uv       () const { return *val; } ///< unknown Value (works only if is_known() == false)
    SI64         kv       () const { return kno; }  ///< known Value (works only if is_known() == true)
    KuSI64       operator!() const;
    operator     bool     () const;

protected:
    Value *val; ///<
    SI64   kno; ///<
};
