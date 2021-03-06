// Generated file
#pragma once

#include <Hpipe/BinStream.h>
#include "../../System/RaiiSave.h"
#include "../../System/RcString.h"
#include "../../System/Stream.h"

#ifndef AST_TOK_NUMS
#define AST_TOK_NUMS
#define AST_TOK_pass_NUM 0
#define AST_TOK_variable_NUM 1
#define AST_TOK_var_assembly_NUM 2
#define AST_TOK_continue_NUM 3
#define AST_TOK_break_NUM 4
#define AST_TOK_false_NUM 5
#define AST_TOK_true_NUM 6
#define AST_TOK_self_NUM 7
#define AST_TOK_this_NUM 8
#define AST_TOK_number_NUM 9
#define AST_TOK_string_NUM 10
#define AST_TOK_get_attr_NUM 11
#define AST_TOK_scope_resolution_NUM 12
#define AST_TOK_get_attr_ptr_NUM 13
#define AST_TOK_get_attr_calc_NUM 14
#define AST_TOK_scope_resolution_calc_NUM 15
#define AST_TOK_get_attr_ptr_calc_NUM 16
#define AST_TOK_ss_block_NUM 17
#define AST_TOK_block_NUM 18
#define AST_TOK_apply_op_NUM 19
#define AST_TOK_apply_NUM 20
#define AST_TOK_select_NUM 21
#define AST_TOK_chbeba_NUM 22
#define AST_TOK_init_of_NUM 23
#define AST_TOK_assign_NUM 24
#define AST_TOK_destruct_assign_NUM 25
#define AST_TOK_def_NUM 26
#define AST_TOK_class_NUM 27
#define AST_TOK_if_else_NUM 28
#define AST_TOK_if_NUM 29
#define AST_TOK_while_NUM 30
#define AST_TOK_return_NUM 31
#define AST_TOK_for_NUM 32
#define AST_TOK_typeof_NUM 33
#define AST_TOK_sizeof_NUM 34
#define AST_TOK_aligof_NUM 35
#define AST_TOK_sizeof_bits_NUM 36
#define AST_TOK_aligof_bits_NUM 37
#define AST_TOK_lambda_NUM 38
#define AST_TOK_and_NUM 39
#define AST_TOK_or_NUM 40
#define AST_TOK_vec_NUM 41
#define AST_TOK_map_NUM 42
#define AST_TOK_matrix_NUM 43
#define AST_TOK_raii_NUM 44
#define AST_TOK_info_NUM 45
#define AST_TOK_assert_NUM 46
#define AST_TOK_try_catch_NUM 47
#define AST_TOK_import_NUM 48
#define AST_TOK_enum_NUM 49
#endif // AST_TOK_NUMS

