#include "../Codegen/Codegen.h"
#include "../System/DotOut.h"
#include "../System/Deque.h"
#include "../Ressource.h"
#include "../Type.h"
#include "../Ref.h"
#include "../Vm.h"
#include "CanoCst.h"
#include <fstream>

size_t Inst::cur_op_id = 0;
size_t Inst::date      = 0;

Inst::Inst() : op_id( 0 ) {
    creation_date = date++;
}

Inst::~Inst() {
    for( int ninp = 0; ninp < (int)children.size(); ++ninp )
        children[ ninp ].inst->parents.remove_first( Parent{ this, ninp } );
}

void Inst::clear_children() {
    for( size_t ninp = 0; ninp < children.size(); ++ninp )
        children[ ninp ].inst->parents.remove_first( Parent{ this, int( ninp ) } );
    children.clear();
}

int Inst::add_child( const Ressource &ch ) {
    int res = children.size();
    ch.inst->parents << Parent{ this, res };
    children << ch;
    return res;
}

void Inst::mod_child( int ninp, const Ressource &ch ) {
    children[ ninp ].inst->parents.remove_first( Parent{ this, ninp } );
    ch.inst->parents << Parent{ this, ninp };
    children[ ninp ] = ch;
}

void Inst::rem_child( int ninp ) {
    // remove link of parent of child ninp
    children[ ninp ].inst->parents.remove_first( Parent{ this, ninp } );

    // offset ninp in parents of children with index > ninp
    for( int i = children.size(); --i > ninp; )
        --children[ i ].inst->parents.find( Parent{ this, i } )->ninp;

    // remove from children list
    children.remove( ninp );
}

void Inst::rem_out( int nout, bool check_if_unused ) {
    for( Parent &p : parents ) {
        if ( check_if_unused )
            ASSERT( p.inst->children[ p.ninp ].nout != nout, "..." );
        if ( p.inst->children[ p.ninp ].nout < 0 )
            TODO;
        if ( p.inst->children[ p.ninp ].nout > nout )
            --p.inst->children[ p.ninp ].nout;
    }
}

void Inst::init_attr( IiRessourceWithOffset &attr, const Ressource &ressource, const KuSI64 offset ) {
    init_attr( attr.ressource, ressource );
    init_attr( attr.offset   , offset    );
}

void Inst::init_attr( IiRessource &attr, const Ressource &ressource ) {
    attr.index = add_child( ressource );
}

void Inst::init_attr( IiKuSI64 &attr, const KuSI64 &val ) {
    if ( val.is_known() )
        attr.kv = val.kv();
    else
        init_attr( *( attr.uv = new IiValue ), val.uv() );
}

void Inst::init_attr( IiValue &attr, const Value &val ) {
    init_attr( attr.ressource, val.ressource );
    init_attr( attr.offset   , val.offset    );
    init_attr( attr.length   , val.length    );

    attr.type = val.type;
}

const Ressource &Inst::to_Ressource( const IiRessource &attr ) const {
    return children[ attr.index ];
}

KuSI64 Inst::to_KuSI64( const IiKuSI64 &attr ) const {
    if ( attr.uv )
        return to_Value( *attr.uv );
    return attr.kv;
}

Value Inst::to_Value( const IiValue &attr ) const  {
    return { to_Ressource( attr.ressource ), to_KuSI64( attr.offset ), to_KuSI64( attr.length ), attr.type };
}

Ref *Inst::new_created_output() {
    Ref *res = new Ref( Ressource( this, created_outputs.size() ) );
    created_outputs << CreatedOutput{ res };
    return res;
}

void Inst::get_linked_refs( int nout, const KcSI64 &offset, const KcSI64 &length, const std::function<void (Ref *)> &cb ) {
}

Inst::FuncOnRefPtr Inst::add_wr_cb() {
    return [this]( Ref *ref ) {
        // if *this has modified the ref, there's nothing to do (ressource is already a child and ref has already been modified)
        if ( ref->current.inst == this )
            return;

        size_t nc = 0;
        for( ; ; ++nc ) {
            // not in children ?
            if ( nc == children.size() ) {
                add_child( ref->current );
                break;
            }
            // already in children ?
            if ( ref->current == children[ nc ] )
                break;
        }
        ref->set( Ressource( this, iomap.size() ) );
        iomap << nc;
    };
}

Inst::FuncOnRefPtr Inst::add_rd_cb() {
    return [this]( Ref *ref ) {
        // if *this has modified the ref, there's nothing to do (ressource is already a child)
        if ( ref->current.inst == this )
            return;

        // else, we have to say that the ressource is needed
        for( size_t nc = 0; ; ++nc ) {
            // not in children ?
            if ( nc == children.size() ) {
                add_child( ref->current );
                break;
            }
            // already in children ?
            if ( ref->current == children[ nc ] )
                break;
        }
    };
}

void Inst::replace_by( int nout, Inst *new_inst, int new_nout ) {
    Vec<Inst::Parent> cp_parents = parents;
    for( const Parent &p : cp_parents )
        if ( p.inst->children[ p.ninp ].inst == this && p.inst->children[ p.ninp ].nout == nout )
            p.inst->mod_child( p.ninp, Ressource( new_inst, new_nout ) );
}

