#include "../Type.h"
#include "../Vm.h"
#include "Void.h"

/**
*/
class Void : public Inst {
public:
    virtual void write_dot( std::ostream &os ) const override;
};


void Void::write_dot( std::ostream &os ) const {
    os << "void";
}

Variable make_Void( Type *type ) {
    Void *res = new Void;
    return { res->new_created_output( type, type->content.data.size ) };
}

Variable make_Void() {
    return make_Void( vm->type_Void );
}

