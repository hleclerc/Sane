#include "System/RaiiSave.h"
#include "Interceptor.h"
#include "Vm.h"

void Interceptor::run( const std::function<void ()> &func ) {
    // new global interception context
    auto _r0 = raii_save( vm->inter_date, vm->inter_date + 1 );
    auto _r1 = raii_save( vm->interceptor, this );

    // do the stuff
    func();

    // save the new values, restore the refs
    for( auto p = mod_refs.begin(); p != mod_refs.end(); ) {
        if ( p->first->current == p->second.o ) {
            p = mod_refs.erase( p );
        } else {
            p->second.n = p->first->current;
            p->first->current = p->second.o;
            ++p;
        }
    }

    // new_breaks = breaks;
}
