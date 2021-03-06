#include "../System/byte_swaped.h"
#include "../System/BoolVec.h"
#include "../System/Memcpy.h"
#include "../TypeInSane.h"
#include "../Vm.h"
#include "CanoCst.h"

/**
*/
class CanoCst : public CanoInst {
public:
    CanoCst( const void *ptr, int len ) : content( len ) {
        memcpy_bit( content.data, ptr, len );
    }

    virtual void write_dot( std::ostream &os, TypeInSane *type ) const override {
        if ( type )
            type->write_cst( os, content.data );
        else
            os << content;
    }

    virtual void *known_value() const override {
        return content.data;
    }

    virtual KcSI64 length() const override {
        return content.size;
    }

    virtual bool always_false( TypeInSane *type ) const override {
        return content.all_false();
    }

    virtual bool always_true( TypeInSane *type ) const override {
        return ! content.all_false();
    }

    virtual SI64 get_SI64_value( TypeInSane *orig ) const override {
        return orig->convert_cst_to_SI64( content.data );
    }

    virtual RcPtr<CanoInst> simp_CanoConv( TypeInSane *orig, TypeInSane *target ) override {
        if ( RcPtr<CanoInst> res = orig->convert_cano_cst( content.data, target ) )
            return res;
        return 0;
    }

    virtual void attr_visitor( AttrVisitor &visitor ) const override {
    }

    virtual RcPtr<CanoInst> sub_part( const KcSI64 &off, const KcSI64 &len ) {
        if ( ::always_true( len == content.size ) )
            return this;
        if ( off.is_known() && len.is_known() ) {
            BoolVec new_content( len.kv() );
            memcpy_bit( new_content.data, 0, content.data, off.kv(), len.kv() );
            return make_CanoCst( new_content.data, len.kv() );
        }
        P( content, content.size, off, len );
        TODO;
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

static std::map<BoolVec,RcPtr<CanoCst>> map_gen_cst;

RcPtr<CanoInst> make_gen_CanoCst( const void *ptr, int len ) {
    BoolVec bv( Reference(), const_cast<void *>( ptr ), len );

    auto iter = map_gen_cst.find( bv );
    if ( iter == map_gen_cst.end() )
        iter = map_gen_cst.emplace_hint( iter, bv, new CanoCst( ptr, len ) );
    return iter->second;
}

template<class T>
RcPtr<CanoInst> make_CanoCst_kv( std::vector<RcPtr<CanoCst>> &map, T val, int length ) {
    constexpr int ws = 512;
    constexpr int of = std::is_signed<T>::value ? 64 : 0;
    T o_val = val + of;

    if ( o_val >= 0 && o_val < ws ) {
        if ( map.empty() ) {
            map.resize( ws );
            if ( sizeof( T ) > 1 && vm->reverse_endianness ) {
                for( T i = 0; i < ws; ++i ) {
                    T c = byte_swaped( i ) - of;
                    map[ i ] = new CanoCst( &c, length );
                }
            } else {
                for( T i = 0; i < ws; ++i ) {
                    T c = i - of;
                    map[ i ] =  new CanoCst( &c, length );
                }
            }
        }
        return map[ o_val ];
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