struct AstVisitor {
    struct Apply { RcString attr; Vec<RcString> args, arg_names; };
    AstVisitor() { rec = true; }
    virtual ~AstVisitor() {}
    virtual void set_src( size_t src, size_t off ) {}
    virtual bool enter_test_pass                 () { enter_pass(); return rec; }
    virtual void enter_pass                      () { default_enter( "pass                 " ); }
    virtual void leave_pass                      () { default_leave( "pass                 " ); }
    virtual bool enter_test_variable             ( RcString name ) { enter_variable( name ); return rec; }
    virtual void enter_variable                  ( RcString name ) { default_enter( "variable             " ); }
    virtual void leave_variable                  () { default_leave( "variable             " ); }
    virtual bool enter_test_var_assembly         ( const Vec<RcString> &args ) { enter_var_assembly( args ); return rec; }
    virtual void enter_var_assembly              ( const Vec<RcString> &args ) { default_enter( "var_assembly         " ); }
    virtual void leave_var_assembly              () { default_leave( "var_assembly         " ); }
    virtual bool enter_test_continue             () { enter_continue(); return rec; }
    virtual void enter_continue                  () { default_enter( "continue             " ); }
    virtual void leave_continue                  () { default_leave( "continue             " ); }
    virtual bool enter_test_break                () { enter_break(); return rec; }
    virtual void enter_break                     () { default_enter( "break                " ); }
    virtual void leave_break                     () { default_leave( "break                " ); }
    virtual bool enter_test_false                () { enter_false(); return rec; }
    virtual void enter_false                     () { default_enter( "false                " ); }
    virtual void leave_false                     () { default_leave( "false                " ); }
    virtual bool enter_test_true                 () { enter_true(); return rec; }
    virtual void enter_true                      () { default_enter( "true                 " ); }
    virtual void leave_true                      () { default_leave( "true                 " ); }
    virtual bool enter_test_self                 () { enter_self(); return rec; }
    virtual void enter_self                      () { default_enter( "self                 " ); }
    virtual void leave_self                      () { default_leave( "self                 " ); }
    virtual bool enter_test_this                 () { enter_this(); return rec; }
    virtual void enter_this                      () { default_enter( "this                 " ); }
    virtual void leave_this                      () { default_leave( "this                 " ); }
    virtual bool enter_test_number               ( RcString value ) { enter_number( value ); return rec; }
    virtual void enter_number                    ( RcString value ) { default_enter( "number               " ); }
    virtual void leave_number                    () { default_leave( "number               " ); }
    virtual bool enter_test_string               ( RcString value ) { enter_string( value ); return rec; }
    virtual void enter_string                    ( RcString value ) { default_enter( "string               " ); }
    virtual void leave_string                    () { default_leave( "string               " ); }
    virtual bool enter_test_get_attr             ( RcString obj, RcString name ) { enter_get_attr( obj, name ); return rec; }
    virtual void enter_get_attr                  ( RcString obj, RcString name ) { default_enter( "get_attr             " ); }
    virtual void leave_get_attr                  () { default_leave( "get_attr             " ); }
    virtual bool enter_test_scope_resolution     ( RcString obj, RcString name ) { enter_scope_resolution( obj, name ); return rec; }
    virtual void enter_scope_resolution          ( RcString obj, RcString name ) { default_enter( "scope_resolution     " ); }
    virtual void leave_scope_resolution          () { default_leave( "scope_resolution     " ); }
    virtual bool enter_test_get_attr_ptr         ( RcString obj, RcString name ) { enter_get_attr_ptr( obj, name ); return rec; }
    virtual void enter_get_attr_ptr              ( RcString obj, RcString name ) { default_enter( "get_attr_ptr         " ); }
    virtual void leave_get_attr_ptr              () { default_leave( "get_attr_ptr         " ); }
    virtual bool enter_test_get_attr_calc        ( RcString obj, const Vec<RcString> &args ) { enter_get_attr_calc( obj, args ); return rec; }
    virtual void enter_get_attr_calc             ( RcString obj, const Vec<RcString> &args ) { default_enter( "get_attr_calc        " ); }
    virtual void leave_get_attr_calc             () { default_leave( "get_attr_calc        " ); }
    virtual bool enter_test_scope_resolution_calc( RcString obj, const Vec<RcString> &args ) { enter_scope_resolution_calc( obj, args ); return rec; }
    virtual void enter_scope_resolution_calc     ( RcString obj, const Vec<RcString> &args ) { default_enter( "scope_resolution_calc" ); }
    virtual void leave_scope_resolution_calc     () { default_leave( "scope_resolution_calc" ); }
    virtual bool enter_test_get_attr_ptr_calc    ( RcString obj, const Vec<RcString> &args ) { enter_get_attr_ptr_calc( obj, args ); return rec; }
    virtual void enter_get_attr_ptr_calc         ( RcString obj, const Vec<RcString> &args ) { default_enter( "get_attr_ptr_calc    " ); }
    virtual void leave_get_attr_ptr_calc         () { default_leave( "get_attr_ptr_calc    " ); }
    virtual bool enter_test_ss_block             ( const Vec<RcString> &items ) { enter_ss_block( items ); return rec; }
    virtual void enter_ss_block                  ( const Vec<RcString> &items ) { default_enter( "ss_block             " ); }
    virtual void leave_ss_block                  () { default_leave( "ss_block             " ); }
    virtual bool enter_test_block                ( const Vec<RcString> &items ) { enter_block( items ); return rec; }
    virtual void enter_block                     ( const Vec<RcString> &items ) { default_enter( "block                " ); }
    virtual void leave_block                     () { default_leave( "block                " ); }
    virtual bool enter_test_apply_op             ( RcString name, const Vec<RcString> &args ) { enter_apply_op( name, args ); return rec; }
    virtual void enter_apply_op                  ( RcString name, const Vec<RcString> &args ) { default_enter( "apply_op             " ); }
    virtual void leave_apply_op                  () { default_leave( "apply_op             " ); }
    virtual bool enter_test_apply                ( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { enter_apply( f, args, names, splats ); return rec; }
    virtual void enter_apply                     ( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { default_enter( "apply                " ); }
    virtual void leave_apply                     () { default_leave( "apply                " ); }
    virtual bool enter_test_select               ( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { enter_select( f, args, names, splats ); return rec; }
    virtual void enter_select                    ( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { default_enter( "select               " ); }
    virtual void leave_select                    () { default_leave( "select               " ); }
    virtual bool enter_test_chbeba               ( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { enter_chbeba( f, args, names, splats ); return rec; }
    virtual void enter_chbeba                    ( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { default_enter( "chbeba               " ); }
    virtual void leave_chbeba                    () { default_leave( "chbeba               " ); }
    virtual bool enter_test_init_of              ( RcString name, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { enter_init_of( name, args, names, splats ); return rec; }
    virtual void enter_init_of                   ( RcString name, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) { default_enter( "init_of              " ); }
    virtual void leave_init_of                   () { default_leave( "init_of              " ); }
    virtual bool enter_test_assign               ( RcString name, RcString cname, PI8 nb_scope_rec, RcString value, PI8 flags ) { enter_assign( name, cname, nb_scope_rec, value, flags ); return rec; }
    virtual void enter_assign                    ( RcString name, RcString cname, PI8 nb_scope_rec, RcString value, PI8 flags ) { default_enter( "assign               " ); }
    virtual void leave_assign                    () { default_leave( "assign               " ); }
    virtual bool enter_test_destruct_assign      ( const Vec<RcString> &names, const Vec<RcString> &equal, const Vec<RcString> &types, RcString value, PI8 flags ) { enter_destruct_assign( names, equal, types, value, flags ); return rec; }
    virtual void enter_destruct_assign           ( const Vec<RcString> &names, const Vec<RcString> &equal, const Vec<RcString> &types, RcString value, PI8 flags ) { default_enter( "destruct_assign      " ); }
    virtual void leave_destruct_assign           () { default_leave( "destruct_assign      " ); }
    virtual bool enter_test_def                  ( RcString name, RcString cname, PI8 nb_scope_rec, const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &arg_splats, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats, RcString condition, RcString pertinence, SI32 def_pert_num, SI32 def_pert_exp, PI32 flags, const Vec<RcString> &block, RcString self_constraint, RcString return_type, const Vec<RcString> &wpc ) { enter_def( name, cname, nb_scope_rec, arg_names, arg_constraints, arg_def_vals, arg_splats, with_names, with_constraints, with_def_vals, with_splats, condition, pertinence, def_pert_num, def_pert_exp, flags, block, self_constraint, return_type, wpc ); return rec; }
    virtual void enter_def                       ( RcString name, RcString cname, PI8 nb_scope_rec, const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &arg_splats, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats, RcString condition, RcString pertinence, SI32 def_pert_num, SI32 def_pert_exp, PI32 flags, const Vec<RcString> &block, RcString self_constraint, RcString return_type, const Vec<RcString> &wpc ) { default_enter( "def                  " ); }
    virtual void leave_def                       () { default_leave( "def                  " ); }
    virtual bool enter_test_class                ( RcString name, RcString cname, PI8 nb_scope_rec, const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &arg_splats, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats, RcString condition, RcString pertinence, SI32 def_pert_num, SI32 def_pert_exp, PI32 flags, const Vec<RcString> &block, const Vec<RcString> &inheritance_names, const Vec<RcString> &inheritance ) { enter_class( name, cname, nb_scope_rec, arg_names, arg_constraints, arg_def_vals, arg_splats, with_names, with_constraints, with_def_vals, with_splats, condition, pertinence, def_pert_num, def_pert_exp, flags, block, inheritance_names, inheritance ); return rec; }
    virtual void enter_class                     ( RcString name, RcString cname, PI8 nb_scope_rec, const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &arg_splats, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats, RcString condition, RcString pertinence, SI32 def_pert_num, SI32 def_pert_exp, PI32 flags, const Vec<RcString> &block, const Vec<RcString> &inheritance_names, const Vec<RcString> &inheritance ) { default_enter( "class                " ); }
    virtual void leave_class                     () { default_leave( "class                " ); }
    virtual bool enter_test_if_else              ( RcString cond, const Vec<RcString> &ok, const Vec<RcString> &ko ) { enter_if_else( cond, ok, ko ); return rec; }
    virtual void enter_if_else                   ( RcString cond, const Vec<RcString> &ok, const Vec<RcString> &ko ) { default_enter( "if_else              " ); }
    virtual void leave_if_else                   () { default_leave( "if_else              " ); }
    virtual bool enter_test_if                   ( RcString cond, const Vec<RcString> &ok ) { enter_if( cond, ok ); return rec; }
    virtual void enter_if                        ( RcString cond, const Vec<RcString> &ok ) { default_enter( "if                   " ); }
    virtual void leave_if                        () { default_leave( "if                   " ); }
    virtual bool enter_test_while                ( RcString cond, const Vec<RcString> &ok ) { enter_while( cond, ok ); return rec; }
    virtual void enter_while                     ( RcString cond, const Vec<RcString> &ok ) { default_enter( "while                " ); }
    virtual void leave_while                     () { default_leave( "while                " ); }
    virtual bool enter_test_return               ( RcString value ) { enter_return( value ); return rec; }
    virtual void enter_return                    ( RcString value ) { default_enter( "return               " ); }
    virtual void leave_return                    () { default_leave( "return               " ); }
    virtual bool enter_test_for                  ( RcString name, RcString container, const Vec<RcString> &block ) { enter_for( name, container, block ); return rec; }
    virtual void enter_for                       ( RcString name, RcString container, const Vec<RcString> &block ) { default_enter( "for                  " ); }
    virtual void leave_for                       () { default_leave( "for                  " ); }
    virtual bool enter_test_typeof               ( RcString value ) { enter_typeof( value ); return rec; }
    virtual void enter_typeof                    ( RcString value ) { default_enter( "typeof               " ); }
    virtual void leave_typeof                    () { default_leave( "typeof               " ); }
    virtual bool enter_test_sizeof               ( RcString value ) { enter_sizeof( value ); return rec; }
    virtual void enter_sizeof                    ( RcString value ) { default_enter( "sizeof               " ); }
    virtual void leave_sizeof                    () { default_leave( "sizeof               " ); }
    virtual bool enter_test_aligof               ( RcString value ) { enter_aligof( value ); return rec; }
    virtual void enter_aligof                    ( RcString value ) { default_enter( "aligof               " ); }
    virtual void leave_aligof                    () { default_leave( "aligof               " ); }
    virtual bool enter_test_sizeof_bits          ( RcString value ) { enter_sizeof_bits( value ); return rec; }
    virtual void enter_sizeof_bits               ( RcString value ) { default_enter( "sizeof_bits          " ); }
    virtual void leave_sizeof_bits               () { default_leave( "sizeof_bits          " ); }
    virtual bool enter_test_aligof_bits          ( RcString value ) { enter_aligof_bits( value ); return rec; }
    virtual void enter_aligof_bits               ( RcString value ) { default_enter( "aligof_bits          " ); }
    virtual void leave_aligof_bits               () { default_leave( "aligof_bits          " ); }
    virtual bool enter_test_lambda               ( const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &splats, RcString body ) { enter_lambda( arg_names, arg_constraints, arg_def_vals, splats, body ); return rec; }
    virtual void enter_lambda                    ( const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &splats, RcString body ) { default_enter( "lambda               " ); }
    virtual void leave_lambda                    () { default_leave( "lambda               " ); }
    virtual bool enter_test_and                  ( RcString v0, RcString v1 ) { enter_and( v0, v1 ); return rec; }
    virtual void enter_and                       ( RcString v0, RcString v1 ) { default_enter( "and                  " ); }
    virtual void leave_and                       () { default_leave( "and                  " ); }
    virtual bool enter_test_or                   ( RcString v0, RcString v1 ) { enter_or( v0, v1 ); return rec; }
    virtual void enter_or                        ( RcString v0, RcString v1 ) { default_enter( "or                   " ); }
    virtual void leave_or                        () { default_leave( "or                   " ); }
    virtual bool enter_test_vec                  ( const Vec<RcString> &values ) { enter_vec( values ); return rec; }
    virtual void enter_vec                       ( const Vec<RcString> &values ) { default_enter( "vec                  " ); }
    virtual void leave_vec                       () { default_leave( "vec                  " ); }
    virtual bool enter_test_map                  ( const Vec<RcString> &keys, const Vec<RcString> &values ) { enter_map( keys, values ); return rec; }
    virtual void enter_map                       ( const Vec<RcString> &keys, const Vec<RcString> &values ) { default_enter( "map                  " ); }
    virtual void leave_map                       () { default_leave( "map                  " ); }
    virtual bool enter_test_matrix               ( const Vec<RcString> &values, const Vec<size_t> &sizes ) { enter_matrix( values, sizes ); return rec; }
    virtual void enter_matrix                    ( const Vec<RcString> &values, const Vec<size_t> &sizes ) { default_enter( "matrix               " ); }
    virtual void leave_matrix                    () { default_leave( "matrix               " ); }
    virtual bool enter_test_raii                 ( const Vec<RcString> &values ) { enter_raii( values ); return rec; }
    virtual void enter_raii                      ( const Vec<RcString> &values ) { default_enter( "raii                 " ); }
    virtual void leave_raii                      () { default_leave( "raii                 " ); }
    virtual bool enter_test_info                 ( const Vec<RcString> &str, const Vec<RcString> &code ) { enter_info( str, code ); return rec; }
    virtual void enter_info                      ( const Vec<RcString> &str, const Vec<RcString> &code ) { default_enter( "info                 " ); }
    virtual void leave_info                      () { default_leave( "info                 " ); }
    virtual bool enter_test_assert               ( RcString str, RcString code ) { enter_assert( str, code ); return rec; }
    virtual void enter_assert                    ( RcString str, RcString code ) { default_enter( "assert               " ); }
    virtual void leave_assert                    () { default_leave( "assert               " ); }
    virtual bool enter_test_try_catch            ( RcString try_body, RcString arg_name, RcString arg_constraint, RcString catch_body, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats ) { enter_try_catch( try_body, arg_name, arg_constraint, catch_body, with_names, with_constraints, with_def_vals, with_splats ); return rec; }
    virtual void enter_try_catch                 ( RcString try_body, RcString arg_name, RcString arg_constraint, RcString catch_body, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats ) { default_enter( "try_catch            " ); }
    virtual void leave_try_catch                 () { default_leave( "try_catch            " ); }
    virtual bool enter_test_import               ( RcString filename, const Vec<RcString> &names, const Vec<RcString> &attrs ) { enter_import( filename, names, attrs ); return rec; }
    virtual void enter_import                    ( RcString filename, const Vec<RcString> &names, const Vec<RcString> &attrs ) { default_enter( "import               " ); }
    virtual void leave_import                    () { default_leave( "import               " ); }
    virtual bool enter_test_enum                 ( RcString name, const Vec<RcString> &items ) { enter_enum( name, items ); return rec; }
    virtual void enter_enum                      ( RcString name, const Vec<RcString> &items ) { default_enter( "enum                 " ); }
    virtual void leave_enum                      () { default_leave( "enum                 " ); }
    virtual void default_enter( const char *name ) {}
    virtual void default_leave( const char *name ) {}
    bool rec;
};
inline RcString read_Lex( Hpipe::BinStream<RcString> bs ) {
    char *ptr = bs.buf->ptr();
    size_t off = bs.read_unsigned();
    return off ? RcString{ *bs.buf, ptr + off, bs.buf->end() } : RcString{};
}
inline Vec<RcString> read_VecLex( Hpipe::BinStream<RcString> bs ) {
    Vec<RcString> res;
    res.resize( bs.read_unsigned() );
    for( size_t i = 0; i < res.size(); ++i )
        res[ i ] = read_Lex( bs );
    return res;
}
inline RcString read_String( Hpipe::BinStream<RcString> bs ) {
    size_t n = bs.read_unsigned();
    RcString res{ *bs.buf, bs.buf->ptr(), bs.buf->ptr() + n };
    bs.skip_some( n );
    return res;
}
inline Vec<size_t> read_VecPT( Hpipe::BinStream<RcString> bs ) {
    Vec<size_t> res;
    res.resize( bs.read_unsigned() );
    for( size_t i = 0; i < res.size(); ++i )
        res[ i ] = bs.read_unsigned();
    return res;
}
inline Vec<RcString> read_VecString( Hpipe::BinStream<RcString> bs ) {
    Vec<RcString> res;
    res.resize( bs.read_unsigned() );
    for( size_t i = 0; i < res.size(); ++i )
        res[ i ] = read_String( bs );
    return res;
}
inline Vec<Vec<RcString>> read_VecVecString( Hpipe::BinStream<RcString> bs ) {
    Vec<Vec<RcString>> res;
    res.resize( bs.read_unsigned() );
    for( size_t i = 0; i < res.size(); ++i )
        res[ i ] = read_VecString( bs );
    return res;
}
inline Vec<AstVisitor::Apply> read_VecApply( Hpipe::BinStream<RcString> bs ) {
    Vec<AstVisitor::Apply> res;
    res.resize( bs.read_unsigned() );
    for( size_t i = 0; i < res.size(); ++i ) {
        res[ i ].attr = read_String( bs );
        res[ i ].args = read_VecLex( bs );
        res[ i ].arg_names = read_VecString( bs );
    }
    return res;
}
inline void ast_visit( AstVisitor &visitor, RcString cm ) {
    Hpipe::BinStream<RcString> bs( &cm );
    PI8 cmd = bs.read_byte();
    if ( bs.error() )
        return;
    switch ( cmd ) {
    case 0: {
        if ( ! visitor.enter_test_pass() ) break;
        visitor.leave_pass();
        break;
    }
    case 1: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        if ( ! visitor.enter_test_variable( name ) ) break;
        visitor.leave_variable();
        break;
    }
    case 2: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        Vec<RcString> args = read_VecLex( bs );
        if ( ! visitor.enter_test_var_assembly( args ) ) break;
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_var_assembly();
        break;
    }
    case 3: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        if ( ! visitor.enter_test_continue() ) break;
        visitor.leave_continue();
        break;
    }
    case 4: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        if ( ! visitor.enter_test_break() ) break;
        visitor.leave_break();
        break;
    }
    case 5: {
        if ( ! visitor.enter_test_false() ) break;
        visitor.leave_false();
        break;
    }
    case 6: {
        if ( ! visitor.enter_test_true() ) break;
        visitor.leave_true();
        break;
    }
    case 7: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        if ( ! visitor.enter_test_self() ) break;
        visitor.leave_self();
        break;
    }
    case 8: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        if ( ! visitor.enter_test_this() ) break;
        visitor.leave_this();
        break;
    }
    case 9: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_String( bs );
        if ( ! visitor.enter_test_number( value ) ) break;
        visitor.leave_number();
        break;
    }
    case 10: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_String( bs );
        if ( ! visitor.enter_test_string( value ) ) break;
        visitor.leave_string();
        break;
    }
    case 11: {
        RcString obj = read_Lex( bs );
        RcString name = read_String( bs );
        if ( ! visitor.enter_test_get_attr( obj, name ) ) break;
        ast_visit( visitor, obj );
        visitor.leave_get_attr();
        break;
    }
    case 12: {
        RcString obj = read_Lex( bs );
        RcString name = read_String( bs );
        if ( ! visitor.enter_test_scope_resolution( obj, name ) ) break;
        ast_visit( visitor, obj );
        visitor.leave_scope_resolution();
        break;
    }
    case 13: {
        RcString obj = read_Lex( bs );
        RcString name = read_String( bs );
        if ( ! visitor.enter_test_get_attr_ptr( obj, name ) ) break;
        ast_visit( visitor, obj );
        visitor.leave_get_attr_ptr();
        break;
    }
    case 14: {
        RcString obj = read_Lex( bs );
        Vec<RcString> args = read_VecLex( bs );
        if ( ! visitor.enter_test_get_attr_calc( obj, args ) ) break;
        ast_visit( visitor, obj );
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_get_attr_calc();
        break;
    }
    case 15: {
        RcString obj = read_Lex( bs );
        Vec<RcString> args = read_VecLex( bs );
        if ( ! visitor.enter_test_scope_resolution_calc( obj, args ) ) break;
        ast_visit( visitor, obj );
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_scope_resolution_calc();
        break;
    }
    case 16: {
        RcString obj = read_Lex( bs );
        Vec<RcString> args = read_VecLex( bs );
        if ( ! visitor.enter_test_get_attr_ptr_calc( obj, args ) ) break;
        ast_visit( visitor, obj );
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_get_attr_ptr_calc();
        break;
    }
    case 17: {
        Vec<RcString> items = read_VecLex( bs );
        if ( ! visitor.enter_test_ss_block( items ) ) break;
        for( const RcString &cm : items )
            ast_visit( visitor, cm );
        visitor.leave_ss_block();
        break;
    }
    case 18: {
        Vec<RcString> items = read_VecLex( bs );
        if ( ! visitor.enter_test_block( items ) ) break;
        for( const RcString &cm : items )
            ast_visit( visitor, cm );
        visitor.leave_block();
        break;
    }
    case 19: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        Vec<RcString> args = read_VecLex( bs );
        if ( ! visitor.enter_test_apply_op( name, args ) ) break;
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_apply_op();
        break;
    }
    case 20: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString f = read_Lex( bs );
        Vec<RcString> args = read_VecLex( bs );
        Vec<RcString> names = read_VecString( bs );
        Vec<size_t> splats = read_VecPT( bs );
        if ( ! visitor.enter_test_apply( f, args, names, splats ) ) break;
        ast_visit( visitor, f );
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_apply();
        break;
    }
    case 21: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString f = read_Lex( bs );
        Vec<RcString> args = read_VecLex( bs );
        Vec<RcString> names = read_VecString( bs );
        Vec<size_t> splats = read_VecPT( bs );
        if ( ! visitor.enter_test_select( f, args, names, splats ) ) break;
        ast_visit( visitor, f );
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_select();
        break;
    }
    case 22: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString f = read_Lex( bs );
        Vec<RcString> args = read_VecLex( bs );
        Vec<RcString> names = read_VecString( bs );
        Vec<size_t> splats = read_VecPT( bs );
        if ( ! visitor.enter_test_chbeba( f, args, names, splats ) ) break;
        ast_visit( visitor, f );
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_chbeba();
        break;
    }
    case 23: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        Vec<RcString> args = read_VecLex( bs );
        Vec<RcString> names = read_VecString( bs );
        Vec<size_t> splats = read_VecPT( bs );
        if ( ! visitor.enter_test_init_of( name, args, names, splats ) ) break;
        for( const RcString &cm : args )
            ast_visit( visitor, cm );
        visitor.leave_init_of();
        break;
    }
    case 24: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        RcString cname = read_Lex( bs );
        PI8 nb_scope_rec = bs.read_byte();
        RcString value = read_Lex( bs );
        PI8 flags = bs.read_byte();
        if ( ! visitor.enter_test_assign( name, cname, nb_scope_rec, value, flags ) ) break;
        ast_visit( visitor, cname );
        ast_visit( visitor, value );
        visitor.leave_assign();
        break;
    }
    case 25: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        Vec<RcString> names = read_VecString( bs );
        Vec<RcString> equal = read_VecLex( bs );
        Vec<RcString> types = read_VecLex( bs );
        RcString value = read_Lex( bs );
        PI8 flags = bs.read_byte();
        if ( ! visitor.enter_test_destruct_assign( names, equal, types, value, flags ) ) break;
        for( const RcString &cm : equal )
            ast_visit( visitor, cm );
        for( const RcString &cm : types )
            ast_visit( visitor, cm );
        ast_visit( visitor, value );
        visitor.leave_destruct_assign();
        break;
    }
    case 26: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        RcString cname = read_Lex( bs );
        PI8 nb_scope_rec = bs.read_byte();
        Vec<RcString> arg_names = read_VecString( bs );
        Vec<RcString> arg_constraints = read_VecLex( bs );
        Vec<RcString> arg_def_vals = read_VecLex( bs );
        Vec<size_t> arg_splats = read_VecPT( bs );
        Vec<RcString> with_names = read_VecString( bs );
        Vec<RcString> with_constraints = read_VecLex( bs );
        Vec<RcString> with_def_vals = read_VecLex( bs );
        Vec<size_t> with_splats = read_VecPT( bs );
        RcString condition = read_Lex( bs );
        RcString pertinence = read_Lex( bs );
        SI32 def_pert_num = bs.read_signed();
        SI32 def_pert_exp = bs.read_signed();
        SI32 flags = bs.read_unsigned();
        Vec<RcString> block = read_VecLex( bs );
        RcString self_constraint = read_Lex( bs );
        RcString return_type = read_Lex( bs );
        Vec<RcString> wpc = read_VecLex( bs );
        if ( ! visitor.enter_test_def( name, cname, nb_scope_rec, arg_names, arg_constraints, arg_def_vals, arg_splats, with_names, with_constraints, with_def_vals, with_splats, condition, pertinence, def_pert_num, def_pert_exp, flags, block, self_constraint, return_type, wpc ) ) break;
        ast_visit( visitor, cname );
        for( const RcString &cm : arg_constraints )
            ast_visit( visitor, cm );
        for( const RcString &cm : arg_def_vals )
            ast_visit( visitor, cm );
        for( const RcString &cm : with_constraints )
            ast_visit( visitor, cm );
        for( const RcString &cm : with_def_vals )
            ast_visit( visitor, cm );
        ast_visit( visitor, condition );
        ast_visit( visitor, pertinence );
        for( const RcString &cm : block )
            ast_visit( visitor, cm );
        ast_visit( visitor, self_constraint );
        ast_visit( visitor, return_type );
        for( const RcString &cm : wpc )
            ast_visit( visitor, cm );
        visitor.leave_def();
        break;
    }
    case 27: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        RcString cname = read_Lex( bs );
        PI8 nb_scope_rec = bs.read_byte();
        Vec<RcString> arg_names = read_VecString( bs );
        Vec<RcString> arg_constraints = read_VecLex( bs );
        Vec<RcString> arg_def_vals = read_VecLex( bs );
        Vec<size_t> arg_splats = read_VecPT( bs );
        Vec<RcString> with_names = read_VecString( bs );
        Vec<RcString> with_constraints = read_VecLex( bs );
        Vec<RcString> with_def_vals = read_VecLex( bs );
        Vec<size_t> with_splats = read_VecPT( bs );
        RcString condition = read_Lex( bs );
        RcString pertinence = read_Lex( bs );
        SI32 def_pert_num = bs.read_signed();
        SI32 def_pert_exp = bs.read_signed();
        SI32 flags = bs.read_unsigned();
        Vec<RcString> block = read_VecLex( bs );
        Vec<RcString> inheritance_names = read_VecString( bs );
        Vec<RcString> inheritance = read_VecLex( bs );
        if ( ! visitor.enter_test_class( name, cname, nb_scope_rec, arg_names, arg_constraints, arg_def_vals, arg_splats, with_names, with_constraints, with_def_vals, with_splats, condition, pertinence, def_pert_num, def_pert_exp, flags, block, inheritance_names, inheritance ) ) break;
        ast_visit( visitor, cname );
        for( const RcString &cm : arg_constraints )
            ast_visit( visitor, cm );
        for( const RcString &cm : arg_def_vals )
            ast_visit( visitor, cm );
        for( const RcString &cm : with_constraints )
            ast_visit( visitor, cm );
        for( const RcString &cm : with_def_vals )
            ast_visit( visitor, cm );
        ast_visit( visitor, condition );
        ast_visit( visitor, pertinence );
        for( const RcString &cm : block )
            ast_visit( visitor, cm );
        for( const RcString &cm : inheritance )
            ast_visit( visitor, cm );
        visitor.leave_class();
        break;
    }
    case 28: {
        RcString cond = read_Lex( bs );
        Vec<RcString> ok = read_VecLex( bs );
        Vec<RcString> ko = read_VecLex( bs );
        if ( ! visitor.enter_test_if_else( cond, ok, ko ) ) break;
        ast_visit( visitor, cond );
        for( const RcString &cm : ok )
            ast_visit( visitor, cm );
        for( const RcString &cm : ko )
            ast_visit( visitor, cm );
        visitor.leave_if_else();
        break;
    }
    case 29: {
        RcString cond = read_Lex( bs );
        Vec<RcString> ok = read_VecLex( bs );
        if ( ! visitor.enter_test_if( cond, ok ) ) break;
        ast_visit( visitor, cond );
        for( const RcString &cm : ok )
            ast_visit( visitor, cm );
        visitor.leave_if();
        break;
    }
    case 30: {
        RcString cond = read_Lex( bs );
        Vec<RcString> ok = read_VecLex( bs );
        if ( ! visitor.enter_test_while( cond, ok ) ) break;
        ast_visit( visitor, cond );
        for( const RcString &cm : ok )
            ast_visit( visitor, cm );
        visitor.leave_while();
        break;
    }
    case 31: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_Lex( bs );
        if ( ! visitor.enter_test_return( value ) ) break;
        ast_visit( visitor, value );
        visitor.leave_return();
        break;
    }
    case 32: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        RcString container = read_Lex( bs );
        Vec<RcString> block = read_VecLex( bs );
        if ( ! visitor.enter_test_for( name, container, block ) ) break;
        ast_visit( visitor, container );
        for( const RcString &cm : block )
            ast_visit( visitor, cm );
        visitor.leave_for();
        break;
    }
    case 33: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_Lex( bs );
        if ( ! visitor.enter_test_typeof( value ) ) break;
        ast_visit( visitor, value );
        visitor.leave_typeof();
        break;
    }
    case 34: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_Lex( bs );
        if ( ! visitor.enter_test_sizeof( value ) ) break;
        ast_visit( visitor, value );
        visitor.leave_sizeof();
        break;
    }
    case 35: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_Lex( bs );
        if ( ! visitor.enter_test_aligof( value ) ) break;
        ast_visit( visitor, value );
        visitor.leave_aligof();
        break;
    }
    case 36: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_Lex( bs );
        if ( ! visitor.enter_test_sizeof_bits( value ) ) break;
        ast_visit( visitor, value );
        visitor.leave_sizeof_bits();
        break;
    }
    case 37: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString value = read_Lex( bs );
        if ( ! visitor.enter_test_aligof_bits( value ) ) break;
        ast_visit( visitor, value );
        visitor.leave_aligof_bits();
        break;
    }
    case 38: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        Vec<RcString> arg_names = read_VecString( bs );
        Vec<RcString> arg_constraints = read_VecLex( bs );
        Vec<RcString> arg_def_vals = read_VecLex( bs );
        Vec<size_t> splats = read_VecPT( bs );
        RcString body = read_Lex( bs );
        if ( ! visitor.enter_test_lambda( arg_names, arg_constraints, arg_def_vals, splats, body ) ) break;
        for( const RcString &cm : arg_constraints )
            ast_visit( visitor, cm );
        for( const RcString &cm : arg_def_vals )
            ast_visit( visitor, cm );
        ast_visit( visitor, body );
        visitor.leave_lambda();
        break;
    }
    case 39: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString v0 = read_Lex( bs );
        RcString v1 = read_Lex( bs );
        if ( ! visitor.enter_test_and( v0, v1 ) ) break;
        ast_visit( visitor, v0 );
        ast_visit( visitor, v1 );
        visitor.leave_and();
        break;
    }
    case 40: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString v0 = read_Lex( bs );
        RcString v1 = read_Lex( bs );
        if ( ! visitor.enter_test_or( v0, v1 ) ) break;
        ast_visit( visitor, v0 );
        ast_visit( visitor, v1 );
        visitor.leave_or();
        break;
    }
    case 41: {
        Vec<RcString> values = read_VecLex( bs );
        if ( ! visitor.enter_test_vec( values ) ) break;
        for( const RcString &cm : values )
            ast_visit( visitor, cm );
        visitor.leave_vec();
        break;
    }
    case 42: {
        Vec<RcString> keys = read_VecLex( bs );
        Vec<RcString> values = read_VecLex( bs );
        if ( ! visitor.enter_test_map( keys, values ) ) break;
        for( const RcString &cm : keys )
            ast_visit( visitor, cm );
        for( const RcString &cm : values )
            ast_visit( visitor, cm );
        visitor.leave_map();
        break;
    }
    case 43: {
        Vec<RcString> values = read_VecLex( bs );
        Vec<size_t> sizes = read_VecPT( bs );
        if ( ! visitor.enter_test_matrix( values, sizes ) ) break;
        for( const RcString &cm : values )
            ast_visit( visitor, cm );
        visitor.leave_matrix();
        break;
    }
    case 44: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        Vec<RcString> values = read_VecLex( bs );
        if ( ! visitor.enter_test_raii( values ) ) break;
        for( const RcString &cm : values )
            ast_visit( visitor, cm );
        visitor.leave_raii();
        break;
    }
    case 45: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        Vec<RcString> str = read_VecString( bs );
        Vec<RcString> code = read_VecLex( bs );
        if ( ! visitor.enter_test_info( str, code ) ) break;
        for( const RcString &cm : code )
            ast_visit( visitor, cm );
        visitor.leave_info();
        break;
    }
    case 46: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString str = read_String( bs );
        RcString code = read_Lex( bs );
        if ( ! visitor.enter_test_assert( str, code ) ) break;
        ast_visit( visitor, code );
        visitor.leave_assert();
        break;
    }
    case 47: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString try_body = read_Lex( bs );
        RcString arg_name = read_String( bs );
        RcString arg_constraint = read_Lex( bs );
        RcString catch_body = read_Lex( bs );
        Vec<RcString> with_names = read_VecString( bs );
        Vec<RcString> with_constraints = read_VecLex( bs );
        Vec<RcString> with_def_vals = read_VecLex( bs );
        Vec<size_t> with_splats = read_VecPT( bs );
        if ( ! visitor.enter_test_try_catch( try_body, arg_name, arg_constraint, catch_body, with_names, with_constraints, with_def_vals, with_splats ) ) break;
        ast_visit( visitor, try_body );
        ast_visit( visitor, arg_constraint );
        ast_visit( visitor, catch_body );
        for( const RcString &cm : with_constraints )
            ast_visit( visitor, cm );
        for( const RcString &cm : with_def_vals )
            ast_visit( visitor, cm );
        visitor.leave_try_catch();
        break;
    }
    case 48: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString filename = read_String( bs );
        Vec<RcString> names = read_VecString( bs );
        Vec<RcString> attrs = read_VecString( bs );
        if ( ! visitor.enter_test_import( filename, names, attrs ) ) break;
        visitor.leave_import();
        break;
    }
    case 49: {
        if ( size_t nsrc = bs.read_unsigned() ) visitor.set_src( nsrc - 1, bs.read_unsigned() );
        RcString name = read_String( bs );
        Vec<RcString> items = read_VecString( bs );
        if ( ! visitor.enter_test_enum( name, items ) ) break;
        visitor.leave_enum();
        break;
    }
    }
}
inline void ast_visit_VecLex( AstVisitor &visitor, RcString cm ) {
    Hpipe::BinStream<RcString> bs( &cm );
    for( size_t n = bs.read_unsigned(); n--; )
        ast_visit( visitor, read_Lex( bs ) );
}

