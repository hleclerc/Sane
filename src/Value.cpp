#include "System/BoolVec.h"
#include "Value.h"
#include "Type.h"

Value::Value( const Ressource &ressource, const KuSI64 &offset, Type *type ) : ressource( ressource ), offset( offset ), type( type ) {
}

Value::Value( Inst *inst, int nout ) : Value( Ressource{ inst, nout }, 0, inst->out_type( nout ) ) {
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
    KuSI64::ShallowCmp o0{ offset }, o1{ that.offset };
    return std::tie( ressource, o0, type ) < std::tie( that.ressource, o1, that.type );
}

bool Value::operator==( const Value &that ) const {
    KuSI64::ShallowCmp o0{ offset }, o1{ that.offset };
    return std::tie( ressource, o0, type ) == std::tie( that.ressource, o1, that.type );
}

void Value::write_to_stream( std::ostream &os ) const {
    if ( ressource.inst )
        ressource.inst->write_to_stream( os, ressource.nout, type, offset.is_known() ? offset.kv() : -1 );
    else
        os << "NULL";
}

CanoVal Value::cano_val() const {
    return ressource.cano_val( offset.cano(), size().cano(), type );
}

KuSI64 Value::size() const {
    if ( type->kv_size() >= 0 )
        return type->kv_size();
    // -> create a temporary artificial reference
    TODO;
    return 0;
}

