#include "TypeCallableWithSelf.h"
#include "CallableWithSelfOrArgs.h"

TypeCallableWithSelf::TypeCallableWithSelf() : TypeInSane( "CallableWithSelf" ) {
}

void TypeCallableWithSelf::destroy( const Variable &self, bool use_virtual ) {
    delete self.rcast<CallableWithSelfOrArgs>();
}

Variable TypeCallableWithSelf::apply( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) {
    CallableWithSelfOrArgs *cs = self.rcast<CallableWithSelfOrArgs>();
    return cs->callable.type->apply( cs->callable, want_ret, args, names, cs->self, apply_flags );
}
