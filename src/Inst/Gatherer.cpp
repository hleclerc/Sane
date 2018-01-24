#include "Gatherer.h"

/**
*/
class Gatherer : public Clonable<Gatherer> {
public:
    Gatherer( const Vec<Ressource> &children ) {
        for( const Ressource &ch : children )
            add_child( ch );
    }

    Gatherer( AttrClone, const Gatherer *orig ) {
    }

    virtual void write_dot ( std::ostream &os ) const override {
        os << "Gatherer";
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        TODO;
        return 0;
    }
};


RcPtr<Inst> make_Gatherer( const Vec<Ressource> &children ) {
    return new Gatherer( children );
}
