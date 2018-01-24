#include "../System/byte_swaped.h"
#include "../System/BoolVec.h"
#include "../System/Memcpy.h"
#include "CanoCst.h"
#include "../Type.h"
#include "../Vm.h"

/**
*/
class CanoCst : public CanoInst {
public:
    CanoCst( const void *ptr, int len ) : content( len ) {
        memcpy_bit( content.data, ptr, len );
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        if ( type )
            type->write_cst( os, content.data );
        else
            os << content;
    }

    virtual bool known_value() const override {
        return true;
    }

    virtual bool always_false( Type *type ) const override {
        return content.all_false();
    }

    virtual bool always_true( Type *type ) const override {
        return ! content.all_false();
    }

    virtual SI64 get_SI64_value( Type *orig ) const override {
        return orig->convert_cst_to_SI64( content.data );
    }

    virtual RcPtr<CanoInst> simp_CanoConv( Type *orig, Type *target ) override {
        if ( RcPtr<CanoInst> res = orig->convert_cano_cst( content.data, target ) )
            return res;
        return 0;
    }

    BoolVec content;
};

static std::vector<RcPtr<CanoCst>> map_64;
static std::vector<RcPtr<CanoCst>> map_32;
static std::vector<RcPtr<CanoCst>> map_16;
static std::vector<RcPtr<CanoCst>> map_8 ;
static RcPtr<CanoCst> cst_false;
static RcPtr<CanoCst> cst_true;

RcPtr<CanoInst> make_gen_CanoCst( const void *content, int length ) {
    TODO;
    return 0;
}

template<class T>
RcPtr<CanoInst> make_CanoCst_kv( std::vector<RcPtr<CanoCst>> &map, T val, int length ) {
    constexpr int ws = 512;

    if ( val >= 0 && val < ws ) {
        if ( map.empty() ) {
            map.resize( ws );
            if ( sizeof( T ) > 1 && vm->reverse_endianness ) {
                for( T i = 0; i < ws; ++i ) {
                    T c = byte_swaped( i );
                    map[ i ] = new CanoCst( &c, length );
                }
            } else {
                for( T i = 0; i < ws; ++i ) {
                    map[ i ] =  new CanoCst( &i, length );
                }
            }
        }
        return map[ val ];
    }
    return make_gen_CanoCst( &val, length );
}

RcPtr<CanoInst> make_CanoCst( const void *content, int length ) {
    if ( length == 64 ) {
        SI64 val = *reinterpret_cast<const SI64 *>( content );
        return make_cano_inst( vm->reverse_endianness ? byte_swaped( val ) : val );
    }
    if ( length == 32 ) {
        SI32 val = *reinterpret_cast<const SI32 *>( content );
        return make_cano_inst( vm->reverse_endianness ? byte_swaped( val ) : val );
    }
    if ( length == 16 ) {
        SI16 val = *reinterpret_cast<const SI16 *>( content );
        return make_cano_inst( vm->reverse_endianness ? byte_swaped( val ) : val );
    }
    if ( length == 8 ) {
        SI8 val = *reinterpret_cast<const SI8 *>( content );
        return make_cano_inst( val );
    }
    return make_gen_CanoCst( content, length );
}

RcPtr<CanoInst> make_cano_inst( PI8  val ) { return make_CanoCst_kv<PI8 >( map_8 , val, 8  ); }
RcPtr<CanoInst> make_cano_inst( PI16 val ) { return make_CanoCst_kv<PI16>( map_16, val, 16 ); }
RcPtr<CanoInst> make_cano_inst( PI32 val ) { return make_CanoCst_kv<PI32>( map_32, val, 32 ); }
RcPtr<CanoInst> make_cano_inst( PI64 val ) { return make_CanoCst_kv<PI64>( map_64, val, 64 ); }
RcPtr<CanoInst> make_cano_inst( SI8  val ) { return make_CanoCst_kv<SI8 >( map_8 , val, 8  ); }
RcPtr<CanoInst> make_cano_inst( SI16 val ) { return make_CanoCst_kv<SI16>( map_16, val, 16 ); }
RcPtr<CanoInst> make_cano_inst( SI32 val ) { return make_CanoCst_kv<SI32>( map_32, val, 32 ); }
RcPtr<CanoInst> make_cano_inst( SI64 val ) { return make_CanoCst_kv<SI64>( map_64, val, 64 ); }

CanoVal make_cano_val( PI8  val ) { return { make_cano_inst( val ), vm->type_PI8  }; }
CanoVal make_cano_val( PI16 val ) { return { make_cano_inst( val ), vm->type_PI16 }; }
CanoVal make_cano_val( PI32 val ) { return { make_cano_inst( val ), vm->type_PI32 }; }
CanoVal make_cano_val( PI64 val ) { return { make_cano_inst( val ), vm->type_PI64 }; }
CanoVal make_cano_val( SI8  val ) { return { make_cano_inst( val ), vm->type_SI8  }; }
CanoVal make_cano_val( SI16 val ) { return { make_cano_inst( val ), vm->type_SI16 }; }
CanoVal make_cano_val( SI32 val ) { return { make_cano_inst( val ), vm->type_SI32 }; }
CanoVal make_cano_val( SI64 val ) { return { make_cano_inst( val ), vm->type_SI64 }; }

RcPtr<CanoInst> make_cano_inst( Bool val ) {
    if ( val ) {
        if ( ! cst_true )
            cst_true = new CanoCst( &val, 1 );
        return cst_true;
    }
    if ( ! cst_false )
        cst_false = new CanoCst( &val, 1 );
    return cst_false;
}

CanoVal make_cano_val( Bool val ) {
    return { make_cano_inst( val ), vm->type_Bool };
}
