#pragma once

#include "System/byte_swaped.h"
#include "System/Stream.h"
class CanoVal;
class Value;

/**
  Known or unknown value

  If known, stored directly.

  If not, stored as an instruction reference (of type vm->type_#T)
*/
class KuSI64 {
public:
    struct ShallowCmp {
        bool operator==( ShallowCmp &that ) const { return std::tie( ku.val, ku.kno ) == std::tie( that.ku.val, that.ku.kno ); }
        bool operator< ( ShallowCmp &that ) const { return std::tie( ku.val, ku.kno ) <  std::tie( that.ku.val, that.ku.kno ); }
        const KuSI64 &ku;
    };

    KuSI64( SI64 kno = 0 ) : val( 0 ), kno( kno ) {}
    KuSI64( const Value &value );
    KuSI64( const KuSI64 &ku );

    ~KuSI64();

    KuSI64      &operator=    ( const KuSI64 &ku );

    bool         is_known     () const { return val == 0; }
    const Value &uv           () const { return *val; } ///< unknown Value (works only if is_known() == false)
    SI64         kv           () const { return kno; }  ///< known Value (works only if is_known() == true)

    CanoVal      cano_val     () const; ///< canonical representation. Enables faster comparisons

    KuSI64       operator!    () const;
    explicit     operator bool() const;

protected:
    Value       *val; ///<
    SI64         kno; ///<
};

