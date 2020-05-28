#ifndef VM_OP_H
#define VM_OP_H

#include "memory/VMMem.h"
#include "utils.h"
#include "ConditionalMicroOp.h"
#include "RPN_MicroOp.h"
#include "alu_rpn/RPN_Calculator.h"

#include <memory>

class VMOp{
public:
    VMOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, std::vector<std::string>& values);

    void operator()(std::vector<uint8_t>& bytes);

    int get_args_sz();

    #ifdef DEBUG_LOG
    friend std::ostream& operator<<(std::ostream& os, const VMOp& vmop);
    #endif

private:
    VMRegisters& vmr;
    VMMem& vmm;

    int args_sz;

    std::vector<std::unique_ptr<MicroOp>> microOps{};
};

#endif