#pragma once

#include "Inst/Inst.h"
#include "KuSI64.h"

/**
  Ressource State
*/
class Ressource {
public:
    Ressource( RcPtr<Inst> inst, int nout = 0 ) : inst( inst ), nout( nout ) {}
    Ressource( Inst *inst, int nout = 0 ) : inst( inst ), nout( nout ) {}
    Ressource() {}

    Type       *type           () const { return inst->out_type( nout ); }
    KuSI64      size           () const { return inst->out_size( nout ); }
    operator    bool           () const { return inst; }

    void        write_to_stream( std::ostream &os ) const;
    void        thread_visitor ( const std::function<void( Inst *, int, int )> &cb, bool call_before = true ) const;

    bool        get_bytes      ( void *dst, PI32 beg_dst, PI32 beg_src, PI32 len ) const;
    void        get_bytes      ( void *dst, PI32 beg_dst, PI32 beg_src, PI32 len, void *msk ) const;

    RcPtr<Inst> inst;
    int         nout; ///< num output of inst
};

