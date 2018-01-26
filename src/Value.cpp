#include "System/BoolVec.h"
#include "Value.h"
#include "Type.h"

Value::Value( const Ressource &ressource, const KuSI64 &offset, const KuSI64 &length, Type *type ) : ressource( ressource ), offset( offset ), length( length ), type( type ) {
}

Value::Value( Inst *inst, int nout ) : Value( Ressource{ inst, nout }, 0, inst->out_size( nout ), inst->out_type( nout ) ) {
}

Value::Value( const Ressource &ressource ) : Value( ressource.inst.ptr(), ressource.nout ) {
}

Value::Value( const Value &that ) : ressource( that.ressource ), offset( that.offset ), length( that.length ), type( that.type ) {
}

Value &Value::operator=( const Value &that ) {
    ressource = that.ressource;
    offset    = that.offset;
    length    = that.length;
    type      = that.type;
    return *this;
}

bool Value::operator<( const Value &that ) const {
    KuSI64::ShallowCmp o0{ offset }, o1{ that.offset };
    KuSI64::ShallowCmp l0{ length }, l1{ that.length };
    return std::tie( ressource, o0, l0, type ) < std::tie( that.ressource, o1, l1, that.type );
}

bool Value::operator==( const Value &that ) const {
    KuSI64::ShallowCmp o0{ offset }, o1{ that.offset };
    KuSI64::ShallowCmp l0{ length }, l1{ that.length };
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
