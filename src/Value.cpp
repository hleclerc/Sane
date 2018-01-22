#include "System/BoolVec.h"
#include "Value.h"
#include "Type.h"

Value::Value( const Ressource &ressource, const KuSI64 &offset, const KuSI64 &length, Type *type ) : ressource( ressource ), offset( offset ), length( length ), type( type ) {
}

Value::Value( Inst *inst, int nout ) : Value( Ressource{ inst, nout }, 0, inst->out_size( nout ), inst->out_type( nout ) ) {
}

Value::Value( const Ressource &ressource ) : Value( ressource, 0, ressource.size(), ressource.type() ) {
}

Value::Value( const Value &value ) : ressource( value.ressource ), offset( value.offset ), type( value.type ) {
}

Value &Value::operator=( const Value &value ) {
    ressource = value.ressource;
    offset    = value.offset;
    type      = value.type;
    return *this;
}

bool Value::operator<( const Value &that ) const {
    KuSI64::ShallowCmp o0{ offset }, l0{ length }, o1{ that.offset }, l1{ that.length };
    return std::tie( ressource, o0, l0, type ) < std::tie( that.ressource, o1, l1, that.type );
}

bool Value::operator==( const Value &that ) const {
    KuSI64::ShallowCmp o0{ offset }, l0{ length }, o1{ that.offset }, l1{ that.length };
    return std::tie( ressource, o0, l0, type ) == std::tie( that.ressource, o1, l1, that.type );
}

void Value::write_to_stream( std::ostream &os ) const {
    if ( ressource.inst )
        ressource.inst->write_to_stream( os, ressource.nout, type, offset.is_known() ? offset.kv() : -1 );
    else
        os << "NULL";
}

bool Value::get_bytes( void *dst, PI32 beg_dst ) const {
    if ( length.is_known() ) {
        BoolVec msk( length.kv(), true );
        get_bytes( dst, beg_dst, msk.data );
        return msk.all_false();
    }
    return false;
}

void Value::get_bytes( void *dst, PI32 beg_dst, void *msk ) const {
    if ( offset.is_known() && length.is_known() )
        ressource.get_bytes( dst, beg_dst, offset.kv(), length.kv(), msk );
}

bool Value::is_equal( const Value &that ) const {
    //    if ( type == that.type ) {
    //        BoolVec bv_this( this->type->size() );
    //        BoolVec bv_that( that. type->size() );
    //        if ( this->get_bytes( bv_this.data, 0, 0, this->type->size() ) &&
    //             that. get_bytes( bv_that.data, 0, 0, that. type->size() ) )
    //            return bv_this == bv_that;
    //        return false;
    //    }

    TODO;
    return false;
}

bool Value::is_non_null() const {
    return ressource.inst->is_non_null( ressource.nout, offset, length, type );
}

bool Value::is_null() const {
    return ressource.inst->is_null( ressource.nout, offset, length, type );
}

bool Value::is_not_equal( const Value &that ) const {
    //    if ( type == that.type ) {
    //        BoolVec bv_this( this->type->size() );
    //        BoolVec bv_that( that. type->size() );
    //        if ( this->get_bytes( bv_this.data, 0, 0, this->type->size() ) &&
    //             that. get_bytes( bv_that.data, 0, 0, that. type->size() ) )
    //            return bv_this != bv_that;
    //        return false;
    //    }

    TODO;
    return false;
}

