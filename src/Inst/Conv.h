#pragma once

#include "../System/BoolVec.h"
#include "Clonable.h"

/**
*/
class Conv : public Clonable<Conv> {
public:
    Conv( const Value &orig, Type *target_type );
    Conv( AttrClone, const Conv *orig );

    virtual void  write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override;
    // virtual int   nb_created_outputs       () const override;
    virtual void  write_dot        ( std::ostream &os ) const override;
    // virtual Type *out_type         ( int nout ) const override;

    Type         *target_type;
};

Value make_Conv( const Value &orig, Type *target_type );