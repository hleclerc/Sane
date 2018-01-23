#pragma once

#include "System/EnumFlags.h"
#include "RefAncestor.h"

/**
*/
class Ref : public RefAncestor {
public:
    enum class Flags: PI32 { NONE = 0, NOT_CONSTRUCTED = 1, CONST = 2 };

    Ref( const Ressource &creator, Flags flags = Flags::NONE );
    virtual ~Ref();

    virtual void       write_to_stream( std::ostream &os ) const;
    virtual bool       is_shared      () const;
    virtual void       constify       ();
    virtual Ref       *ref            () const override;
    virtual void       set            ( const Ressource &src_ressource, int cst = 0 );

    PI64               creation_inter_date; ///< value of inter_date during creation
    Ressource          current;             ///< current state
    Ressource          creator;             ///< current state
    Flags              flags;
};
ENUM_FLAGS( Ref::Flags )

