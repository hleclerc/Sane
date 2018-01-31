#pragma once

#include "../System/StreamPrio.h"
#include "../System/StreamSep.h"
#include "Codegen.h"
#include <map>
#include <set>

/**
*/
class Codegen_C : public Codegen {
public:
    using MTR = std::map<TypeInSane *,String>;

    Codegen_C( Codegen_C *parent = 0 );

    virtual void       gen_code_for       ( const Vec<Inst *> &targets ) override;
    virtual String     code               () override;

    virtual void       write_block        ( StreamSep &os, const Vec<Inst *> &out ) override;
    virtual void       write_repr         ( std::ostream &os, TypeInSane *type ) override;
    virtual void       write_repr         ( std::ostream &os, const Value &value, int prio, int flags ) override;
    virtual Reg       *new_reg_for        ( Inst *inst, TypeInSane *type, int nout ) override;

    virtual String     write_func_write_fd( TypeInSane *type ) override;

    virtual Codegen   *new_child          () override;


protected:
    void               get_scheduling     ( Vec<Inst *> &sched, const Vec<Inst *> &out );
    bool               write_repr_rec     ( StreamPrio &os, const std::function<void(StreamPrio&)> &reg_writer, TypeInSane *reg_type, TypeInSane *tgt_type, int tgt_offset );
    void               write_func_itoa    ();
    void               add_include        ( const String &include );

    std::ostringstream declarations;
    std::ostringstream main_block;
    MTR                type_reprs;
    std::set<String>   decl_types;
    std::set<String>   decl_funcs;
    Vec<String>        includes;
    Codegen_C         *parent;
    int                nb_reg;
};
