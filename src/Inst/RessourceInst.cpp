#include "RessourceInst.h"
#include "Clonable.h"
#include "../Vm.h"

/**
*/
class RessourceInst : public Clonable<RessourceInst> {
public:
    RessourceInst( const char *txt) : txt( txt ) {}
    RessourceInst( AttrClone, const RessourceInst *orig ) : txt( orig->txt ) {}

    virtual void write_code( StreamSep &ss, Codegen &cg ) override {
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << txt;
    }

    virtual CanoVal cano_repr( int nout, const CanoVal &offset, const CanoVal &length, Type *type ) const {
        TODO;
        return {};
    }

    const char *txt;
};

Variable make_RessourceInst( const char *txt ) {
    RessourceInst *res = new RessourceInst( txt );
    return { res->new_created_output( vm->type_Ressource, 0 ), 0, 0, vm->type_Ressource };
}