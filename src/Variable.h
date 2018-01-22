#pragma once

#include "System/RcString.h"
#include "ApplyFlags.h"
#include "RefAncestor.h"
class TCI;

/**
*/
class Variable {
public:
    enum class Flags: PI32 { NONE = 0, CONST = 1 };

    Variable( const RcPtr<RefAncestor> &ref, const KuSI64 &offset, const KuSI64 &length, Type *type, Flags flags = Flags::NONE );
    Variable( const Value &value, Flags flags = Flags::NONE ); // make a RefLeaf from a value
    Variable() : type( 0 ), flags( Flags::NONE ) {} // void Variable

    Variable   &operator=           ( const Variable &value );

    Ressource  &ressource_ref       () { return ref->ressource_ref(); }

    operator    bool                () const { return ref; }
    bool        error               () const;
    bool        is_true             () const;
    bool        is_false            () const;
    bool        is_shared           () const;

    void        write_to_stream     ( std::ostream &os ) const;

    RcString    valid_constraint_for( const Variable &tested_var, TCI &tci ) const;
    Variable    find_attribute      ( const RcString &name, bool ret_err = true, bool msg_if_err = false ) const;
    void        setup_vtables       ();
    Variable    constify            ( bool deep );
    Variable    to_Bool             () const;
    Variable    chbeba              ( bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {} );
    Variable    select              ( bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {} );
    Variable    equal               ( const Variable &that ) const;
    void        clear               () { ref = 0; type = 0; }
    Variable    apply               ( bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {}, ApplyFlags apply_flags = ApplyFlags::NONE, const Vec<size_t> &spreads = {} );

    String      as_String           () const;
    FP64        as_FP64             () const;
    SI32        as_SI32             () const;

    Value       get                 () const;
    bool        get_bytes           ( void *dst, PI32 beg_dst, PI32 beg_src, PI32 len ) const;
    void        get_bytes           ( void *dst, PI32 beg_dst, PI32 beg_src, PI32 len, void *msk ) const;

    bool        get_value           ( SI32 &val ) const;

    void        set_bv              ( const Value &src_val, int cst = 0 );
    void        memcpy              ( const Value &src_val, int cst = 0 );

    Variable    sub_part            ( Type *new_type, SI32 add_off ) const;

    template<class T>
    T          *rcast               () const { return (T *)ref->ressource_ref().rcast(); }

    RcPtr<RefAncestor>  ref;
    Type       *type;
    Flags       flags;
    KuSI64      offset;
    KuSI64      length;
};
ENUM_FLAGS( Variable::Flags )