bool Inst::all_children_with_op_id( size_t oi ) const {
    for( const Ressource &ch : children )
        if ( ch.inst->op_id < oi )
            return false;
    return true;
}

Type *Inst::created_out_type( int nout ) const {
    write_dot( std::cerr << __FUNCTION__ << " " );
    TODO;
    return 0;
}

KuSI64 Inst::created_out_size( int nout ) const {
    return out_type( nout )->kv_size();
}

KuSI64 Inst::created_out_alig( int nout ) const {
    return out_type( nout )->kv_alig();
}

int Inst::nb_parents_on_nout( int nout ) const {
    size_t res = 0;
    for( const Parent &p : parents )
        res += p.ninp >= 0 && p.inst->children[ p.ninp ].nout == nout;
    return res;
}

RcPtr<CanoInst> Inst::make_cano_inst( int nout ) const {
    write_dot( std::cerr << __FUNCTION__ << " " );
    TODO;
    return 0;
}

void Inst::externalize( Inst *inst, size_t ninp ) {
    write_dot( std::cerr << __FUNCTION__ << " " );
    TODO;
}

RcPtr<CanoInst> Inst::cano_inst(const IiRessource &ressource, const KcSI64 &offset, const KcSI64 &length ) const {
    const Ressource &ch = children[ ressource.index ];
    return ch.inst->cano_inst( ch.nout, offset, length );
}

RcPtr<CanoInst> Inst::cano_inst( const IiRessource &ressource ) const {
    return children[ ressource.index ].cano_inst();
}

KcSI64 Inst::cano_kcSI64( const IiKuSI64 &value ) const {
    return value.is_known() ? KcSI64( value.kv ) : KcSI64( cano_val( *value.uv ) );
}

CanoVal Inst::cano_val( const IiValue &value ) const {
    return cano_val( value.ressource, cano_kcSI64( value.offset ), cano_kcSI64( value.length ), value.type );
}

RcPtr<CanoInst> Inst::cano_inst( int nout, const KcSI64 &offset, const KcSI64 &length ) const {
    return cano_inst( nout )->sub_part( offset, length );
}

RcPtr<CanoInst> Inst::cano_inst( int nout ) const {
    if ( ! cano_inst_buf )
        cano_inst_buf = make_cano_inst( nout );
    return cano_inst_buf;
}

CanoVal Inst::cano_val( const IiRessource &ressource, const KcSI64 &offset, const KcSI64 &length, Type *type ) const {
    return { cano_inst( ressource, offset, length ), type };
}

CanoVal Inst::cano_val( const IiRessource &ressource ) const {
    return children[ ressource.index ].cano_val();
}

CanoVal Inst::cano_val(int nout, const KcSI64 &offset, const KcSI64 &length, Type *type ) const {
    return { cano_inst( nout, offset, length ), type };
}

CanoVal Inst::cano_val( int nout ) const {
    return { cano_inst( nout ), out_type( nout ) };
}

Type *Inst::out_type( int nout ) const {
    if ( nout < (int)created_outputs.size() )
        return created_out_type( nout );
    return children[ iomap[ nout - created_outputs.size() ] ].type();
}

KuSI64 Inst::out_size( int nout ) const {
    if ( nout < (int)created_outputs.size() )
        return created_out_size( nout );
    return children[ iomap[ nout - created_outputs.size() ] ].size();
}

int Inst::inp_corr( int nout ) const {
    return nout >= (int)created_outputs.size() ? iomap[ nout - created_outputs.size() ] : -1;
}

Inst *Inst::clone() const {
    write_dot( std::cerr << __FUNCTION__ << " " );
    TODO;
    return 0;
}

bool Inst::is_non_null( int nout, const KuSI64 &offset, const KuSI64 &length, Type *type ) const {
    return false;
}

bool Inst::is_null( int nout, const KuSI64 &offset, const KuSI64 &length, Type *type ) const {
    return false;
}

void Inst::write_to_stream( std::ostream &os, SI32 nout, Type *type, int offset ) const {
    write_dot( os );
    if ( nout >= 0 )
        os << "[" << nout << "]";
    if ( offset >= 0 )
        os << "{" << offset << "}";
    if ( children.size() ) {
        os << '(' << children[ 0 ];
        for( size_t i = 1; i < children.size(); ++i )
            os << ',' << children[ i ];
        os << ')';
    }
}

