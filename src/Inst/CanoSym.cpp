#include "CanoVal.h"
#include "../Vm.h"

/***/
class CanoSym : public CanoInst {
public:
    CanoSym( const String &name, const KcSI64 &size ) : name( name ), size( size ) {
    }

    virtual void write_dot( std::ostream &os, TypeInSane *type ) const override {
        os << name;
    }

    virtual void attr_visitor( AttrVisitor &visitor ) const override {
        CANO_INST_ATTR_VISIT( size );
    }

    virtual KcSI64 length() const override {
        return size;
    }

    String name;
    KcSI64 size;
};

CanoInst *make_CanoSym( const String &name, const KcSI64 &size ) {
    return new CanoSym( name, size );
}
