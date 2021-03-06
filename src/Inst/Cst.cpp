#include "../System/byte_swaped.h"
#include "../System/BoolVec.h"
#include "../System/Memcpy.h"

#include "../Codegen/Codegen.h"

#include "../TypeInSane.h"
#include "../KuSI64.h"
#include "../Ref.h"
#include "../Vm.h"

#include "Clonable.h"
#include "CanoCst.h"
#include "Cst.h"

union U {
    PI64        v;
    const void *p;
};

/**
*/
class Cst : public Clonable<Cst,Inst> {
public:
    Cst( TypeInSane *type, int size, void *val = 0, void *kno = 0 ) : type( type ), val( size ), kno( size ) {
        if ( val )
            memcpy( this->val.data, val, ( size + 7 ) / 8 );
        else
            this->val.set( false );
        if ( kno )
            memcpy( this->kno.data, kno, ( size + 7 ) / 8 );
        else
            this->kno.set( bool( val ) );
    }

    Cst( AttrClone, const Cst *orig ) : type( orig->type ), val( orig->val ), kno( orig->kno ) {
    }

    virtual TypeInSane *created_out_type( int nout ) const override {
        return type;
    }

    virtual KuSI64 created_out_size( int nout ) const override {
        return val.size;
    }

    virtual void write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) override {
        if ( ! kno.all_false() )
            type->write_cst( ss.stream, val.data, 0, false );
        else
            ss << "{}";
    }

    virtual void write_to_stream( std::ostream &os, SI32 nout = -1, Type *type = 0, int offset = -1 ) const {
        if ( type )
            type->write_cst( os, val.data + offset / 8, offset % 8 );
        else
            this->type->write_cst( os, val.data, 0 );
    }

    virtual AssFunc get_assign_func( int nout, int off, int len ) override {
        return [this,off,len]( const PI8 *data ) {
            memcpy_bit( val.data, off, data, 0, len );
            memset_bit( kno.data, off, true, len );
        };
    }

    virtual void write_dot( std::ostream &os ) const override {
        type->write_cst( os, val.data, 0 );
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        return make_CanoCst( val.data, val.size );
    }


    TypeInSane *type;
    BoolVec     val;
    BoolVec     kno;
};

Variable make_Cst( TypeInSane *type, int size, void *val, void *kno ) {
    Cst *res = new Cst( type, size, val, kno );
    return { res->new_created_output(), 0, size, type };
}


Variable make_Cst_PI64( PI64 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return make_Cst( vm->type_PI64, 64, &val ); }
Variable make_Cst_SI64( SI64 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return make_Cst( vm->type_SI64, 64, &val ); }
Variable make_Cst_PI32( PI32 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return make_Cst( vm->type_PI32, 32, &val ); }
Variable make_Cst_SI32( SI32 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return make_Cst( vm->type_SI32, 32, &val ); }
Variable make_Cst_PI16( PI16 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return make_Cst( vm->type_PI16, 16, &val ); }
Variable make_Cst_SI16( SI16 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return make_Cst( vm->type_SI16, 16, &val ); }
Variable make_Cst_PI8 ( PI8  val ) {                                                         return make_Cst( vm->type_PI8 ,  8, &val ); }
Variable make_Cst_SI8 ( SI8  val ) {                                                         return make_Cst( vm->type_SI8 ,  8, &val ); }
Variable make_Cst_Bool( Bool val ) {                                                         return make_Cst( vm->type_Bool,  1, &val ); }


Variable make_Cst( PI64 val ) { return make_Cst_PI64( val ); }
Variable make_Cst( SI64 val ) { return make_Cst_SI64( val ); }
Variable make_Cst( PI32 val ) { return make_Cst_PI32( val ); }
Variable make_Cst( SI32 val ) { return make_Cst_SI32( val ); }
Variable make_Cst( PI16 val ) { return make_Cst_PI16( val ); }
Variable make_Cst( SI16 val ) { return make_Cst_SI16( val ); }
Variable make_Cst( PI8  val ) { return make_Cst_PI8 ( val ); }
Variable make_Cst( SI8  val ) { return make_Cst_SI8 ( val ); }
Variable make_Cst( Bool val ) { return make_Cst_Bool( val ); }

