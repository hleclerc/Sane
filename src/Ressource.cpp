#include "System/BoolVec.h"
#include "Ressource.h"

void Ressource::thread_visitor( const std::function<void (Inst *, int, int)> &cb, bool call_before ) const {
    inst->thread_visitor( nout, cb, call_before );
}

void *Ressource::rcast() {
    return inst->rcast( nout );
}

void Ressource::write_to_stream( std::ostream &os ) const {
    if ( inst )
        inst->write_to_stream( os, nout );
    else
        os << "NULL";
}

Ressource &Ressource::operator=( const Ressource &that ) {
    inst = that.inst;
    nout = that.nout;
    return *this;
}

bool Ressource::operator==( const Ressource &that ) const {
    return std::tie( inst, nout ) == std::tie( that.inst, that.nout );
}

bool Ressource::operator!=(const Ressource &that) const {
    return std::tie( inst, nout ) != std::tie( that.inst, that.nout );
}

bool Ressource::operator<( const Ressource &that ) const {
    return std::tie( inst, nout ) < std::tie( that.inst, that.nout );
}
