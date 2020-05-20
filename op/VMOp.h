#ifndef VM_OP_H
#define VM_OP_H

#include "config/VMConfig.h"
#include "memory/VMMem.h"
#include "utils.h"
#include "ConditionalMicroOp.h"
#include "RPN_MicroOp.h"
#include "alu_rpn/RPN_Calculator.h"

class VMOp{
public:
    VMOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, std::vector<std::string>& values);

    void operator()(std::vector<uint8_t>& bytes);

private:
    VMRegisters& vmr;
    VMMem& vmm;

    std::vector<MicroOp> microOps{};
};

#endif