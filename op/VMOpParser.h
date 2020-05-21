#ifndef VMOP_PARSER_H
#define VMOP_PARSER_H

#include <vector>
#include <string>
#include <map>
#include <functional>

#include "VMOp.h"
#include "ConfigParser.h"
#include "utils.h"
#include "alu_rpn/RPN_Calculator.h"


class VMOpParser{
public:
    VMOpParser(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm): rpn_calc(rpn_calc), vmr(vmr), vmm(vmm) {};
    OpConfig parse(const std::string& line);

private:
    VMRegisters& vmr;
    VMMem& vmm;
    RPN_Calculator& rpn_calc;
};

#endif