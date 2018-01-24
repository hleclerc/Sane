#include "../Codegen/Codegen.h"
#include "../Type.h"
#include "../Vm.h"
#include "WriteFd.h"
#include "Cst.h"
#include "Clonable.h"
class RessourceMap;

/**
  fd, arg_0, [arg_1, ... arg_{nb_inp}], deps
*/
class WriteFd : public Clonable<WriteFd,Inst> {
public:
    WriteFd() {
        //        for( const Value &arg : args )
        //            add_child( arg );

        //        int nout = 0;
        //        auto af = [&]( Rss *rs ) {
        //            add_child( rs->state->get() );
        //            rs->state->set( { this, nout++, gvm->type_Ressource, 0 } );
        //        };

        //        nb_base_args = children.size();
        //        ressource_map->get_prs_on_file_content( args[ 0 ], af );
        //        ressource_map->get_prs_on_file_cursor ( args[ 0 ], af );
    }

    WriteFd( AttrClone, const WriteFd * ) {
    }

    virtual void write_code( StreamSep &ss, Codegen &cg ) override {
        //        ss.write_beg();
        //        if ( nb_base_args == 2 )
        //            *ss << cg.write_func_write_fd( children[ 1 ].type ) << "(" << cg.repr( children[ 0 ] ) << "," << cg.repr( children[ 1 ] ) << ")";
        //        else
        //            *ss << cg.write_func_write_fd( 0 ) << "(" << cg.repr( children[ 0 ] ) << "," << cg.repr( children[ 1 ] ) << "," << cg.repr( children[ 2 ] ) << ")";
        //        ss.write_end( ";" );
        TODO;
    }

    virtual void write_dot( std::ostream &os ) const override {
        os << "WriteFd";
    }

    virtual RcPtr<CanoInst> make_cano_inst( int nout ) const override {
        TODO;
        return 0;
    }

    IiValue      fd;
    Vec<IiValue> args;
};



void make_WriteFd( const Variable &fd, const Vec<Variable> &args ) {
    WriteFd *res = new WriteFd;
    res->init_attr( res->fd, fd.get() );
    for( Variable &arg : args )
        res->init_attr( *res->args.push_back(), arg.get() );

    // for each potentially modified/read ressource
    vm->ressource_map.on_file_content( fd.cano_repr(), res->add_wr_cb() );
    vm->ressource_map.on_file_cursor ( fd.cano_repr(), res->add_wr_cb() );
}

void make_WriteFd( const Variable &fd, const Variable &ptr, const Variable &len ) {
    make_WriteFd( fd, Vec<Variable>{ ptr, len } );
}

void make_WriteFd( const Variable &fd, const Variable &val ) {
    make_WriteFd( fd, Vec<Variable>{ val } );
}
