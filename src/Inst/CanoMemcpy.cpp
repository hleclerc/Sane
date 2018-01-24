#include "CanoVal.h"
#include "../Vm.h"

/***/
class CanoMemcpy : public CanoInst {
public:
    CanoMemcpy( const CanoVal &dst, const CanoVal &src, const CanoVal &off_dst, const CanoVal &off_src, const CanoVal &len ) {
        add_child( dst     );
        add_child( src     );
        add_child( off_dst );
        add_child( off_src );
        add_child( len     );
    }

    bool same( const CanoVal &dst, const CanoVal &src, const CanoVal &off_dst, const CanoVal &off_src, const CanoVal &len ) const {
        return ::always_true( dst     == children[ 0 ] ) &&
               ::always_true( src     == children[ 1 ] ) &&
               ::always_true( off_dst == children[ 2 ] ) &&
               ::always_true( off_src == children[ 3 ] ) &&
               ::always_true( len     == children[ 4 ] ) ;
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << "memcpy";
    }
};


RcPtr<CanoInst> make_CanoMemcpy( const CanoVal &dst, const CanoVal &src, const CanoVal &off_dst, const CanoVal &off_src, const CanoVal &len ) {
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
