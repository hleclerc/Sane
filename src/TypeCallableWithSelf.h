#pragma once

#include "TypeInSane.h"

/**
*/
class TypeCallableWithSelf : public TypeInSane {
public:
    TypeCallableWithSelf();

    virtual void     destroy( const Variable &self, bool use_virtual ) override;
    virtual Variable apply  ( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags = ApplyFlags::NONE );
};

