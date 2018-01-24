#include "Inst/CanoCst.h"
#include "KuSI64.h"
#include "Value.h"
#include "Vm.h"

KuSI64::KuSI64( const KuSI64 &ku ) {
    if ( ku.val )
        val = new Value( *ku.val );
    else {
        kno = ku.kno;
        val = 0;
    }
}

KuSI64::~KuSI64() {
    delete val;
}

KuSI64::KuSI64( const Value &value ) {
    // if ( value.type == vm->type_SI64, "TODO" );
    KcSI64 kc( value );
    if ( kc.is_known() ) {
        kno = kc.kv();
        val = 0;
    } else {
        val = new Value( value );
    }
}

KuSI64 &KuSI64::operator=( const KuSI64 &ku ) {
    if ( ku.val ) {
        if ( val )
            *val = *ku.val;
        else
            val = new Value( *ku.val );
    } else {
        kno = ku.kno;
        delete val;
        val = 0;
    }
    return *this;
}

KcSI64 KuSI64::cano() const {
    return val ? KcSI64( val->cano_val() ) : KcSI64( kno );
}

//KuSI64 KuSI64::operator!() const {
//    if ( val )
//        return val->is_non_null();
//    return ! kno;
//}

//KuSI64::operator bool() const {
//    if ( val )
//        return val->is_null();
//    return kno;
//}

