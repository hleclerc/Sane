#include "System/BoolVec.h"
#include "Value.h"
#include "Type.h"

Value::Value( const Ressource &ressource, const KuSI64 &offset, const KuSI64 &length, Type *type ) : ressource( ressource ), offset( offset ), length( length ), type( type ) {
}

Value::Value( Inst *inst, int nout ) : Value( Ressource{ inst, nout }, 0, inst->created_outputs[ nout ].size, inst->created_outputs[ nout ].type ) {
}

Value::Value( const Ressource &ressource ) : Value( ressource.inst.ptr(), ressource.nout ) {
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

CanoVal Value::cano_val() const {
    return ressource.cano_val( offset.cano(), length.cano(), type );
}

bool Value::get_bytes( void *dst, PI32 beg_dst ) const {
    if ( length.is_known() ) {
        BoolVec msk( length.kv(), true );
        return get_bytes( dst, beg_dst, msk.data ) && msk.all_false();
    }
    return false;
}

bool Value::get_bytes( void *dst, PI32 beg_dst, void *msk ) const {
    return offset.is_known() && length.is_known() && ressource.get_bytes( dst, beg_dst, offset.kv(), length.kv(), msk );
}

bool Value::is_non_null() const {
    return ressource.inst->is_non_null( ressource.nout, offset, length, type );
}

bool Value::is_null() const {
    return ressource.inst->is_null( ressource.nout, offset, length, type );
}

