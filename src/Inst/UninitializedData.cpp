#include "../Codegen/Codegen.h"
#include "../KuSI64.h"
#include "../Type.h"
#include "../Ref.h"
#include "../Vm.h"

#include "CanoUninitializedData.h"
#include "UninitializedData.h"
#include "Clonable.h"

/**
*/
class UninitializedData : public Clonable<UninitializedData,Inst> {
public:
    UninitializedData( Type *type, const KuSI64 &size ) : type( type ) {
        init_attr( this->size, size );
    }

    UninitializedData( AttrClone, const UninitializedData *UninitializedData ) {
    }

    virtual Type *created_out_type( int nout ) const override {
        return type;
    }

    virtual KuSI64 created_out_size( int nout ) const override {
        return to_KuSI64( size );
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        ss << "{}";
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "UD";
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        return make_CanoUninitializedData( out_size( nout ).cano() );
    }

    Type    *type;
    IiKuSI64 size;
};

Variable make_UninitializedData( Type *type, const KuSI64 &size ) {
    UninitializedData *res = new UninitializedData( type, size );
    return { res->new_created_output() };
}
