#include "CanoUninitializedData.h"
#include "reuse_or_create.h"
#include "../TypeInSane.h"
#include "../Vm.h"

/**
*/
class CanoUninitializedData : public CanoInst {
public:
    CanoUninitializedData( const KcSI64 &size ) : size( size ) {
    }

    bool same( const KcSI64 &size ) const {
        return ::always_true( this->size == size );
    }

    virtual void write_dot( std::ostream &os, TypeInSane *type ) const override {
        os << "UD";
    }

    virtual KcSI64 length() const override {
        return size;
    }

    virtual void attr_visitor( AttrVisitor &visitor ) const override {
        CANO_INST_ATTR_VISIT( size );
    }

    KcSI64 size;
};

static Vec<RcPtr<CanoUninitializedData>> cano_uninitialized_data;

RcPtr<CanoInst> make_CanoUninitializedData( const KcSI64 &size ) {
    if ( size.is_known() ) {
        if ( (SI64)cano_uninitialized_data.size() <= size.kv() )
            cano_uninitialized_data.resize( size.kv() + 1 );
        if ( ! cano_uninitialized_data[ size.kv() ] )
            cano_uninitialized_data[ size.kv() ] = new CanoUninitializedData( size );
        return cano_uninitialized_data[ size.kv() ];
    }
    return reuse_or_create<CanoUninitializedData>( size );
}
