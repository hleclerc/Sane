#include "CanoVal.h"
#include "../Vm.h"

/***/
class CanoMemcpy : public CanoInst {
public:
    CanoMemcpy( const CanoVal &a, const CanoVal &b ) {
        add_child( a );
        add_child( b );
    }

    bool same( const CanoVal &a, const CanoVal &b ) const {
        return ::always_true( a == children[ 0 ] ) && ::always_true( b == children[ 1 ] );
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << "memcpy";
    }
};


RcPtr<CanoInst> make_CanoMemcpy( const RcPtr<CanoInst> &dst, const RcPtr<CanoInst> &src, const CanoVal &off_dst, const CanoVal &off_src, const CanoVal &len ) {
    if ( CanoInst *p = common_parent<CanoBinOp<T>>( dst.ptr(), dst, src, off_dst, off_src, len ) )
        return p;
    return new CanoMemcpy( a, b );
}
