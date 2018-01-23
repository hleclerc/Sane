#include "../Codegen/Codegen.h"
#include "../Type.h"
#include "Clonable.h"
#include "CanoSym.h"
#include "Rand.h"

/**
*/
class Rand : public Clonable<Rand,Inst> {
public:
    Rand( Type *type ) : type( type ) {
    }

    Rand( AttrClone, const Rand *inst ) : type( inst->type ) {
    }

    virtual void write_inline_code ( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        ss << "rand()";
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "rand[" << *type << "]";
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout, const CanoVal &offset, const CanoVal &length ) const override {
        return make_CanoSym( "rand" );
    }

    Type *type;
};

Variable make_Rand( Type *type, const KuSI64 &size ) {
    Rand *res = new Rand( type );
    return { res->new_created_output( type, size ), 0, size, type };
}
