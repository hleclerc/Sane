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
    UninitializedData( Type *type, const KuSI64 &size, const KuSI64 &alig ) : type( type ) {
        init_attr( this->size, size );
        init_attr( this->alig, alig );
    }

    UninitializedData( AttrClone, const UninitializedData *UninitializedData ) {
    }

    virtual Type *created_out_type( int nout ) const override {
        return type;
    }

    virtual KuSI64 created_out_size( int nout ) const override {
        return to_KuSI64( size );
    }

    virtual KuSI64 created_out_alig( int nout ) const override {
        return to_KuSI64( alig );
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
    IiKuSI64 alig;
};

Variable make_UninitializedData( Type *type, const KuSI64 &size, const KuSI64 &alig ) {
    UninitializedData *res = new UninitializedData( type, size, alig );
    return { res->new_created_output() };
}
