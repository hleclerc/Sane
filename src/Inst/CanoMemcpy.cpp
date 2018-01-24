#include "CanoVal.h"
#include "../Vm.h"

/***/
class CanoMemcpy : public CanoInst {
public:
    CanoMemcpy( const CanoVal &dst, const CanoVal &src, const KcSI64 &off_dst, const KcSI64 &off_src, const KcSI64 &len ) : off_dst( off_dst ), off_src( off_src ),len( len ) {
        add_child( dst     );
        add_child( src     );
    }

    bool same( const CanoVal &dst, const CanoVal &src, const KcSI64 &off_dst, const KcSI64 &off_src, const KcSI64 &len ) const {
        return ::always_true( dst     == children[ 0 ] ) &&
               ::always_true( src     == children[ 1 ] ) &&
               ::always_true( off_dst == this->off_dst ) &&
               ::always_true( off_src == this->off_src ) &&
               ::always_true( len     == this->len     ) ;
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << "memcpy";
    }

    KcSI64 off_dst;
    KcSI64 off_src;
    KcSI64 len;
};


RcPtr<CanoInst> make_CanoMemcpy( const CanoVal &dst, const CanoVal &src, const KcSI64 &off_dst, const KcSI64 &off_src, const KcSI64 &len ) {
    // dst is totally replaced by src
    if ( always_false( off_dst ) && always_false( off_src ) )
        return src.inst;

    // zero length
    if ( always_false( len ) )
        return dst.inst;

    // dst or src are memcpy
    CanoMemcpy *m_dst = dynamic_cast<CanoMemcpy *>( dst.inst.ptr() );
    CanoMemcpy *m_src = dynamic_cast<CanoMemcpy *>( src.inst.ptr() );
    if ( m_dst || m_src ) {
        TODO;
    }


    if ( CanoInst *p = common_parent<CanoMemcpy>( dst.inst.ptr(), dst, src, off_dst, off_src, len ) )
        return p;
    return new CanoMemcpy( dst, src, off_dst, off_src, len );
}
