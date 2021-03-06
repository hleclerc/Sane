#pragma once

#include "Type_BaseBin.h"
#include "Def.h"

/**
*/
class Type_Def : public Type_BaseBin<Def> {
public:
    Type_Def();

    virtual FP64     get_pertinence( Scope *scope, const Variable &self ) const override;
    virtual Variable make_sl_trial ( Scope *scope, bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<Rc_string> &sl_names, const Vec<Variable> &args, const Vec<Rc_string> &names, bool call_ctor ) const;
    virtual Variable use_sl_trial  ( Scope *scope, bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<Rc_string> &sl_names, const Vec<Variable> &args, const Vec<Rc_string> &names, bool call_ctor, const Variable &trial ) const;
};

