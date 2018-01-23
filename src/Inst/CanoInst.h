#pragma once

#include "../System/Deque.h"
#include "../System/RcPtr.h"
#include <set>
class CanoVal;
class Type;

/**
  "canonical instruction" (Inst in canonical representation), to know value of an inst (not its manipulation history)
*/
class CanoInst : public RcObj {
public:
    struct Parent { bool operator==( const Parent &p ) const { return inst == p.inst && ninp == p.ninp; } CanoInst *inst; int ninp; };

    CanoInst();
    virtual ~CanoInst();

    virtual void    write_to_stream ( std::ostream &os, Type *type ) const;
    virtual bool    write_graph_rec ( std::ostream &ss, std::set<const CanoInst *> &seen_insts, const std::function<void(std::ostream&, const CanoInst *)> &f ) const;
    virtual void    write_dot       ( std::ostream &os, Type *type ) const = 0;

    virtual void    get_out_insts   ( Deque<CanoInst *> &outs );

    static void     display_graphviz( const Vec<CanoInst *> &lst, const std::function<void (std::ostream &, const CanoInst *)> &f = {}, const std::string &filename = ".res", bool disp_parents = false, bool launch = true );
    static void     dfs_rec         ( CanoInst *inst, const std::function<void(CanoInst*)> &f, bool deep = false, bool f_after = false, bool need_inc_ref = false );
    static void     dfs             ( const Vec<CanoInst *> &lst, const std::function<void(CanoInst*)> &f, bool deep = false, bool f_after = false, bool need_inc_ref = false );

    Vec<CanoVal>    children;
    Vec<Parent>     parents;
    Type           *type;     ///< optionnal

    mutable void   *op_mp;
    mutable size_t  op_id;

    static size_t   cur_op_id;
};
