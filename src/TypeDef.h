#pragma once

#include "TypeInSane.h"

/**
*/
class TypeDef : public TypeInSane {
public:
    TypeDef();

    virtual double   get_pertinence( const Variable &self ) const override;
    virtual Variable make_sl_trial ( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) const override;
    virtual Variable use_sl_trial  ( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags, const Variable &trial ) const override;
    virtual void     destroy       ( const Variable &self, bool use_virtual ) override;
    virtual Variable apply         ( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags = ApplyFlags::NONE ) override;
};

