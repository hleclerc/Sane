#include "../System/byte_swaped.h"
#include "../System/Memcpy.h"
#include "../Codegen/Codegen.h"
//#include "../Type.h"
#include "../KuSI64.h"
#include "../Vm.h"
#include "Cst.h"

Cst::Cst( Type *type, int size, void *val, void *kno ) : type( type ), val( size ), kno( size ) {
    if ( val )
        memcpy( this->val.data, val, ( size + 7 ) / 8 );
    else
        this->val.set( false );
    if ( kno )
        memcpy( this->kno.data, kno, ( size + 7 ) / 8 );
    else
        this->kno.set( bool( val ) );
}

Cst::Cst( AttrClone, const Cst *cst ) : type( cst->type ), val( cst->val ), kno( cst->kno ) {
}

void Cst::write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) {
    //    if ( ! kno.all_false() )
    //        type->write_cst( ss.stream, val.data, 0, false );
    //    else
    //        ss << "{}";
    TODO;
}

void Cst::write_to_stream( std::ostream &os, SI32 nout, Type *type, int offset ) const {
    //    if ( type )
    //        type->write_cst( os, val.data + offset / 8, offset % 8 );
    //    else
    //        this->type->write_cst( os, val.data, 0 );
    TODO;
}

Inst::AssFunc Cst::get_assign_func( int nout, int off, int len ) {
    return [this,off,len]( const PI8 *data ) {
        memcpy_bit( val.data, off, data, 0, len );
        memset_bit( kno.data, off, true, len );
    };
}

void Cst::write_dot( std::ostream &os ) const {
    TODO;
    //    type->write_cst( os, val.data, 0 );
}

void Cst::get_bytes( int nout, void *dst, int beg_dst, int beg_src, int len, void *msk ) const {
    if ( PI32( beg_src ) >= val.size )
        return;
    if ( PI32( beg_src + len ) > val.size )
        len = val.size - beg_src;
    memcpy_bit( dst, beg_dst, val.data, beg_src, len, msk );
    memset_bit( msk, beg_dst, false, len );
}

Type *Cst::out_type( int nout ) const {
    return type;
}

KuSI64 Cst::out_size( int nout ) const {
    return val.size;
}

int Cst::nb_outputs() const {
    return 1;
}

Value make_Cst_PI64( PI64 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return new Cst( vm->type_PI64, 64, &val ); }
Value make_Cst_SI64( SI64 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return new Cst( vm->type_SI64, 64, &val ); }
Value make_Cst_PI32( PI32 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return new Cst( vm->type_PI32, 32, &val ); }
Value make_Cst_SI32( SI32 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return new Cst( vm->type_SI32, 32, &val ); }
Value make_Cst_PI16( PI16 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return new Cst( vm->type_PI16, 16, &val ); }
Value make_Cst_SI16( SI16 val ) { if ( vm->reverse_endianness ) val = byte_swaped( val ); return new Cst( vm->type_SI16, 16, &val ); }
Value make_Cst_PI8 ( PI8  val ) {                                                         return new Cst( vm->type_PI8 ,  8, &val ); }
Value make_Cst_SI8 ( SI8  val ) {                                                         return new Cst( vm->type_SI8 ,  8, &val ); }
Value make_Cst_Bool( Bool val ) {                                                         return new Cst( vm->type_Bool,  1, &val ); }

// Value make_Cst( Type *type ) { return { new Cst( type, type->content.data.size ), type }; }

