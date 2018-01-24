#include "CanoCst.h"
#include "CanoVal.h"
#include "KcSI64.h"
#include "../Vm.h"

KcSI64::KcSI64( const KcSI64 &ku ) {
    if ( ku.val )
        val = new CanoVal( *ku.val );
    else {
        kno = ku.kno;
        val = 0;
    }
}

KcSI64::KcSI64( const CanoVal &value ) {
    if ( value.inst->known_value() ) {
        kno = value.inst->get_SI64_value( value.type );
        val = 0;
    } else
        val = new CanoVal( value );
}

KcSI64::~KcSI64() {
    delete val;
}

void KcSI64::write_to_stream( std::ostream &os ) const {
    if ( val )
        os << *val;
    else
        os << kno;
}

KcSI64 &KcSI64::operator=( const KcSI64 &ku ) {
    if ( ku.val ) {
        if ( val )
            *val = *ku.val;
        else
            val = new CanoVal( *ku.val );
    } else {
        kno = ku.kno;
        delete val;
        val = 0;
    }
    return *this;
}

CanoVal KcSI64::cano_val() const {
    return is_known() ? make_cano_val( kno ) : *val;
}

//KcSI64 KcSI64::operator!() const {
//    if ( val )
//        return val->is_non_null();
//    return ! kno;
//}

//KcSI64::operator bool() const {
//    if ( val )
//        return val->is_null();
//    return kno;
//}


bool always_false( const KcSI64 &kc ) {
    return kc.is_known() ? ! kc.kv() : always_false( kc.uv() );
}

bool always_true( const KcSI64 &kc ) {
    return kc.is_known() ? kc.kv() : always_true( kc.uv() );
}

KcSI64 operator+ ( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() +  b.kv() ) : KcSI64( a.cano_val() +  b.cano_val() ); }
KcSI64 operator- ( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() -  b.kv() ) : KcSI64( a.cano_val() -  b.cano_val() ); }
KcSI64 operator* ( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() *  b.kv() ) : KcSI64( a.cano_val() *  b.cano_val() ); }
KcSI64 operator/ ( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() /  b.kv() ) : KcSI64( a.cano_val() /  b.cano_val() ); }
KcSI64 operator% ( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() %  b.kv() ) : KcSI64( a.cano_val() %  b.cano_val() ); }
KcSI64 operator< ( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() <  b.kv() ) : KcSI64( a.cano_val() <  b.cano_val() ); }
KcSI64 operator> ( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() >  b.kv() ) : KcSI64( a.cano_val() >  b.cano_val() ); }
KcSI64 operator<=( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() <= b.kv() ) : KcSI64( a.cano_val() <= b.cano_val() ); }
KcSI64 operator>=( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() >= b.kv() ) : KcSI64( a.cano_val() >= b.cano_val() ); }
KcSI64 operator==( const KcSI64 &a, const KcSI64 &b ) { return a.is_known() && b.is_known() ? KcSI64( a.kv() == b.kv() ) : KcSI64( a.cano_val() == b.cano_val() ); }
