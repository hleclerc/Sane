#pragma once

#include "../System/byte_swaped.h"
#include "../System/Stream.h"
class CanoVal;
class Value;

/**
  Known or unknown value

  If known, stored directly.

  If not, stored as an instruction reference (of type vm->type_#T)
*/
class KcSI64 {
public:
    struct ShallowCmp {
        bool operator==( ShallowCmp &that ) const { return std::tie( ku.val, ku.kno ) == std::tie( that.ku.val, that.ku.kno ); }
        bool operator< ( ShallowCmp &that ) const { return std::tie( ku.val, ku.kno ) <  std::tie( that.ku.val, that.ku.kno ); }
        const KcSI64 &ku;
    };

    KcSI64( SI64 kno = 0 ) : val( 0 ), kno( kno ) {}
    KcSI64( const CanoVal &value );
    KcSI64( const Value &value );
    KcSI64( const KcSI64 &ku );

    ~KcSI64();

    void           write_to_stream( std::ostream &os ) const;

    KcSI64        &operator=      ( const KcSI64 &ku );

    bool           is_known       () const { return val == 0; } ///<
    CanoVal        cano_val       () const;                     ///< return a cano val, whether value is known or not
    const CanoVal &uv             () const { return *val; }     ///< unknown Value (works only if is_known() == false)
    SI64           kv             () const { return kno; }      ///< known Value (works only if is_known() == true)


protected:
    CanoVal       *val; ///<
    SI64           kno; ///<
};

bool always_false( const KcSI64 &val );
bool always_true ( const KcSI64 &val );

KcSI64 operator+ ( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator- ( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator* ( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator/ ( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator% ( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator< ( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator> ( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator<=( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator>=( const KcSI64 &a, const KcSI64 &b );
KcSI64 operator==( const KcSI64 &a, const KcSI64 &b );
KcSI64 min       ( const KcSI64 &a, const KcSI64 &b );
KcSI64 max       ( const KcSI64 &a, const KcSI64 &b );
