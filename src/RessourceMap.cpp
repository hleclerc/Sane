#include "Inst/RessourceInst.h"
#include "Inst/CanoConv.h"
#include "RessourceMap.h"
#include "TypeInSane.h"
#include "Variable.h"
#include "Ref.h"
#include "Vm.h"

RessourceMap::RessourceMap() : file_content( 0 ) {
}

RessourceMap::~RessourceMap() {
}

void RessourceMap::get_linked_refs( const Ref *ref, const KcSI64 &offset, const KcSI64 &length, const std::function<void(Ref *)> &cb ) {
    cb( const_cast<Ref *>( ref ) );

    ref->creator.inst->get_linked_refs( ref->creator.nout, offset, length, [&]( Ref *ref ) {
        cb( ref );
    } );
}

void RessourceMap::on_file_content( const CanoVal &fd, const std::function<void(Ref *)> &cb ) {
    if ( fd.type != vm->type_SI32 )
        return on_file_content( make_CanoConv( fd, vm->type_SI32 ), cb );

    if ( ! file_content ) {
        Variable v = make_RessourceInst( "file content" );
        file_content = v.ref;
    }

    cb( file_content.ptr() );
}

void RessourceMap::on_file_cursor( const CanoVal &fd, const std::function<void(Ref *)> &cb ) {
    if ( fd.type != vm->type_SI32 )
        return on_file_content( make_CanoConv( fd, vm->type_SI32 ), cb );

    // check fd is present
    auto iter = file_cursors.find( fd.inst );
    if ( iter == file_cursors.end() ) {
        Variable v = make_RessourceInst( "file cursor" );
        file_cursors.insert( iter, std::make_pair( fd.inst, v.ref ) );
    }

    // call cb on potentially equal fds
    for( std::pair<const RcPtr<CanoInst>,RcPtr<Ref>> &vr : file_cursors  )
        if ( ! always_false( fd == CanoVal( vr.first, vm->type_SI32 ) ) )
            cb( vr.second.ptr() );
}

void RessourceMap::visit_ext_changes( const std::function<void(Ref *)> &visitor ) {
    if ( file_content && file_content->current != file_content->creator )
        visitor( file_content.ptr() );

    //    for( std::pair<const Value,Rss> &vr : file_cursors  )
    //        visitor( &vr.second );
}

//void RessourceMap::visit( std::function<void (Rss *)> visitor ) {
//}

