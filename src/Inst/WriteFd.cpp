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
    }

    WriteFd( AttrClone, const WriteFd *orig ) : fd( orig->fd ), args( orig->args ) {
    }

    virtual void write_code( StreamSep &ss, Codegen &cg ) override {
        ss.write_beg();
        if ( args.size() == 1 )
            *ss << cg.write_func_write_fd( args[ 0 ].type ) << "(" << cg.repr( to_Value( fd ) ) << "," << cg.repr( to_Value( args[ 0 ] ) ) << ")";
        else
            *ss << cg.write_func_write_fd( 0 ) << "(" << cg.repr( to_Value( fd ) ) << "," << cg.repr( to_Value( args[ 0 ] ) ) << "," << cg.repr( to_Value( args[ 1 ] ) ) << ")";
        ss.write_end( ";" );
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
    res->init_attr( res->fd, fd.to_Value() );
    for( Variable &arg : args )
        res->init_attr( *res->args.push_back(), arg.to_Value() );

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
