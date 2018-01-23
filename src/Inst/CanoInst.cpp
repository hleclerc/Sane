#include "../System/DotOut.h"
#include "CanoVal.h"
#include <fstream>

size_t CanoInst::cur_op_id = 0;


CanoInst::CanoInst() : type( 0 ), op_id( 0 ) {
}

CanoInst::~CanoInst() {
    for( int ninp = 0; ninp < (int)children.size(); ++ninp )
        children[ ninp ].inst->parents.remove_first( Parent{ this, ninp } );
}

int CanoInst::add_child( const CanoVal &ch ) {
    int res = children.size();
    ch.inst->parents << Parent{ this, res };
    children << ch;
    return res;
}

void CanoInst::write_to_stream( std::ostream &os, Type *type ) const {
    write_dot( os, type );
    if ( children.size() ) {
        os << '(' << children[ 0 ];
        for( size_t i = 1; i < children.size(); ++i )
            os << ',' << children[ i ];
        os << ')';
    }
}

bool CanoInst::write_graph_rec( std::ostream &ss, std::set<const CanoInst *> &seen_insts, const std::function<void (std::ostream &, const CanoInst *)> &f ) const {
    if ( seen_insts.count( this ) )
        return false;
    seen_insts.insert( this );

    // edges
    for( const CanoVal &ch : children ) {
        ss << "  node_" << this << " -> node_" << ch.inst.ptr() << ";\n";
        ch.inst->write_graph_rec( ss, seen_insts, f );
    }

    // node
    std::ostringstream label;
    write_dot( label, 0 );
    if ( f )
        f( label, this );

    dot_out( ss << "  node_" << this << " [label=\"", label.str() ) << "\"];\n";

    return true;
}

void CanoInst::get_out_insts( Deque<CanoInst *> &outs ) {
}

bool CanoInst::always_false( Type *type ) const {
    return false;
}

bool CanoInst::always_true( Type *type ) const {
    return false;
}

bool CanoInst::known_value() const {
    return false;
}

void CanoInst::display_graphviz( const Vec<CanoInst *> &lst, const std::function<void (std::ostream &, const CanoInst *)> &f, const std::string &filename, bool disp_parents, bool launch ) {
    std::set<const CanoInst *> seen_insts;
    std::ofstream ss( filename.c_str() );
    ss << "digraph Vm {\n";
    for( const CanoInst *inst : lst )
        inst->write_graph_rec( ss, seen_insts, f );
    ss << "}";

    ss.close();
    if ( launch )
        exec_dot( filename.c_str() );
}

void CanoInst::dfs_rec( CanoInst *inst, const std::function<void (CanoInst *)> &f, bool deep, bool f_after, bool need_inc_ref ) {
    if ( inst->op_id == CanoInst::cur_op_id )
        return;
    inst->op_id = CanoInst::cur_op_id;

    RcPtr<CanoInst> tp( need_inc_ref ? inst : 0 );

    if ( ! f_after )
        f( inst );

    if ( deep ) {
        Deque<CanoInst *> outs;
        inst->get_out_insts( outs );
        for( CanoInst *out : outs )
            dfs_rec( out, f, deep, f_after, need_inc_ref );
    }

    for( const CanoVal &v : inst->children )
        dfs_rec( v.inst.ptr(), f, deep, f_after, need_inc_ref );

    if ( f_after )
        f( inst );
}

void CanoInst::dfs( const Vec<CanoInst *> &lst, const std::function<void (CanoInst *)> &f, bool deep, bool f_after, bool need_inc_ref ) {
    ++cur_op_id;
    for( CanoInst *inst : lst )
        dfs_rec( inst, f, deep, f_after, need_inc_ref );
}
