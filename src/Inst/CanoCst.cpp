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

    BoolVec content;
};

static std::vector<RcPtr<CanoCst>> map_64;
static std::vector<RcPtr<CanoCst>> map_32;
static RcPtr<CanoCst> cst_false;
static RcPtr<CanoCst> cst_true;

CanoVal make_gen_CanoCst( const void *content, int length ) {
    TODO;
    return {};
}

template<class T>
CanoVal make_CanoCst_kv( std::vector<RcPtr<CanoCst>> &map, T val, int length, Type *type ) {
    constexpr int ws = 512;

    if ( val >= 0 && val < ws ) {
        if ( map.empty() ) {
            map.resize( ws );
            if ( vm->reverse_endianness ) {
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
        return { map[ val ], type };
    }
    return make_gen_CanoCst( &val, length );
}

CanoVal make_CanoCst( const void *content, int length ) {
    if ( length == 64 ) {
        SI64 val = *reinterpret_cast<const SI64 *>( content );
        return make_CanoCst( vm->reverse_endianness ? byte_swaped( val ) : val );
    }
    if ( length == 32 ) {
        SI32 val = *reinterpret_cast<const SI32 *>( content );
        return make_CanoCst( vm->reverse_endianness ? byte_swaped( val ) : val );
    }
    return make_gen_CanoCst( content, length );
}

CanoVal make_CanoCst( SI64 val ) {
    return make_CanoCst_kv<SI64>( map_64, val, 64, vm->type_SI64 );
}

CanoVal make_CanoCst( SI32 val ) {
    return make_CanoCst_kv<SI32>( map_32, val, 32, vm->type_SI32 );
}


CanoVal make_CanoCst( Bool val ) {
    if ( val ) {
        if ( ! cst_true )
            cst_true = new CanoCst( &val, 1 );
        return { cst_true, vm->type_Bool };
    }
    if ( ! cst_false )
        cst_false = new CanoCst( &val, 1 );
    return { cst_false, vm->type_Bool };
}
