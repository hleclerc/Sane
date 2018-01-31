#pragma once

#include "TypeInSane.h"

/**
*/
class TypeVarargs : public TypeInSane {
public:
    TypeVarargs();

    virtual void spread_in( const Variable &self, Vec<Variable> &res, Vec<RcString> &names ) override;
    virtual void destroy  ( const Variable &self, bool use_virtual ) override;
};

