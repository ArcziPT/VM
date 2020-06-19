#ifndef OP_CONFIG_H
#define OP_CONFIG_H

#include "op/VMOp.h"

using opcode = uint64_t; //!< \typedef opcode 

//!
//! \struct OpConfig information about operation and its arguments. 
//!
struct OpConfig{
    opcode opc; //!< opcode
    std::string mnemonic; //!< mnemonic

    int args_sz_bytes; //!< size of arguments in bytes

    std::unique_ptr<VMOp> vm_op; //!< operation

    OpConfig() = default;

    //! creates new operation config
    //! @param vm_op - VMOp (the operation itself), withgiven opcode
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