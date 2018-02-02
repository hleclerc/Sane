#pragma once

#include "FunctionSignature.h"
#include "System/RcString.h"
#include "Type.h"
#include <map>

/**
*/
class TypeInSane : public Type {
public:
    struct Attribute {
        RcString         name;
        TypeInSane      *type;
        SI32             off;   ///< in bits
        Variable::Flags  flags;
        Attribute       *prev;
        Attribute       *next;
    };
    using MA  = std::map<RcString,Attribute>;
    using MSA = std::map<RcString,Variable *>;
    using SFS = std::set<FunctionSignature>;


    TypeInSane( const RcString &name );

    virtual bool            has_vtable_at_the_beginning() const override;
    virtual Variable        find_attribute             ( const RcString &name, const Variable &self, Variable::Flags flags, const KuSI64 &off ) const override;
    void                    add_attribute              ( const RcString &name, SI32 off, TypeInSane *type, Variable::Flags flags = Variable::Flags::NONE );
    virtual TypeInSane     *type_in_sane               () override;
    Class                  *orig_class                 () const;
    virtual void            spread_in                  ( const Variable &self, Vec<Variable> &res, Vec<RcString> &names ) override;
    virtual void            construct                  ( const Variable &self, const Vec<Variable> &args, const Vec<RcString> &names ) override;
    virtual Value           to_Value                   ( const Variable &var ) override;
    virtual void            destroy                    ( const Variable &self, bool use_virtual ) override;
    virtual RcString        isa                        ( TypeInSane *type, TCI &tci ) override;
    virtual RcString        isa                        ( SurdefList *se, TCI &tci ) override;

    virtual void            write_to_stream            ( std::ostream &os ) const;
    virtual void            write_cst                  ( std::ostream &os, const PI8 *data, int offset_mod_8 = 0, bool always_add_braces = false ) const;

    // properties
    virtual SI32            kv_size                    () const;
    virtual SI32            kv_alig                    () const;
    virtual String          c_name                     () const;

    RcString                name;
    SI32                    alig;
    MSA                     methods;
    SI32                    _kv_size;
    SI32                    _kv_alig;
    MA                      attributes;
    Class                  *_orig_class;
    Vec<CanoVal>            parameters;        ///< template arguments
    Attribute              *last_attribute;
    bool                    has_new_vtable;
    Attribute              *first_attribute;
    SFS                     abstract_methods;
    MSA                     static_attributes;
    int                     type_promote_score;
};

TypeInSane *type_promote_gen( TypeInSane *a, TypeInSane *b );