bool Inst::write_graph_rec( std::ostream &ss, std::set<const Inst *> &seen_insts, const std::function<void (std::ostream &, const Inst *)> &f, bool disp_parents ) const {
    if ( seen_insts.count( this ) )
        return false;
    seen_insts.insert( this );

    // edges
    int cpt = 0;
    for( const Ressource &v : children ) {
        std::ostringstream label;
        if ( v.inst->created_outputs.size() + v.inst->iomap.size() > 1 )
            label << v.nout;        
        // label << v.type()->name;

        const char *style = "solid";
        if ( v.nout >= (int)v.inst->created_outputs.size() )
            style = "dotted";

        if ( children.size() > 1 )
            ss << "  node_" << this << ":f" << cpt++ << " -> node_" << v.inst.ptr() << " [style=" << style << ",label=\"" << label.str() << "\"];\n";
        else
            ss << "  node_" << this << " -> node_" << v.inst.ptr() << " [style=" << style << ",label=\"" << label.str() << "\"];\n";
        v.inst->write_graph_rec( ss, seen_insts, f, disp_parents );
    }

    //    if ( disp_parents ) {
    //        for( const Parent &p : parents ) {
    //            // p.inst->write_graph_rec( ss, seen_insts, f, disp_parents );

    //            if ( p.inst->children.size() > 1 )
    //                ss << "  node_" << p.inst << ":f" << p.ninp << " -> node_" << this << " [color=\"green\"];\n";
    //            else
    //                ss << "  node_" << p.inst << " -> node_" << this << " [color=\"green\"];\n";
    //        }
    //    }

    // node
    std::ostringstream label;
    write_dot( label );
    if ( f )
        f( label, this );

    if ( children.size() > 1 ) {
        for( size_t n = 0; n < children.size(); ++n )
            label << " |<f" << n << "> ";
        dot_out( ss << "  node_" << this << " [label=\"", label.str() ) << "\",shape=record];\n";
    } else
        dot_out( ss << "  node_" << this << " [label=\"", label.str() ) << "\"];\n";

    return true;
}

void Inst::write_code( StreamSep &ss, Codegen &cg ) {
    // if this inst can be inlined inside a future inst, we don't do nothing here
    if ( can_be_inlined() )
        return;

    if ( created_outputs.size() != 1 )
        TODO;

    Type *type = out_type( 0 );
    ss.write_beg() << cg.repr( type ) << " " << *cg.new_reg_for( this, type, 0 ) << " = ";
    StreamPrio sp{ *ss, PRIO_Assignment };
    write_inline_code( sp, cg, 0, Codegen::WriteInlineCodeFlags::type_is_forced );
    ss.write_end( ";" );
}

void Inst::write_inline_code( StreamPrio &ss, Codegen &cg, int nout, int flags ) {
    // ss << "TODO: inline code for " << *this;
    TODO;
}

bool Inst::expects_a_reg_at( int ninp ) const {
    return false;
}

bool Inst::can_be_inlined() const {
    for( const Parent &p : parents )
        if ( p.inst->expects_a_reg_at( p.ninp ) )
            return false;
    return true;
}

void *Inst::rcast( int nout ) {
    write_dot( std::cerr );
    TODO;
    return 0;
}

Inst::AssFunc Inst::get_assign_func( int nout, int off, int len ) {
    return {};
}

void Inst::display_graphviz( const Vec<Inst *> &lst, const std::function<void (std::ostream &, const Inst *)> &f, const std::string &filename, bool disp_parents, bool launch ) {
    std::set<const Inst *> seen_insts;
    std::ofstream ss( filename.c_str() );
    ss << "digraph Vm {\n";
    for( const Inst *inst : lst )
        inst->write_graph_rec( ss, seen_insts, f, disp_parents );
    ss << "}";

    ss.close();
    if ( launch )
        exec_dot( filename.c_str() );
}

void Inst::dfs( const Vec<Inst *> &lst, const std::function<void (Inst *)> &f, bool deep, bool f_after, bool need_inc_ref ) {
    ++cur_op_id;
    for( Inst *inst : lst )
        dfs_rec( inst, f, deep, f_after, need_inc_ref );
}

void Inst::dfs_rec( Inst *inst, const std::function<void (Inst *)> &f, bool deep, bool f_after, bool need_inc_ref ) {
    if ( inst->op_id == Inst::cur_op_id )
        return;
    inst->op_id = Inst::cur_op_id;

    RcPtr<Inst> tp( need_inc_ref ? inst : 0 );

    if ( ! f_after )
        f( inst );

    if ( deep ) {
        Deque<Inst *> outs;
        inst->get_out_insts( outs );
        for( Inst *out : outs )
            dfs_rec( out, f, deep, f_after, need_inc_ref );
    }

    for( const Ressource &v : inst->children )
        dfs_rec( v.inst.ptr(), f, deep, f_after, need_inc_ref );

    if ( f_after )
        f( inst );
}

Inst *Inst::parent_out_inst() const {
    TODO;
    return 0;
}

bool Inst::simplify_for_cg( Codegen &cg ) {
    return false;
}


void Inst::get_out_insts( Deque<Inst *> &outs ) {
}

void Inst::thread_visitor( int nout, const std::function<void( Inst *, int nout, int ninp )> &cb, bool call_before ) {
    int ninp = inp_corr( nout );

    if ( call_before )
        cb( this, nout, ninp );

    if ( ninp >= 0 )
        children[ ninp ].thread_visitor( cb, call_before );

    if ( ! call_before )
        cb( this, nout, ninp );
}

