#include "../System/DotOut.h"
#include "../Type.h"
#include "CanoVal.h"
#include <fstream>

size_t CanoInst::cur_op_id = 0;


CanoInst::CanoInst() : fully_solved_buf( 0 ), child_for_fact( 0 ), op_id( 0 ) {
}

CanoInst::~CanoInst() {
    if ( child_for_fact )
        child_for_fact->parents.remove_first( this );

    if ( fully_solved_buf != this )
        reinterpret_cast<RcPtr<CanoInst> &>( fully_solved_buf ).~RcPtr();
}

struct CanoInstWriteWisitor : CanoInst::AttrVisitor {
    template<class T>
    void disp( const char *name, const T &val ) {
        *os << ( cpt++ ? "," : "(" );
        if ( name )
            *os << name << "=";
        *os << val;
    }

    virtual void on( const char *name, const RcPtr<CanoInst> &val ) { disp( name, val ); }
    virtual void on( const char *name, const CanoVal &val ) { disp( name, val ); }
    virtual void on( const char *name, const KcSI64 &val ) { disp( name, val ); }
    virtual void on( const char *name, Type *val ) { if ( val ) disp( name, *val ); else disp( name, 0 ); }

    std::ostream *os;
    int cpt;
};

void CanoInst::write_to_stream( std::ostream &os, Type *type ) const {
    write_dot( os, type );

    CanoInstWriteWisitor cv;
    cv.os = &os;
    cv.cpt = 0;
    attr_visitor( cv );
    if ( cv.cpt )
        os << ')';
}

struct CanoInstWriteGraphWisitor : CanoInst::AttrVisitor {
    template<class T>
    void disp( const char *name, const T &val ) {
        label << ( cpt++ ? "," : "(" );
        if ( name )
            label << name << "=";
        label << val;
    }

    virtual void on( const char *name, const RcPtr<CanoInst> &val ) { edges << name; children << val.ptr(); }
    virtual void on( const char *name, const CanoVal &val ) { on( name, val.inst ); }
    virtual void on( const char *name, const KcSI64 &val ) { if ( val.is_known() ) disp( name, val ); else on( name, val.uv() ); }
    virtual void on( const char *name, Type *val ) { disp( name, *val ); }

    Vec<const CanoInst *> children;
    Vec<const char *>     edges;
    std::ostringstream    label;
    int                   cpt = 0;
};

bool CanoInst::write_graph_rec( std::ostream &ss, std::set<const CanoInst *> &seen_insts, const std::function<void (std::ostream &, const CanoInst *)> &f ) const {
    if ( seen_insts.count( this ) )
        return false;
    seen_insts.insert( this );

    // node
    CanoInstWriteGraphWisitor cv;
    write_dot( cv.label, 0 );
    attr_visitor( cv );
    if ( cv.cpt )
        cv.label << ')';
    if ( f )
        f( cv.label, this );

    dot_out( ss << "  node_" << this << " [label=\"", cv.label.str() ) << "\"];\n";

    // edges
    for( const CanoInst *inst : cv.children ) {
        ss << "  node_" << this << " -> node_" << inst << ";\n";
        inst->write_graph_rec( ss, seen_insts, f );
    }

    return true;
}

CanoInst *CanoInst::make_fully_solved() {
    return this;
}

struct ChildrenVisitor : public CanoInst::AttrVisitor {
    virtual void on( const char *name, const RcPtr<CanoInst> &val ) { (*visitor)( name, val.ptr() ); }
    virtual void on( const char *name, const CanoVal &val ) { on( name, val.inst ); }
    virtual void on( const char *name, const KcSI64 &val ) { if ( val.is_known() == false ) on( name, val.uv() ); }
    virtual void on( const char *name, Type *val ) {}

    const std::function<void (const char *, CanoInst *)> *visitor;
};

void CanoInst::children_visitor( const std::function<void (const char *, CanoInst *)> &visitor ) {
    ChildrenVisitor cv;
    cv.visitor = &visitor;
    attr_visitor( cv );
}

SI64 CanoInst::get_SI64_value( Type *orig ) const {
    ERROR( "not a known value" );
    return 0;
}

void CanoInst::get_out_insts( Deque<CanoInst *> &outs ) {
}

bool CanoInst::always_false( Type *type ) const {
    return false;
}

bool CanoInst::always_true( Type *type ) const {
    return false;
}

RcPtr<CanoInst> CanoInst::simp_CanoConv( Type *orig, Type *target ) {
    return 0;
}

CanoInst *CanoInst::fully_solved() {
    if ( fully_solved_buf == 0 )
        fully_solved_buf = make_fully_solved();
    return fully_solved_buf;
}

void *CanoInst::known_value() const {
    return 0;
}

RcPtr<CanoInst> CanoInst::sub_part( const KcSI64 &wanted_off, const KcSI64 &wanted_len ) {
    if ( ::always_true( wanted_len == length() ) )
        return this;
    P( *this );
    TODO;
    return 0;
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

//void CanoInst::dfs_rec( CanoInst *inst, const std::function<void (CanoInst *)> &f, bool deep, bool f_after, bool need_inc_ref ) {
//    if ( inst->op_id == CanoInst::cur_op_id )
//        return;
//    inst->op_id = CanoInst::cur_op_id;

//    RcPtr<CanoInst> tp( need_inc_ref ? inst : 0 );

//    if ( ! f_after )
//        f( inst );

//    if ( deep ) {
//        Deque<CanoInst *> outs;
//        inst->get_out_insts( outs );
//        for( CanoInst *out : outs )
//            dfs_rec( out, f, deep, f_after, need_inc_ref );
//    }

//    for( const CanoVal &v : inst->children )
//        dfs_rec( v.inst.ptr(), f, deep, f_after, need_inc_ref );

//    if ( f_after )
//        f( inst );
//}

//void CanoInst::dfs( const Vec<CanoInst *> &lst, const std::function<void (CanoInst *)> &f, bool deep, bool f_after, bool need_inc_ref ) {
//    ++cur_op_id;
//    for( CanoInst *inst : lst )
//        dfs_rec( inst, f, deep, f_after, need_inc_ref );
//}
