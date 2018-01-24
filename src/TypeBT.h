#pragma once

#include "Inst/CanoCst.h"
#include "Type.h"
#include "Vm.h"

/**
*/
template<class T,bool reverse_endianness>
class TypeBT : Type {
public:
    TypeBT( const LString &name ) : Type( name ) {
    }

    virtual void write_cst( std::ostream &os, const PI8 *data, int offset_mod_8 = 0, bool always_add_braces = false ) const override {
        if ( always_add_braces )
            os << "{";

        if ( offset_mod_8 )
            TODO;

        T value = *reinterpret_cast<const T *>( data );
        if ( reverse_endianness )
            value = byte_swaped( value );

        os << value;

        if ( always_add_braces )
            os << "}";
    }

    virtual bool is_a_TypeBT() const override {
        return true;
    }

    virtual int is_signed() const override {
        return std::is_signed<T>::value;
    }

    virtual int mantissa_len() const override {
        if ( std::is_same<T,Bool>::value )
            return 1;
        if ( std::is_integral<T>::value )
            return 8 * sizeof( T ) - std::is_signed<T>::value;
        TODO;
        return -1;
    }

    virtual int exponent_len() const override {
        return -1;
    }

    virtual RcPtr<CanoInst> convert_cano_cst( const void *content, Type *target ) override {
        T value = *reinterpret_cast<const T *>( content );
        if ( reverse_endianness )
            value = byte_swaped( value );

        if ( target->is_a_TypeBT() ) {
            switch ( target->mantissa_len() ) {
            case 1 : return make_cano_inst( Bool( value ) );
            case 7 : return make_cano_inst( SI8 ( value ) );
            case 15: return make_cano_inst( SI16( value ) );
            case 31: return make_cano_inst( SI32( value ) );
            case 63: return make_cano_inst( SI64( value ) );
            case 8 : return make_cano_inst( PI8 ( value ) );
            case 16: return make_cano_inst( PI16( value ) );
            case 32: return make_cano_inst( PI32( value ) );
            case 64: return make_cano_inst( PI64( value ) );
            }
            TODO;
        }

        return 0;
    }

    virtual SI64 convert_cst_to_SI64( const void *content ) const {
        T value = *reinterpret_cast<const T *>( content );
        return reverse_endianness ? byte_swaped( value ) : value;
    }
};
