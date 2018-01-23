#include "../Codegen/Codegen.h"
#include "../System/BoolVec.h"
#include "../Type.h"
#include "../Vm.h"

#include "CanoMemcpy.h"
#include "Clonable.h"
#include "Memcpy.h"


/**
*/
class Memcpy : public Clonable<Memcpy,Inst> {
public:
    Memcpy() {
    }

    Memcpy( AttrClone, const Memcpy *a ) {
        TODO;
    }

    virtual bool expects_a_reg_at( int ninp ) const override {
        return ninp == 0;
    }

    virtual bool simplify_for_cg( Codegen &cg ) override {
        //    // we can replace memcpy( ... ) by children[ 1 ] ?
        //    if ( children[ 0 ].type->size() == children[ 1 ].type->size() &&
        //         children[ 0 ].inst->has_been_refed( children[ 0 ].nout ) == false &&
        //         children[ 1 ].inst->has_been_refed( children[ 1 ].nout ) == false &&
        //         children[ 1 ].can_take_creation_constraints( children[ 0 ].creation_constraints() ) ) {
        //    }

        // if children[ 1 ] data is known and children[ 0 ] can be modified accordingly
        TODO;
        //        int len = children[ 1 ].type->size();
        //        BoolVec dst( len );
        //        if ( children[ 1 ].get_bytes( dst.data, 0, 0, len ) ) {
        //            if ( std::function<void(const PI8 *)> assign = children[ 0 ].inst->get_assign_func( children[ 0 ].nout, dst.offset.kv, len ) ) {
        //                replace_by( 0, children[ 0 ].inst.ptr(), children[ 0 ].nout );
        //                assign( dst.data );
        //                return true;
        //            }
        //        }

        return false;
    }

    virtual bool can_be_inlined() const override {
        return false;
    }

    virtual void write_code( StreamSep &ss, Codegen &cg ) override {
        TODO;
        //        cd.out_regs = { children[ 0 ].inst->cd.out_regs[ children[ 0 ].nout ] };

        //        if ( write_ssp_rec( ss, cg, dst.offset.kv, children[ 0 ].type, "" ) )
        //            return;
        //        ss << "memcpy_bits(...);";
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "Memcpy";
    }

    virtual bool get_bytes( int nout, void *w_dst, int beg_w_dst, int beg_w_src, int w_len, void *msk ) const override {
        if ( nout )
            return false;
        // look if we can get something from children[ 1 ]
        if ( dst.offset.is_known() && src.offset.is_known() && len.is_known() ) {
            int beg_l_src = std::max( beg_w_src, int( dst.offset.kv ) );
            int end_l_src = std::min( beg_w_src + w_len, int( dst.offset.kv + len.kv ) );
            int beg_n_dst = beg_l_src - dst.offset.kv;
            int beg_n_src = beg_l_src - dst.offset.kv + src.offset.kv;
            int n_len = end_l_src - beg_l_src;
            if ( beg_l_src < end_l_src &&
                 memcmp_bit( msk, beg_n_dst, n_len, false ) &&
                 children[ 1 ].inst->get_bytes( children[ 1 ].nout, w_dst, beg_n_dst, beg_n_src, n_len, msk ) == false )
                return false;
        }
        return memcmp_bit( msk, beg_w_dst, w_len, false ) ?
            children[ 0 ].inst->get_bytes( children[ 0 ].nout, w_dst, beg_w_dst, beg_w_src, w_len, msk ) :
            true;
    }

    virtual int inp_corr( int nout ) const override {
        return nout == 0 ? 0 : -1;
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        return make_CanoMemcpy( cano_repr( dst.ressource ), cano_repr( src.ressource ), cano_repr( dst.offset ), cano_repr( src.offset ), cano_repr( len ) );
    }

//    bool write_ssp_rec( StreamSep &ss, Codegen &cg, int dst.offset.kvset, Type *dst_type, String m ) const {
//        TODO;
//        //        if ( dst.offset.kvset == 0 && dst_type == children[ 1 ].type ) {
//        //            ss << cg.repr( children[ 0 ], PRIO_Member_selection ) << m << " = " << cg.repr( children[ 1 ], PRIO_Assignment, Codegen::WriteInlineCodeFlags::type_is_forced ) << ";";
//        //            return true;
//        //        }

//        //        for( const TypeContent::Attribute *attr = dst_type->content.data.first_attribute; attr; attr = attr->next ) {
//        //            if ( dst.offset.kvset < attr->off )
//        //                return false;
//        //            if ( write_ssp_rec( ss, cg, dst.offset.kvset - attr->off, attr->type, m + "." + attr->name ) )
//        //                return true;
//        //        }
//        return false;
//    }

    IiRessourceWithOffset dst;
    IiRessourceWithOffset src;
    IiKuSI64              len;
};

void make_Memcpy( Ref *dst, Ref *src, const KuSI64 &off_dst, const KuSI64 &off_src, const KuSI64 &len ) {
    Memcpy *res = new Memcpy;
    res->init_attr( res->dst, dst->current, off_dst );
    res->init_attr( res->src, src->current, off_src );
    res->init_attr( res->len, len                   );

    // for each potentially modified/read ressource
    vm->ressource_map.get_linked_refs( dst, off_dst, len, res->add_wr_cb() );
    vm->ressource_map.get_linked_refs( src, off_src, len, res->add_rd_cb() );
}
