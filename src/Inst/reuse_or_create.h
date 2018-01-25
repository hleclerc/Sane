#pragma once

#include "CanoVal.h"
#include "KcSI64.h"


inline CanoInst *first_CanoInst() {
    return 0;
}
template<class... Args>
CanoInst *first_CanoInst( const CanoVal &val, const Args &...args ) {
    return val.inst.ptr();
}
template<class... Args>
CanoInst *first_CanoInst( const RcPtr<CanoInst> &val, const Args &...args ) {
    return val.ptr();
}
template<class... Args>
CanoInst *first_CanoInst( const KcSI64 &kc, const Args &...args ) {
    if ( kc.is_known() == false )
        return kc.uv().inst.ptr();
    return first_CanoInst( args... );
}
template<class T,class... Args>
CanoInst *first_CanoInst( const T &, const Args &...args ) {
    return first_CanoInst( args... );
}


template<class Op,class... Args>
CanoInst *reuse_or_create( Args&& ...args ) {
    // we have a CanoInst child ?
    if ( CanoInst *ch = first_CanoInst( args... ) ) {
        // we can reuse a CanoInst ?
        for( CanoInst *p : ch->parents )
            if ( const Op *op = dynamic_cast<const Op *>( p ) )
                if ( op->same( args... ) )
                    return p;
        // else, create a new Op and register it in parents of ch
        Op *res = new Op( std::forward<Args>( args )... );
        res->child_for_fact = ch;
        ch->parents << res;
        return res;
    }

    //
    return new Op( std::forward<Args>( args )... );
}
