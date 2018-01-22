#include "../Codegen/Codegen.h"
#include "../System/BoolVec.h"
#include "../Type.h"
#include "../Vm.h"

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
        //            if ( std::function<void(const PI8 *)> assign = children[ 0 ].inst->get_assign_func( children[ 0 ].nout, dst_off, len ) ) {
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

        //        if ( write_ssp_rec( ss, cg, dst_off, children[ 0 ].type, "" ) )
        //            return;
        //        ss << "memcpy_bits(...);";
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "Memcpy";
    }

    virtual void get_bytes( int nout, void *dst, int beg_dst, int beg_src, int len, void *msk ) const override {
        TODO;
        //        // we have to get data from...
        //        int len_ssp = children[ 1 ].type->size(), end_ssp = dst_off + len_ssp, end_src = beg_src + len;
        //        if ( beg_src < dst_off ) { // left part of children[ 0 ] and...
        //            if ( end_src <= dst_off ) { // => only children[ 0 ]
        //                children[ 0 ].inst->get_bytes( children[ 0 ].nout, dst, beg_dst, beg_src, len, msk );
        //            } else if ( end_src <= end_ssp ) {
        //                children[ 1 ].inst->get_bytes( children[ 1 ].nout, dst, beg_dst + dst_off - beg_src, 0, end_src - dst_off, msk );
        //                children[ 0 ].inst->get_bytes( children[ 0 ].nout, dst, beg_dst, beg_src, len, msk );
        //            } else {
        //                children[ 1 ].inst->get_bytes( children[ 1 ].nout, dst, beg_dst + dst_off - beg_src, 0, len_ssp, msk );
        //                children[ 0 ].inst->get_bytes( children[ 0 ].nout, dst, beg_dst, beg_src, len, msk );
        //            }
        //        } else if ( beg_src < end_ssp ) { // children[ 1 ] and...
        //            if ( end_src <= end_ssp ) {
        //                children[ 1 ].inst->get_bytes( children[ 1 ].nout, dst, beg_dst, beg_src - dst_off, len, msk );
        //            } else {
        //                children[ 1 ].inst->get_bytes( children[ 1 ].nout, dst, beg_dst, beg_src - dst_off, end_ssp - beg_src, msk );
        //                children[ 0 ].inst->get_bytes( children[ 0 ].nout, dst, beg_dst, beg_src, len, msk );
        //            }
        //        } else { // right part of children[ 0 ]
        //            children[ 0 ].inst->get_bytes( children[ 0 ].nout, dst, beg_dst, beg_src, len, msk );
        //        }
    }

    virtual int inp_corr( int nout ) const override {
        return nout == 0 ? 0 : -1;
    }

    virtual Type *out_type( int nout ) const override {
        return children[ 0 ].inst->out_type( children[ 0 ].nout );
    }

    bool write_ssp_rec( StreamSep &ss, Codegen &cg, int dst_offset, Type *dst_type, String m ) const {
        TODO;
        //        if ( dst_offset == 0 && dst_type == children[ 1 ].type ) {
        //            ss << cg.repr( children[ 0 ], PRIO_Member_selection ) << m << " = " << cg.repr( children[ 1 ], PRIO_Assignment, Codegen::WriteInlineCodeFlags::type_is_forced ) << ";";
        //            return true;
        //        }

        //        for( const TypeContent::Attribute *attr = dst_type->content.data.first_attribute; attr; attr = attr->next ) {
        //            if ( dst_offset < attr->off )
        //                return false;
        //            if ( write_ssp_rec( ss, cg, dst_offset - attr->off, attr->type, m + "." + attr->name ) )
        //                return true;
        //        }
        return false;
    }

    IiRessourceWithOffset dst;
    IiRessourceWithOffset src;
    IiKuSI64              len;
};

void memcpy( Ressource &dst, const Ressource &src, const KuSI64 &off_dst, const KuSI64 &off_src, const KuSI64 &len ) {
    Memcpy *res = new Memcpy;
    res->init_attr( res->dst, dst, off_dst );
    res->init_attr( res->src, src, off_src );
    res->init_attr( res->len, len          );

    // for each potentially modified/read ressource
    vm->ressource_map.get_potentially_linked_refs( dst, off_dst, len, res->add_wr_cb() );
    vm->ressource_map.get_potentially_linked_refs( src, off_src, len, res->add_rd_cb() );
}
