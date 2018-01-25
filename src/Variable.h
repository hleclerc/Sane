#pragma once

#include "System/RcString.h"
#include "ApplyFlags.h"
#include "Ref.h"
class Ref;
class TCI;

/**
*/
class Variable {
public:
    enum class Flags: PI32 { NONE = 0, CONST = 1 };

    Variable( const RcPtr<RefAncestor> &ref_anc, const KuSI64 &offset, const KuSI64 &length, Type *type, Flags flags = Flags::NONE );
    Variable( const RcPtr<RefAncestor> &ref_anc, Flags flags = Flags::NONE );
    Variable() : flags( Flags::NONE ), type( 0 ) {} // void Variable

    Variable          &operator=           ( const Variable &value );

    Ref               *ref                 () const { return ref_anc->ref(); }

    CanoVal            cano_repr           () const;

    bool               is_shared           () const;
    bool               is_false            () const;
    bool               is_true             () const;
    bool               error               () const;
    operator           bool                () const { return bool( ref_anc ); }

    void               write_to_stream     ( std::ostream &os ) const;

    RcString           valid_constraint_for( const Variable &tested_var, TCI &tci ) const;
    Variable           find_attribute      ( const RcString &name, bool ret_err = true, bool msg_if_err = false ) const;
    void               setup_vtables       ();
    Variable           constify            ( bool deep );
    Variable           to_Bool             () const;
    Variable           chbeba              ( bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {} );
    Variable           select              ( bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {} );
    Variable           equal               ( const Variable &that ) const;
    void               clear               () { ref_anc = 0; type = 0; }
    Variable           apply               ( bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {}, ApplyFlags apply_flags = ApplyFlags::NONE, const Vec<size_t> &spreads = {} );

    String             as_String           () const;
    FP64               as_FP64             () const;
    SI32               as_SI32             () const;

    Value              get                 () const;

    void               set_bv              ( const Value &src_val, int cst = 0 );
    void               memcpy              ( const Value &src_val, int cst = 0 );

    Variable           sub_part            ( Type *new_type, SI32 add_off ) const;

    template<class T>
    T                 *rcast               () const { return (T *)ref_anc->ref()->current.rcast(); }

    RcPtr<RefAncestor> ref_anc;
    KuSI64             offset;
    KuSI64             length;
    Flags              flags;
    Type              *type;
};
ENUM_FLAGS( Variable::Flags )
