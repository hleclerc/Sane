#include "Inst/CanoCst.h"
#include "KuSI64.h"
#include "Class.h"
#include "Type.h"
#include "Vm.h"

Type::Type() {
}

bool Type::has_vtable_at_the_beginning() const {
    TODO;
    return false;
}

RcString Type::checks_type_constraint( const Variable &self, const Variable &tested_var, TCI &tci ) const {
    vm->add_error( "checks_type_constraint for type {}", *this );
    PE( *this );
    TODO;
    return "not equal nor inherited";
}

unsigned Type::get_nb_conversions( const Variable &self ) const {
    PE( *this );
    TODO;
    return 0;
}

bool Type::has_a_constructor() const {
    return true;
}


//void Type::write_cst( std::ostream &os, const PI8 *data, int offset_mod_8, bool always_add_braces ) const {
//    // os << content << "(" << "..." << ")";
//    os << "{";
//    for( TypeContent::Attribute *attr = first_attribute; attr; attr = attr->next ) {
//        if ( attr != first_attribute )
//            os << ",";
//        attr->type->write_cst( os, data + ( offset_mod_8 + attr->off ) / 8, ( offset_mod_8 + attr->off ) % 8 );
//    }
//    os << "}";
//}

void Type::destroy( const Variable &self, bool use_virtual ) {
}


void Type::spread_in( const Variable &self, Vec<Variable> &res, Vec<RcString> &names ) {
    PE( *this );
    TODO;
}

void Type::construct( const Variable &self, const Vec<Variable> &args, const Vec<RcString> &names ) {
    Scope new_scope( Scope::ScopeType::BLOCK );
    new_scope.ctor_self = self;

    if ( Variable constructor = self.find_attribute( "construct", false ) )
        constructor.apply( false, args, names );
    else
        vm->add_error( "Found no 'construct' method" );

}

double Type::get_pertinence( const Variable &self ) const {
    PE( *this );
    TODO;
    return 0;
}

Type::CondVal Type::get_condition( const Variable &self ) const {
    PE( *this );
    TODO;
    return Type::CondVal{ 0, {} };
}

void Type::get_fail_info( const Variable &self, size_t &offset, RcString &source, RcString &msg ) const {
    PE( *this );
    TODO;
}

bool Type::destroy_attrs() const {
    return true;
}

Variable Type::make_sl_trial( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) const {
    PE( *this );
    TODO;
    return {};
}

Variable Type::use_sl_trial( bool want_ret, const Variable &func, const Variable &self, const Vec<Variable> &sl_args, const Vec<RcString> &sl_names, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags, const Variable &trial ) const {
    PE( *this );
    TODO;
    return {};
}

Variable Type::apply( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names, const Variable &with_self, ApplyFlags apply_flags ) {
    PE( *this );
    TODO; return {};
}

Variable Type::chbeba( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names ) {
    Variable op = self.find_attribute( "operator {}", false );
    if ( ! op )
        return vm->add_error( "class {} has no 'operator {}'", *self.type, "{}" );
    return op.apply( want_ret, args, names );
}

Variable Type::select( Variable &self, bool want_ret, const Vec<Variable> &args, const Vec<RcString> &names ) {
    Variable op = self.find_attribute( "operator []", false );
    if ( ! op )
        return vm->add_error( "class {} has no 'operator []'", *self.type );
    return op.apply( want_ret, args, names );
}

Variable Type::with_self( Variable &orig, const Variable &new_self ) const {
    PE( *this );
    TODO;
    return {};
}

bool Type::eq_type( Type *that ) {
    return this == that;
}

bool Type::has_floating_point() const {
    return false;
}

int Type::is_signed() const {
    return -1;
}

SI32 Type::kv_size() const {
    return -1;
}

SI32 Type::kv_alig() const {
    return -1;
}

int Type::mantissa_len() const {
    return -1;
}

int Type::exponent_len() const {
    return -1;
}

bool Type::error() const {
    return false;
}

KuSI64 Type::size( const RcPtr<Ref> &ref, const KuSI64 &offset ) const {
    return kv_size();
}

bool Type::is_a_TypeBT() const {
    return false;
}

RcPtr<CanoInst> Type::convert_cano_cst( const void *content, Type *target ) {
    return 0;
}

SI64 Type::convert_cst_to_SI64( const void *content ) const {
    ERROR( "..." );
    return 0;
}

#define BO( NAME ) CanoVal Type::make_Cano##NAME( const void *a, const void *b ) { TODO; return {}; }
#include "decl_bin_op.h"
#undef BO

