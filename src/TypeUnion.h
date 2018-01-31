#pragma once

#include "TypeInSane.h"

/**
*/
class TypeUnion : public TypeInSane {
public:
    TypeUnion( SI32 size, SI32 alig );

    virtual bool has_a_constructor() const override;
    virtual void construct        ( const Variable &self, const Vec<Variable> &args, const Vec<RcString> &names ) override;
    virtual void destroy          ( const Variable &self, bool use_virtual ) override;
};

