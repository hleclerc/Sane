#pragma once

#include "Type.h"

/**
*/
class TypeProxy : public Type {
public:
    TypeProxy( Type *base_type );

    virtual void        write_to_stream( std::ostream &os ) const override;
    virtual Variable    find_attribute (const RcString &name, const Variable &self, Variable::Flags flags, const KuSI64 &off ) const override;
    virtual TypeInSane *type_in_sane   () override;
    virtual Class      *orig_class     () const override;
    virtual void        write_cst      ( std::ostream &os, const PI8 *data, int offset_mod_8 = 0, bool always_add_braces = false ) const override;
    virtual Value       to_Value       ( const Variable &var ) override;
    virtual void        destroy        ( const Variable &self, bool use_virtual ) override;
    virtual String      c_name         () const override;

    Type               *base_type;
};

