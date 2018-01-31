#include "../Codegen/Codegen.h"
#include "../TypeInSane.h"
#include "Clonable.h"
#include "Conv.h"

/**
*/
class Conv : public Clonable<Conv> {
public:
    Conv( const Value &orig, TypeInSane *target_type ) : target_type( target_type ) {
        init_attr( this->orig, orig );
    }

    Conv( AttrClone, const Conv *orig ) : orig( orig->orig ), target_type( orig->target_type ) {
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        if ( flags & Codegen::WriteInlineCodeFlags::type_is_forced )
            ss << cg.repr( this->children[ 0 ], ss.prio, flags );
        else
            ss( PRIO_Function_call ) << cg.repr( target_type ) << "(" << cg.repr( this->children[ 0 ], PRIO_Cast, Codegen::WriteInlineCodeFlags::type_is_forced ) << ")";
    }

    virtual TypeInSane *created_out_type( int nout ) const override {
        return target_type;
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "Conv[" << *target_type << "]";
    }

    IiValue     orig;
    TypeInSane *target_type;
};


Variable make_Conv( const Value &orig, TypeInSane *target_type ) {
    return { ( new Conv( orig, target_type ) )->new_created_output() };
}
