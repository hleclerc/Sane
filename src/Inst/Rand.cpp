#include "../Codegen/Codegen.h"
#include "../Type.h"
#include "Clonable.h"
#include "CanoSym.h"
#include "Rand.h"

/**
*/
class Rand : public Clonable<Rand,Inst> {
public:
    Rand( Type *type, const KuSI64 &size ) : type( type ) {
        init_attr( this->size, size );
    }

    Rand( AttrClone, const Rand *orig ) : type( orig->type ), size( orig->size ) {
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        ss << "rand()";
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "rand[" << *type << "]";
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        return make_CanoSym( "rand", to_KuSI64( size ).cano() );
    }

    Type    *type;
    IiKuSI64 size;
};

Variable make_Rand( Type *type, const KuSI64 &size ) {
    Rand *res = new Rand( type, size );
    return { res->new_created_output(), 0, size, type };
}
