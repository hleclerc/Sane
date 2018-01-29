#pragma once

#include "IiRessourceWithOffset.h"
#include "CodegenData.h"
#include "IiValue.h"
#include "CanoVal.h"

#include "../KuSI64.h"

#include <functional>
#include <set>

class StreamPrio;
class Ressource;
class StreamSep;
class Codegen;
class BoolVec;
class KcSI64;
class Type;
class Ref;

/**
*/
class Inst : public RcObj {
public:
    struct Parent { bool operator==( const Parent &p ) const { return inst == p.inst && ninp == p.ninp; } Inst *inst; int ninp; };
    struct CreatedOutput { Ref *ref; };

    using FuncOnRefPtr = std::function<void(Ref *)>;
    using AssFunc = std::function<void(const PI8 *)>;

    Inst();
    virtual ~Inst();

    void                    clear_children         ();
    int                     add_child              ( const Ressource &ch );
    void                    mod_child              ( int ninp, const Ressource &ch );
    void                    rem_child              ( int ninp );
    void                    rem_out                ( int nout, bool check_if_unused = true ); ///< shifts outputs > nout

    void                    init_attr              ( IiRessourceWithOffset &attr, const Ressource &ressource, const KuSI64 offset );
    void                    init_attr              ( IiRessource           &attr, const Ressource &ressource );
    void                    init_attr              ( IiKuSI64              &attr, const KuSI64 &val );
    void                    init_attr              ( IiValue               &attr, const Value &val );

    const Ressource        &to_Ressource           ( const IiRessource &attr ) const;
    KuSI64                  to_KuSI64              ( const IiKuSI64    &attr ) const;
    Value                   to_Value               ( const IiValue     &attr ) const;


    Ref                    *new_created_output     ();

    virtual void            get_linked_refs        ( int nout, const KcSI64 &offset, const KcSI64 &length, const std::function<void (Ref *)> &cb );

    FuncOnRefPtr            add_wr_cb              (); ///< cb to add a ressource thay may be written by this
    FuncOnRefPtr            add_rd_cb              (); ///< cb to add a ressource thay may be read by this

    void                    replace_by             ( int nout, Inst *new_inst, int new_nout ); ///< replace { this, nout } by { new_inst, new_nout }

    bool                    all_children_with_op_id( size_t oi ) const;
    int                     nb_parents_on_nout     ( int nout ) const;
    virtual Type           *created_out_type       ( int nout ) const;
    virtual KuSI64          created_out_size       ( int nout ) const;
    virtual KuSI64          created_out_alig       ( int nout ) const;
    virtual RcPtr<CanoInst> make_cano_inst         ( int nout ) const; ///< called by cano_repr if not already filled
    virtual void            externalize            ( Inst *inst, size_t ninp );
    Type                   *out_type               ( int nout ) const;
    KuSI64                  out_size               ( int nout ) const;
    virtual int             inp_corr               ( int nout ) const;
    virtual Inst           *clone                  () const;

    KcSI64                  cano_kcSI64            ( const IiKuSI64 &value ) const;

    RcPtr<CanoInst>         cano_inst              ( const IiRessource &ressource, const KcSI64 &offset, const KcSI64 &length ) const;
    RcPtr<CanoInst>         cano_inst              ( const IiRessource &ressource ) const;
    RcPtr<CanoInst>         cano_inst              ( int nout, const KcSI64 &offset, const KcSI64 &length ) const; ///< canonical representation. Enables faster comparisons
    RcPtr<CanoInst>         cano_inst              ( int nout ) const; ///< canonical representation. Enables faster comparisons

    CanoVal                 cano_val               ( const IiRessource &ressource, const KcSI64 &offset, const KcSI64 &length, Type *type ) const;
    CanoVal                 cano_val               ( const IiRessource &ressource ) const;
    CanoVal                 cano_val               ( int nout, const KcSI64 &offset, const KcSI64 &length, Type *type ) const; ///< canonical representation. Enables faster comparisons
    CanoVal                 cano_val               ( int nout ) const; ///< canonical representation. Enables faster comparisons
    CanoVal                 cano_val               ( const IiValue &value ) const; ///< canonical representation. Enables faster comparisons


    virtual bool            is_non_null            ( int nout, const KuSI64 &offset, const KuSI64 &length, Type *type ) const;
    virtual bool            is_null                ( int nout, const KuSI64 &offset, const KuSI64 &length, Type *type ) const;

    virtual void            write_to_stream        ( std::ostream &os, SI32 nout = -1, Type *type = 0, int offset = -1 ) const;
    virtual bool            write_graph_rec        ( std::ostream &ss, std::set<const Inst *> &seen_insts, const std::function<void(std::ostream&, const Inst *)> &f, bool disp_parents ) const;
    virtual AssFunc         get_assign_func        ( int nout, int off, int len );
    virtual void            write_dot              ( std::ostream &os ) const = 0;
    virtual void           *rcast                  ( int nout );

    virtual void            write_inline_code      ( StreamPrio &ss, Codegen &cg, int nout, int flags ); ///< helper for case nb_created_outputs == 1
    virtual bool            expects_a_reg_at       ( int ninp ) const;
    virtual bool            can_be_inlined         () const;
    virtual void            write_code             ( StreamSep &ss, Codegen &cg );

    // instructions with sub graphs
    virtual Inst           *parent_out_inst        () const;
    virtual bool            simplify_for_cg        ( Codegen &cg );
    virtual void            get_out_insts          ( Deque<Inst *> &outs );

    void                    thread_visitor         ( int nout, const std::function<void( Inst *inst, int nout, int ninp )> &cb, bool call_before = true );

    static void             display_graphviz       ( const Vec<Inst *> &lst, const std::function<void (std::ostream &, const Inst *)> &f = {}, const std::string &filename = ".res", bool disp_parents = false, bool launch = true );
    static void             dfs_rec                ( Inst *inst, const std::function<void(Inst*)> &f, bool deep = false, bool f_after = false, bool need_inc_ref = false );
    static void             dfs                    ( const Vec<Inst *> &lst, const std::function<void(Inst*)> &f, bool deep = false, bool f_after = false, bool need_inc_ref = false );

    Vec<CreatedOutput>      created_outputs; ///<
    size_t                  creation_date;   ///< used mainly for ordering during code generation
    mutable RcPtr<CanoInst> cano_inst_buf;
    Vec<Ressource>          children;
    Vec<Parent>             parents;
    Vec<int>                iomap;           ///< ( num output - created_outputs.size() ) => num child for each ressources potentially modified by this

    CodegenData             cd;

    mutable void           *op_mp;
    mutable size_t          op_id;

    static size_t           cur_op_id;
    static size_t           date;            ///< for creation date (enable to find similar ordering in code generation)
};

