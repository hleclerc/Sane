#pragma once

#include "Value.h"
class Variable;
class RcString;

/**
*/
class RefAncestor : public RcObj {
public:
    virtual ~RefAncestor();

    virtual Variable   intercept_find_attribute( const RcString &name, Type *type, bool is_const, SI32 offset ) const;
    virtual void       write_to_stream         ( std::ostream &os ) const = 0;
    virtual Ressource &ressource_ref           () = 0;
    virtual bool       is_shared               () const;
    virtual void       constify                () = 0;
    virtual void       set                     ( const Ressource &ressource, int cst = 0 ) = 0;
};

