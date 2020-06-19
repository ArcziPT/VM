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

//!
//! \struct VMConfig contains information about vm's operations, registers,
//! screen, flags, ...
//!
struct VMConfig{
    std::map<std::string, RegisterConfig> registers_symtable; //!< registers' config
    std::map<opcode, OpConfig> ops_symtable; //!< operations' config

    std::unique_ptr<RPN_Calculator> rpn_calc; //!< rpn_calc
    std::unique_ptr<VMRegisters> vmr; //!< VMRegisters
    std::unique_ptr<VMMem> vmm; //!< VMMem
    
    std::unique_ptr<VMScreen> vms; //!< VMScreen

    //flags
    std::map<std::string, FlagConfig> flags_config_map; //!< flags' config map
    std::vector<FlagConfig> flags_config; //!< flags' config

    int opc_sz; //!< opcode size in bytes
    int reg_code_sz; //!< register code size in bytes
};

#endif