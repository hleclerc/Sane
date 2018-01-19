#include "System/BoolVec.h"
#include "Ressource.h"

void Ressource::thread_visitor( const std::function<void (Inst *, int, int)> &cb, bool call_before ) const {
    inst->thread_visitor( nout, cb, call_before );
}

bool Ressource::get_bytes( void *dst, PI32 beg_dst, PI32 beg_src, PI32 len ) const {
    BoolVec msk( len, true );
    get_bytes( dst, beg_dst, beg_src, len, msk.data );
    return msk.all_false();
}

void Ressource::get_bytes( void *dst, PI32 beg_dst, PI32 beg_src, PI32 len, void *msk ) const {
    return inst->get_bytes( nout, dst, beg_dst, beg_src, len, msk );
}

void Ressource::write_to_stream( std::ostream &os ) const {
    if ( inst )
        inst->write_to_stream( os, nout );
    else
        os << "NULL";
}