struct AstVisitorDisplay : public AstVisitor {
    AstVisitorDisplay( std::ostream &os, std::string sp = "" ) : os( os ), sp( sp ) {}
    bool enter_test_pass() override {
        os << "pass(";
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_variable( RcString name ) override {
        os << "variable(";
        os << "name=" << name;
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_var_assembly( const Vec<RcString> &args ) override {
        os << "var_assembly(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_continue() override {
        os << "continue(";
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_break() override {
        os << "break(";
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_false() override {
        os << "false(";
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_true() override {
        os << "true(";
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_self() override {
        os << "self(";
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_this() override {
        os << "this(";
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_number( RcString value ) override {
        os << "number(";
        os << "value=" << value;
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_string( RcString value ) override {
        os << "string(";
        os << "value=" << value;
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_get_attr( RcString obj, RcString name ) override {
        os << "get_attr(";
        os << "name=" << name;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "obj=\n"; is(); os << sp; if ( obj.size() ) { ast_visit( *this, obj ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_scope_resolution( RcString obj, RcString name ) override {
        os << "scope_resolution(";
        os << "name=" << name;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "obj=\n"; is(); os << sp; if ( obj.size() ) { ast_visit( *this, obj ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_get_attr_ptr( RcString obj, RcString name ) override {
        os << "get_attr_ptr(";
        os << "name=" << name;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "obj=\n"; is(); os << sp; if ( obj.size() ) { ast_visit( *this, obj ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_get_attr_calc( RcString obj, const Vec<RcString> &args ) override {
        os << "get_attr_calc(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "obj=\n"; is(); os << sp; if ( obj.size() ) { ast_visit( *this, obj ); } else os << "null\n"; ds();
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_scope_resolution_calc( RcString obj, const Vec<RcString> &args ) override {
        os << "scope_resolution_calc(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "obj=\n"; is(); os << sp; if ( obj.size() ) { ast_visit( *this, obj ); } else os << "null\n"; ds();
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_get_attr_ptr_calc( RcString obj, const Vec<RcString> &args ) override {
        os << "get_attr_ptr_calc(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "obj=\n"; is(); os << sp; if ( obj.size() ) { ast_visit( *this, obj ); } else os << "null\n"; ds();
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_ss_block( const Vec<RcString> &items ) override {
        os << "ss_block(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "items=\n"; is(); for( size_t i = 0; i < items.size(); ++i ) { os << sp; if ( items[ i ].size() ) { is(); ast_visit( *this, items[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_block( const Vec<RcString> &items ) override {
        os << "block(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "items=\n"; is(); for( size_t i = 0; i < items.size(); ++i ) { os << sp; if ( items[ i ].size() ) { is(); ast_visit( *this, items[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_apply_op( RcString name, const Vec<RcString> &args ) override {
        os << "apply_op(";
        os << "name=" << name;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_apply( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) override {
        os << "apply(";
        os << "names=" << names;
        os << ",splats=" << splats;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "f=\n"; is(); os << sp; if ( f.size() ) { ast_visit( *this, f ); } else os << "null\n"; ds();
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_select( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) override {
        os << "select(";
        os << "names=" << names;
        os << ",splats=" << splats;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "f=\n"; is(); os << sp; if ( f.size() ) { ast_visit( *this, f ); } else os << "null\n"; ds();
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_chbeba( RcString f, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) override {
        os << "chbeba(";
        os << "names=" << names;
        os << ",splats=" << splats;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "f=\n"; is(); os << sp; if ( f.size() ) { ast_visit( *this, f ); } else os << "null\n"; ds();
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_init_of( RcString name, const Vec<RcString> &args, const Vec<RcString> &names, const Vec<size_t> &splats ) override {
        os << "init_of(";
        os << "name=" << name;
        os << ",names=" << names;
        os << ",splats=" << splats;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "args=\n"; is(); for( size_t i = 0; i < args.size(); ++i ) { os << sp; if ( args[ i ].size() ) { is(); ast_visit( *this, args[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_assign( RcString name, RcString cname, PI8 nb_scope_rec, RcString value, PI8 flags ) override {
        os << "assign(";
        os << "name=" << name;
        os << ",nb_scope_rec=" << PI32( nb_scope_rec );
        os << ",flags=" << PI32( flags );
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "cname=\n"; is(); os << sp; if ( cname.size() ) { ast_visit( *this, cname ); } else os << "null\n"; ds();
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_destruct_assign( const Vec<RcString> &names, const Vec<RcString> &equal, const Vec<RcString> &types, RcString value, PI8 flags ) override {
        os << "destruct_assign(";
        os << "names=" << names;
        os << ",flags=" << PI32( flags );
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "equal=\n"; is(); for( size_t i = 0; i < equal.size(); ++i ) { os << sp; if ( equal[ i ].size() ) { is(); ast_visit( *this, equal[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "types=\n"; is(); for( size_t i = 0; i < types.size(); ++i ) { os << sp; if ( types[ i ].size() ) { is(); ast_visit( *this, types[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_def( RcString name, RcString cname, PI8 nb_scope_rec, const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &arg_splats, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats, RcString condition, RcString pertinence, SI32 def_pert_num, SI32 def_pert_exp, PI32 flags, const Vec<RcString> &block, RcString self_constraint, RcString return_type, const Vec<RcString> &wpc ) override {
        os << "def(";
        os << "name=" << name;
        os << ",nb_scope_rec=" << PI32( nb_scope_rec );
        os << ",arg_names=" << arg_names;
        os << ",arg_splats=" << arg_splats;
        os << ",with_names=" << with_names;
        os << ",with_splats=" << with_splats;
        os << ",def_pert_num=" << def_pert_num;
        os << ",def_pert_exp=" << def_pert_exp;
        os << ",flags=" << flags;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "cname=\n"; is(); os << sp; if ( cname.size() ) { ast_visit( *this, cname ); } else os << "null\n"; ds();
        os << sp << "arg_constraints=\n"; is(); for( size_t i = 0; i < arg_constraints.size(); ++i ) { os << sp; if ( arg_constraints[ i ].size() ) { is(); ast_visit( *this, arg_constraints[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "arg_def_vals=\n"; is(); for( size_t i = 0; i < arg_def_vals.size(); ++i ) { os << sp; if ( arg_def_vals[ i ].size() ) { is(); ast_visit( *this, arg_def_vals[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "with_constraints=\n"; is(); for( size_t i = 0; i < with_constraints.size(); ++i ) { os << sp; if ( with_constraints[ i ].size() ) { is(); ast_visit( *this, with_constraints[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "with_def_vals=\n"; is(); for( size_t i = 0; i < with_def_vals.size(); ++i ) { os << sp; if ( with_def_vals[ i ].size() ) { is(); ast_visit( *this, with_def_vals[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "condition=\n"; is(); os << sp; if ( condition.size() ) { ast_visit( *this, condition ); } else os << "null\n"; ds();
        os << sp << "pertinence=\n"; is(); os << sp; if ( pertinence.size() ) { ast_visit( *this, pertinence ); } else os << "null\n"; ds();
        os << sp << "block=\n"; is(); for( size_t i = 0; i < block.size(); ++i ) { os << sp; if ( block[ i ].size() ) { is(); ast_visit( *this, block[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "self_constraint=\n"; is(); os << sp; if ( self_constraint.size() ) { ast_visit( *this, self_constraint ); } else os << "null\n"; ds();
        os << sp << "return_type=\n"; is(); os << sp; if ( return_type.size() ) { ast_visit( *this, return_type ); } else os << "null\n"; ds();
        os << sp << "wpc=\n"; is(); for( size_t i = 0; i < wpc.size(); ++i ) { os << sp; if ( wpc[ i ].size() ) { is(); ast_visit( *this, wpc[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_class( RcString name, RcString cname, PI8 nb_scope_rec, const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &arg_splats, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats, RcString condition, RcString pertinence, SI32 def_pert_num, SI32 def_pert_exp, PI32 flags, const Vec<RcString> &block, const Vec<RcString> &inheritance_names, const Vec<RcString> &inheritance ) override {
        os << "class(";
        os << "name=" << name;
        os << ",nb_scope_rec=" << PI32( nb_scope_rec );
        os << ",arg_names=" << arg_names;
        os << ",arg_splats=" << arg_splats;
        os << ",with_names=" << with_names;
        os << ",with_splats=" << with_splats;
        os << ",def_pert_num=" << def_pert_num;
        os << ",def_pert_exp=" << def_pert_exp;
        os << ",flags=" << flags;
        os << ",inheritance_names=" << inheritance_names;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "cname=\n"; is(); os << sp; if ( cname.size() ) { ast_visit( *this, cname ); } else os << "null\n"; ds();
        os << sp << "arg_constraints=\n"; is(); for( size_t i = 0; i < arg_constraints.size(); ++i ) { os << sp; if ( arg_constraints[ i ].size() ) { is(); ast_visit( *this, arg_constraints[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "arg_def_vals=\n"; is(); for( size_t i = 0; i < arg_def_vals.size(); ++i ) { os << sp; if ( arg_def_vals[ i ].size() ) { is(); ast_visit( *this, arg_def_vals[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "with_constraints=\n"; is(); for( size_t i = 0; i < with_constraints.size(); ++i ) { os << sp; if ( with_constraints[ i ].size() ) { is(); ast_visit( *this, with_constraints[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "with_def_vals=\n"; is(); for( size_t i = 0; i < with_def_vals.size(); ++i ) { os << sp; if ( with_def_vals[ i ].size() ) { is(); ast_visit( *this, with_def_vals[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "condition=\n"; is(); os << sp; if ( condition.size() ) { ast_visit( *this, condition ); } else os << "null\n"; ds();
        os << sp << "pertinence=\n"; is(); os << sp; if ( pertinence.size() ) { ast_visit( *this, pertinence ); } else os << "null\n"; ds();
        os << sp << "block=\n"; is(); for( size_t i = 0; i < block.size(); ++i ) { os << sp; if ( block[ i ].size() ) { is(); ast_visit( *this, block[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "inheritance=\n"; is(); for( size_t i = 0; i < inheritance.size(); ++i ) { os << sp; if ( inheritance[ i ].size() ) { is(); ast_visit( *this, inheritance[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_if_else( RcString cond, const Vec<RcString> &ok, const Vec<RcString> &ko ) override {
        os << "if_else(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "cond=\n"; is(); os << sp; if ( cond.size() ) { ast_visit( *this, cond ); } else os << "null\n"; ds();
        os << sp << "ok=\n"; is(); for( size_t i = 0; i < ok.size(); ++i ) { os << sp; if ( ok[ i ].size() ) { is(); ast_visit( *this, ok[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "ko=\n"; is(); for( size_t i = 0; i < ko.size(); ++i ) { os << sp; if ( ko[ i ].size() ) { is(); ast_visit( *this, ko[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_if( RcString cond, const Vec<RcString> &ok ) override {
        os << "if(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "cond=\n"; is(); os << sp; if ( cond.size() ) { ast_visit( *this, cond ); } else os << "null\n"; ds();
        os << sp << "ok=\n"; is(); for( size_t i = 0; i < ok.size(); ++i ) { os << sp; if ( ok[ i ].size() ) { is(); ast_visit( *this, ok[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_while( RcString cond, const Vec<RcString> &ok ) override {
        os << "while(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "cond=\n"; is(); os << sp; if ( cond.size() ) { ast_visit( *this, cond ); } else os << "null\n"; ds();
        os << sp << "ok=\n"; is(); for( size_t i = 0; i < ok.size(); ++i ) { os << sp; if ( ok[ i ].size() ) { is(); ast_visit( *this, ok[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_return( RcString value ) override {
        os << "return(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_for( RcString name, RcString container, const Vec<RcString> &block ) override {
        os << "for(";
        os << "name=" << name;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "container=\n"; is(); os << sp; if ( container.size() ) { ast_visit( *this, container ); } else os << "null\n"; ds();
        os << sp << "block=\n"; is(); for( size_t i = 0; i < block.size(); ++i ) { os << sp; if ( block[ i ].size() ) { is(); ast_visit( *this, block[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_typeof( RcString value ) override {
        os << "typeof(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_sizeof( RcString value ) override {
        os << "sizeof(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_aligof( RcString value ) override {
        os << "aligof(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_sizeof_bits( RcString value ) override {
        os << "sizeof_bits(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_aligof_bits( RcString value ) override {
        os << "aligof_bits(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "value=\n"; is(); os << sp; if ( value.size() ) { ast_visit( *this, value ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_lambda( const Vec<RcString> &arg_names, const Vec<RcString> &arg_constraints, const Vec<RcString> &arg_def_vals, const Vec<size_t> &splats, RcString body ) override {
        os << "lambda(";
        os << "arg_names=" << arg_names;
        os << ",splats=" << splats;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "arg_constraints=\n"; is(); for( size_t i = 0; i < arg_constraints.size(); ++i ) { os << sp; if ( arg_constraints[ i ].size() ) { is(); ast_visit( *this, arg_constraints[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "arg_def_vals=\n"; is(); for( size_t i = 0; i < arg_def_vals.size(); ++i ) { os << sp; if ( arg_def_vals[ i ].size() ) { is(); ast_visit( *this, arg_def_vals[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "body=\n"; is(); os << sp; if ( body.size() ) { ast_visit( *this, body ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_and( RcString v0, RcString v1 ) override {
        os << "and(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "v0=\n"; is(); os << sp; if ( v0.size() ) { ast_visit( *this, v0 ); } else os << "null\n"; ds();
        os << sp << "v1=\n"; is(); os << sp; if ( v1.size() ) { ast_visit( *this, v1 ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_or( RcString v0, RcString v1 ) override {
        os << "or(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "v0=\n"; is(); os << sp; if ( v0.size() ) { ast_visit( *this, v0 ); } else os << "null\n"; ds();
        os << sp << "v1=\n"; is(); os << sp; if ( v1.size() ) { ast_visit( *this, v1 ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_vec( const Vec<RcString> &values ) override {
        os << "vec(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "values=\n"; is(); for( size_t i = 0; i < values.size(); ++i ) { os << sp; if ( values[ i ].size() ) { is(); ast_visit( *this, values[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_map( const Vec<RcString> &keys, const Vec<RcString> &values ) override {
        os << "map(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "keys=\n"; is(); for( size_t i = 0; i < keys.size(); ++i ) { os << sp; if ( keys[ i ].size() ) { is(); ast_visit( *this, keys[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "values=\n"; is(); for( size_t i = 0; i < values.size(); ++i ) { os << sp; if ( values[ i ].size() ) { is(); ast_visit( *this, values[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_matrix( const Vec<RcString> &values, const Vec<size_t> &sizes ) override {
        os << "matrix(";
        os << "sizes=" << sizes;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "values=\n"; is(); for( size_t i = 0; i < values.size(); ++i ) { os << sp; if ( values[ i ].size() ) { is(); ast_visit( *this, values[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_raii( const Vec<RcString> &values ) override {
        os << "raii(";
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "values=\n"; is(); for( size_t i = 0; i < values.size(); ++i ) { os << sp; if ( values[ i ].size() ) { is(); ast_visit( *this, values[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_info( const Vec<RcString> &str, const Vec<RcString> &code ) override {
        os << "info(";
        os << "str=" << str;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "code=\n"; is(); for( size_t i = 0; i < code.size(); ++i ) { os << sp; if ( code[ i ].size() ) { is(); ast_visit( *this, code[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_assert( RcString str, RcString code ) override {
        os << "assert(";
        os << "str=" << str;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "code=\n"; is(); os << sp; if ( code.size() ) { ast_visit( *this, code ); } else os << "null\n"; ds();
        return false;
    }
    bool enter_test_try_catch( RcString try_body, RcString arg_name, RcString arg_constraint, RcString catch_body, const Vec<RcString> &with_names, const Vec<RcString> &with_constraints, const Vec<RcString> &with_def_vals, const Vec<size_t> &with_splats ) override {
        os << "try_catch(";
        os << "arg_name=" << arg_name;
        os << ",with_names=" << with_names;
        os << ",with_splats=" << with_splats;
        os << ")";
        RaiiSave<std::string> rs( sp, sp + "  " );
        os << "\n";
        os << sp << "try_body=\n"; is(); os << sp; if ( try_body.size() ) { ast_visit( *this, try_body ); } else os << "null\n"; ds();
        os << sp << "arg_constraint=\n"; is(); os << sp; if ( arg_constraint.size() ) { ast_visit( *this, arg_constraint ); } else os << "null\n"; ds();
        os << sp << "catch_body=\n"; is(); os << sp; if ( catch_body.size() ) { ast_visit( *this, catch_body ); } else os << "null\n"; ds();
        os << sp << "with_constraints=\n"; is(); for( size_t i = 0; i < with_constraints.size(); ++i ) { os << sp; if ( with_constraints[ i ].size() ) { is(); ast_visit( *this, with_constraints[ i ] ); ds(); } else os << "null\n"; } ds();
        os << sp << "with_def_vals=\n"; is(); for( size_t i = 0; i < with_def_vals.size(); ++i ) { os << sp; if ( with_def_vals[ i ].size() ) { is(); ast_visit( *this, with_def_vals[ i ] ); ds(); } else os << "null\n"; } ds();
        return false;
    }
    bool enter_test_import( RcString filename, const Vec<RcString> &names, const Vec<RcString> &attrs ) override {
        os << "import(";
        os << "filename=" << filename;
        os << ",names=" << names;
        os << ",attrs=" << attrs;
        os << ")";
        os << "\n";
        return false;
    }
    bool enter_test_enum( RcString name, const Vec<RcString> &items ) override {
        os << "enum(";
        os << "name=" << name;
        os << ",items=" << items;
        os << ")";
        os << "\n";
        return false;
    }
    void is( int n = 2 ) { while( n-- ) sp += ' '; }
    void ds( int n = 2 ) { sp.resize( sp.size() - n ); }
    std::ostream &os;
    std::string   sp;
};
