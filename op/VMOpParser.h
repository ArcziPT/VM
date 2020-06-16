#ifndef VMOP_PARSER_H
#define VMOP_PARSER_H

#include <vector>
#include <string>
#include <map>
#include <functional>

#include "VMOp.h"
#include "config/ConfigParser.h"
#include "utils.h"
#include "alu_rpn/RPN_Calculator.h"


class VMOpParser{
public:
    VMOpParser(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, std::map<std::string, FlagConfig>& flags_config): rpn_calc(rpn_calc), vmr(vmr), vmm(vmm), flags_config(flags_config) {};
    OpConfig parse(const std::string& line);

private:
    VMRegisters& vmr;
    VMMem& vmm;
    RPN_Calculator& rpn_calc;
    std::map<std::string, FlagConfig>& flags_config;
};

#endif