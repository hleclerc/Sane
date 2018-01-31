#include "reuse_or_create.h"
#include "CanoVal.h"
#include "../Vm.h"

/***/
class CanoMemcpy : public CanoInst {
public:
    struct Sp {
        RcPtr<CanoInst> src;
        KcSI64          off; ///< offset in dst
    };

    CanoMemcpy( const CanoVal &base, const Vec<Sp> &sub_parts ) : base( base ), sub_parts( sub_parts ) {
    }

    bool same( const CanoVal &base, const Vec<Sp> &sub_parts ) const {
        if ( ::always_true( this->base == base ) == false )
            return false;
        if ( this->sub_parts.size() != sub_parts.size() )
            return false;
        for( size_t i = 0; i < sub_parts.size(); ++i )
            if (                this->sub_parts[ i ].src != sub_parts[ i ].src || // TODO: more general equ
                 ::always_true( this->sub_parts[ i ].off == sub_parts[ i ].off ) == false )
                return false;
        return true;
    }

    virtual void write_dot( std::ostream &os, TypeInSane *type ) const override {
        os << "memcpy";
    }

    virtual void attr_visitor( AttrVisitor &visitor ) const override {
        CANO_INST_ATTR_VISIT( base );
        for( const Sp &sp : sub_parts ) {
            CANO_INST_ATTR_VISIT( sp.src );
            CANO_INST_ATTR_VISIT( sp.off );
        }
    }

    virtual KcSI64 length() const override {
        return base.inst->length();
    }


    CanoVal base;
    Vec<Sp> sub_parts; ///< ordered by (inst *,offset)
};


RcPtr<CanoInst> make_CanoMemcpy( const CanoVal &dst, const RcPtr<CanoInst> &src, const KcSI64 &off ) {
    // if dst is totally replaced by src
    if ( always_true( src->length() == dst.length() ) )
        return src;

    // zero length
    if ( always_false( src->length() ) )
        return dst.inst;

    // construction of an ordered list of subpart
    CanoVal base;
    Vec<CanoMemcpy::Sp> sub_parts;
    if ( CanoMemcpy *m_dst = dynamic_cast<CanoMemcpy *>( dst.inst.ptr() ) ) {
        sub_parts = m_dst->sub_parts;
        base = m_dst->base;
    } else {
        base = dst;
    }

    if ( CanoMemcpy *m_src = dynamic_cast<CanoMemcpy *>( src.ptr() ) ) {
        sub_parts << CanoMemcpy::Sp{ m_src->base.inst, off };
        for( CanoMemcpy::Sp &sp : m_src->sub_parts )
            sub_parts << CanoMemcpy::Sp{ sp.src, off + sp.off };
    } else
        sub_parts << CanoMemcpy::Sp{ src, off };

    return reuse_or_create<CanoMemcpy>( base, sub_parts );
}
