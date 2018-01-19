#pragma once

#include "../System/Stream.h"
class Reg;

/**
*/
struct CodegenData {
    CodegenData() {}

    SI32       num_in_sched;
    Vec<Reg *> out_regs;
};
