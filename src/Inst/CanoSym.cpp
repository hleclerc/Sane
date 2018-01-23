#include "CanoVal.h"
#include "../Vm.h"

/***/
class CanoSym : public CanoInst {
public:
    CanoSym( const String &name ) : name( name ) {
    }

    virtual void write_dot( std::ostream &os, Type *type ) const override {
        os << name;
    }

    String name;
};

CanoVal make_CanoSym( const String &name, Type *type ) {
    return { new CanoSym( name ), type };
}
