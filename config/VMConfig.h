#ifndef VM_CONFIG_H
#define VM_CONFIG_H

#include "registers/VMRegisters.h"
#include "alu_rpn/RPN_Calculator.h"
#include "memory/VMMem.h"
#include "op/VMOp.h"
#include "screen/VMScreen.h"
#include "registers/RegisterConfig.h"
#include "registers/FlagConfig.h"
#include "op/OpConfig.h"

#include <memory>
#include <map>

struct VMConfig{
    std::map<std::string, RegisterConfig> registers_symtable;
    std::map<opcode, OpConfig> ops_symtable;

    std::unique_ptr<RPN_Calculator> rpn_calc;
    std::unique_ptr<VMRegisters> vmr;
    std::unique_ptr<VMMem> vmm;
    
    std::unique_ptr<VMScreen> vms;

    //flags
    std::map<std::string, FlagConfig> flags_config_map;
    std::vector<FlagConfig> flags_config;

    //opcode size in bytes
    int opc_sz;
    int reg_code_sz;
};

#endif