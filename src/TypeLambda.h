#pragma once

#include "TypeInSane.h"

/**
*/
class TypeLambda : public TypeInSane {
public:
    TypeLambda();

    virtual bool     destroy_attrs() const override;
    virtual Variable with_self    ( Variable &orig, const Variable &new_self ) const override;
    virtual void     destroy      ( const Variable &self, bool use_virtual ) override;
    virtual Variable chbeba       ( Variable &self, bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {} ) override;
    virtual Variable select       ( Variable &self, bool want_ret, const Vec<Variable> &args = {}, const Vec<RcString> &names = {} ) override;
    virtual Variable apply        ( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags = ApplyFlags::NONE ) override;
};

