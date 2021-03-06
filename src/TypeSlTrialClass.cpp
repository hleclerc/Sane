#include "TypeSlTrialClass.h"
#include "SlTrialClass.h"
#include "Class.h"

TypeSlTrialClass::TypeSlTrialClass() : TypeInSane( "SlTrialClass" ) {
}

Type::CondVal TypeSlTrialClass::get_condition( const Variable &self ) const {
    return self.rcast<SlTrialClass>()->condition;
}

void TypeSlTrialClass::get_fail_info( const Variable &self, size_t &offset, RcString &source, RcString &msg ) const {
    SlTrialClass *tr = self.rcast<SlTrialClass>();
    Class *def = tr->def.rcast<Class>();
    offset = def->offset;
    source = def->source;
    msg = tr->msg;
}

void TypeSlTrialClass::destroy( const Variable &self, bool use_virtual ) {
    delete self.rcast<SlTrialClass>();
}

unsigned TypeSlTrialClass::get_nb_conversions( const Variable &self ) const {
    TODO;
    return 0;
    //    SlTrialClass *tr = rcast( self.ptr() );
    //    return tr->tci.nb_conversions;
}
