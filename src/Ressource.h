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

    Ressource      &operator=      ( const Ressource &that );

    bool            operator==     ( const Ressource &that ) const;
    bool            operator!=     ( const Ressource &that ) const;
    bool            operator<      ( const Ressource &that ) const;

    RcPtr<CanoInst> cano_inst      ( const KcSI64 &offset, const KcSI64 &length ) const { return inst->cano_inst( nout, offset, length ); }
    RcPtr<CanoInst> cano_inst      () const { return inst->cano_inst( nout ); }
    CanoVal         cano_val       ( const KcSI64 &offset, const KcSI64 &length, Type *type ) const { return inst->cano_val( nout, offset, length, type ); }
    CanoVal         cano_val       () const { return inst->cano_val( nout ); }
    void           *rcast          ();
    Type           *type           () const { return inst->out_type( nout ); }
    KuSI64          size           () const { return inst->out_size( nout ); }
    operator        bool           () const { return bool( inst ); }
    Ref            *ref            () const;

    void            write_to_stream( std::ostream &os ) const;
    void            thread_visitor ( const std::function<void( Inst *, int, int )> &cb, bool call_before = true ) const;

    RcPtr<Inst>     inst;
    int             nout; ///< num output of inst
};

