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
    UninitializedData() {
    }

    UninitializedData( AttrClone, const UninitializedData *UninitializedData ) {
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
};

Variable make_UninitializedData( Type *type, const KuSI64 &size ) {
    UninitializedData *res = new UninitializedData;
    return { res->new_created_output( type, size ) };
}
