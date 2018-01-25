#include "reuse_or_create.h"
#include "CanoConv.h"
#include "CanoVal.h"
#include "../Type.h"
#include "../Vm.h"

/***/
class CanoConv : public CanoInst {
public:
    CanoConv( const CanoVal &val, Type *type ) : val( val ), type( type ) {
    }

    bool same( const CanoVal &val, Type *type ) const {
        return ::always_true( this->val == val ) && this->type == type;
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << "conv";
    }

    virtual void attr_visitor( AttrVisitor &visitor ) const {
        CANO_INST_ATTR_VISIT( val  );
        CANO_INST_ATTR_VISIT( type );
    }

    virtual KcSI64 length() const {
        return type->content.data.kv_size;
    }

    CanoVal val;
    Type   *type;
};

CanoVal make_CanoConv( const CanoVal &val, Type *type ) {
    if ( val.type == type )
        return val;

    if ( RcPtr<CanoInst> res = val.inst->simp_CanoConv( val.type, type ) )
        return { res, type };

    return { reuse_or_create<CanoConv>( val, type ), type };
}
