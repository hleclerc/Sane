#pragma once

#include "../System/Deque.h"
#include "../System/RcPtr.h"
#include <set>
class CanoVal;
class KcSI64;
class Type;

/**
  "canonical instruction" (Inst in canonical representation), to know value of an inst (not its manipulation history)
*/
class CanoInst : public RcObj {
public:
    struct AttrVisitor {
        virtual ~AttrVisitor() {}
        virtual void on( const char *, const RcPtr<CanoInst> & ) {}
        virtual void on( const char *, const CanoVal & ) {}
        virtual void on( const char *, const KcSI64 & ) {}
        virtual void on( const char *, Type * ) {}
    };

    CanoInst();
    virtual ~CanoInst();

    virtual void            write_to_stream ( std::ostream &os, Type *type = 0 ) const;
    virtual bool            write_graph_rec ( std::ostream &ss, std::set<const CanoInst *> &seen_insts, const std::function<void(std::ostream&, const CanoInst *)> &f ) const;
    virtual void            write_dot       ( std::ostream &os, Type *type ) const = 0;

    virtual void            children_visitor( const std::function<void( const char *, CanoInst * )> &visitor );
    virtual SI64            get_SI64_value  ( Type *orig ) const;
    virtual void            get_out_insts   ( Deque<CanoInst *> &outs );
    virtual RcPtr<CanoInst> simp_CanoConv   ( Type *orig, Type *target );
    virtual void            attr_visitor    ( AttrVisitor &visitor ) const = 0;
    virtual bool            always_false    ( Type *type ) const;
    virtual bool            always_true     ( Type *type ) const;
    virtual bool            known_value     () const;                                 ///<
    virtual RcPtr<CanoInst> sub_part        ( const KcSI64 &off, const KcSI64 &len );
    virtual KcSI64          length          () const = 0;                             ///< size in memory (in bits)

    static void             display_graphviz( const Vec<CanoInst *> &lst, const std::function<void (std::ostream &, const CanoInst *)> &f = {}, const std::string &filename = ".res", bool disp_parents = false, bool launch = true );

    CanoInst               *child_for_fact;
    Vec<CanoInst *>         parents;

    mutable void           *op_mp;
    mutable size_t          op_id;

    static size_t           cur_op_id;
};

#define CANO_INST_ATTR_VISIT( NAME ) visitor.on( #NAME, NAME );

