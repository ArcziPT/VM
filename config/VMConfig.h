#ifndef VM_CONFIG_H
#define VM_CONFIG_H

#include "registers/VMRegisters.h"
#include "alu_rpn/RPN_Calculator.h"
#include "memory/VMMem.h"
#include "op/VMOp.h"

#include <memory>
#include <map>

struct RegisterConfig{
    std::string name;
    reg_sz sz;
    reg_code code;
    Register::Type type;

    #ifdef DEBUG_LOG
    friend std::ostream& operator<<(std::ostream& os, const RegisterConfig& reg_config);
    #endif
};


using opcode = uint64_t;
struct OpConfig{
    opcode opc;
    std::string mnemonic;

    int args_sz_bytes;

    std::unique_ptr<VMOp> vm_op;

    OpConfig() = default;

    OpConfig(opcode opc, std::string& name, int arg_sz_bytes, std::unique_ptr<VMOp> vm_op){
        this->opc = opc;
        this->mnemonic = name;
        this->args_sz_bytes = arg_sz_bytes;
        this->vm_op = std::move(vm_op);
    }

    OpConfig& operator=(OpConfig&& op_config){
        opc = op_config.opc;
        mnemonic = op_config.mnemonic;
        args_sz_bytes = op_config.args_sz_bytes;
        vm_op = std::move(op_config.vm_op);

        return *this;
    }

    OpConfig(OpConfig&& op_config){
        opc = op_config.opc;
        mnemonic = op_config.mnemonic;
        args_sz_bytes = op_config.args_sz_bytes;
        vm_op = std::move(op_config.vm_op);
    }
};

struct VMConfig{
    std::map<std::string, RegisterConfig> registers_symtable;
    std::map<opcode, OpConfig> ops_symtable;

    std::unique_ptr<RPN_Calculator> rpn_calc;
    std::unique_ptr<VMRegisters> vmr;
    std::unique_ptr<VMMem> vmm;
    //TODO: VMConfig

    //opcode size in bytes
    int opc_sz;
};

#endif