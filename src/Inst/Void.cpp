#include "../Type.h"
#include "../Vm.h"
#include "Void.h"

/**
*/
class Void : public Inst {
public:
    Void( Type *type ) : type( type ) {
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "void";
    }

    virtual Type *created_out_type( int nout ) const override {
        return type;
    }

    Type *type;
};


Variable make_Void( Type *type ) {
    Void *res = new Void( type );
    return { res->new_created_output() };
}

Variable make_Void() {
    return make_Void( vm->type_Void );
}

