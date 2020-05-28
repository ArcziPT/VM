#ifndef RPN_MICRO_OP_H
#define RPN_MICRO_OP_H

#include <vector>
#include <map>
#include "MicroOp.h"
#include "alu_rpn/RPN_Converter.h"

#include "registers/VMRegisters.h"
#include "memory/VMMem.h"
#include "alu_rpn/RPN_Calculator.h"

class RPN_MicroOp: public MicroOp{
public:
    RPN_MicroOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, const std::map<std::string, Args::Info>& argsInfo, const std::string& inst);
    RPN_MicroOp(const RPN_MicroOp& rpn_op);

    void operator()(const std::vector<uint8_t>& bytes);
    uint64_t calculate(const std::vector<uint8_t>& bytes);

private:
    VMRegisters& vmr;
    VMMem& vmm;
    RPN_Calculator& rpn_calc;

    std::map<std::string, Args::Info> argsInfo;
    std::unique_ptr<RPN> rpn;

    bool empty = false;

    bool saveResult = false;
    std::string dest;
};

#endif