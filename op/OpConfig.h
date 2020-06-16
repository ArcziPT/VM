#ifndef OP_CONFIG_H
#define OP_CONFIG_H

#include "op/VMOp.h"

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

#endif