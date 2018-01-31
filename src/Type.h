#pragma once

#include "Variable.h"
#include "CanoType.h"
#include "Value.h"
class Class;
class TCI;

/**
*/
class Type {
public:
    struct CondVal {
        int   kv;
        Value val; ///< val is defined only if kv == 0. if kv < 0 => cond is false. if kv > 0 => cond is true
    };

    Type();

    virtual bool            has_vtable_at_the_beginning() const;
    virtual RcString        checks_type_constraint     ( const Variable &self, const Variable &tested_var, TCI &tci ) const;
    virtual unsigned        get_nb_conversions         ( const Variable &self ) const;
    virtual bool            has_a_constructor          () const; ///< false for types like Union, ...
    virtual double          get_pertinence             ( const Variable &self ) const;
    virtual Variable        find_attribute             (const RcString &name, const Variable &self, Variable::Flags flags, const KuSI64 &off ) const = 0;
    virtual CondVal         get_condition              ( const Variable &self ) const;
    virtual void            get_fail_info              ( const Variable &self, size_t &offset, RcString &source, RcString &msg ) const;
    virtual bool            destroy_attrs              () const;
    virtual Variable        make_sl_trial              ( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) const;
    virtual Variable        use_sl_trial               ( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags, const Variable &trial ) const;
    Type                   *get_proxy_type             ();
    virtual TypeInSane     *type_in_sane               () = 0;
    virtual Class          *orig_class                 () const = 0;
    virtual void            spread_in                  ( const Variable &self, Vec<Variable> &res, Vec<RcString> &names );
    virtual Value           to_Value                   ( const Variable &var ) = 0;
    virtual void            construct                  ( const Variable &self, const Vec<Variable> &args, const Vec<RcString> &names );
    virtual Variable        with_self                  ( Variable &orig, const Variable &new_self ) const;
    virtual void            destroy                    ( const Variable &self, bool use_virtual );
    virtual Variable        chbeba                     ( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names );
    virtual Variable        select                     ( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names );
    virtual Variable        apply                      ( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags = ApplyFlags::NONE );

    virtual void            write_to_stream            ( std::ostream &os ) const = 0;
    virtual void            write_cst                  ( std::ostream &os, const PI8 *data, int offset_mod_8 = 0, bool always_add_braces = false ) const = 0;

    // creation
    virtual RcPtr<CanoInst> convert_cano_cst           ( const void *content, Type *target );

    // properties
    virtual SI64            convert_cst_to_SI64        ( const void *content ) const;
    virtual bool            has_floating_point         () const;
    virtual int             mantissa_len               () const;
    virtual int             exponent_len               () const;
    virtual bool            is_a_TypeBT                () const;
    virtual int             is_signed                  () const;
    virtual SI32            kv_size                    () const;
    virtual SI32            kv_alig                    () const;
    virtual String          c_name                     () const = 0;
    virtual bool            error                      () const;
    virtual KuSI64          size                       ( const RcPtr<Ref> &ref, const KuSI64 &offset ) const;

    // cst ops
    #define BO( NAME ) virtual CanoVal make_Cano##NAME( const void *a, const void *b );
    #include "decl_bin_op.h"
    #undef BO

    Type           *_proxy_type;
    RcPtr<CanoInst> cano_inst;         ///<
};

