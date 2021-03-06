#include "TypeInSane.h"
#include "Ref.h"
#include "Vm.h"

Ref::Ref( const Ressource &creator, Ref::Flags flags ) : creation_inter_date( vm ? vm->inter_date : 0 ), current( creator ), creator( creator ), flags( flags ) {
}

Ref::~Ref() {
    //
    if ( ! ( flags & Flags::NOT_CONSTRUCTED ) ) {
        cpt_use = 654;
        TypeInSane *type = creator.inst->created_out_type( creator.nout );
        if ( type->kv_size() < 0 )
            TODO;
        type->destroy( Variable( this, 0, type->kv_size(), type ), true );
    }

    //
    creator.inst->created_outputs[ creator.nout ].ref = 0;
}

void Ref::write_to_stream( std::ostream &os ) const {
    os << current;
}

bool Ref::is_shared() const {
    return cpt_use > 1;
}

void Ref::constify() {
    flags |= Flags::CONST;
}

void Ref::set( const Ressource &new_current, int cst ) {
    if ( current == new_current )
        return;

    if ( flags & Flags::CONST )
        vm->add_error( "a const reference should not be modified" );

    // interception
    if ( vm->interceptor && vm->inter_date > creation_inter_date ) {
        TODO;
        //        auto iter = vm->interceptor->mod_refs.find( this );
        //        if ( iter == vm->interceptor->mod_refs.end() )
        //            vm->interceptor->mod_refs.emplace_hint( iter, this, Interceptor::ValueChange{ value, {} } );
    }

    // change value
    current = new_current;

    //    auto mod = [&]() {
    //        if ( creation_inter_date < inter_date && inter_map ) {
    //            //RcPtr<Ref> rp_this( inc_ref( this ) );
    //            auto iter = inter_map->find( this );
    //            if ( iter == inter_map->end() )
    //                inter_map->emplace_hint( iter, this, Interception{ val, {} } );
    //        }
    //    };

    //    //
    //    Value in_a_break;
    //    for( const Break &br : breaks )
    //        if ( creation_inter_date < br.date )
    //            in_a_break = in_a_break ? make_Or_log( in_a_break, br.cond ) : br.cond;

    //    if ( in_a_break ) {
    //        if ( ! in_a_break.is_true() ) {
    //            mod();
    //            if ( in_a_break.is_false() ) {
    //                val.inst = new_val.inst;
    //                val.nout = new_val.nout;
    //            } else {
    //                val = new_If( { in_a_break }, new If_inp, new If_out( val ), new If_inp, new If_out( Value{ new_val.inst, new_val.nout } ) );
    //            }
    //        }
    //    } else {
    //        mod();
    //        val.inst = new_val.inst;
    //        val.nout = new_val.nout;
    //    }
}
