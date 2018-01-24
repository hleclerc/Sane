#include "CanoConv.h"
#include "CanoVal.h"
#include "../Type.h"
#include "../Vm.h"

/***/
class CanoConv : public CanoInst {
public:
    CanoConv( const CanoVal &val, Type *type ) : type( type ) {
        add_child( val );
    }

    bool same( const CanoVal &val, Type *type ) const {
        return ::always_true( val == children[ 0 ] ) && this->type == type;
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << "(" << *type << ")";
    }

    Type *type;
};

CanoVal make_CanoConv( const CanoVal &val, Type *type ) {
    if ( val.type == type )
        return val;

    if ( RcPtr<CanoInst> res = val.inst->simp_CanoConv( val.type, type ) )
        return { res, type };

    if ( CanoInst *p = common_parent<CanoConv>( val.inst.ptr(), val, type ) )
        return { p, type };
    return { new CanoConv( val, type ), type };
}
