#include "registers/Register.h"
#include "op/VMOp.h"
#include "alu_rpn/RPN_Calculator.h"

#include <memory>
#include <map>

struct RegisterConfig{
    std::string name;
    reg_sz sz;
    reg_code code;
    Register::reg_type type;
};


using opcode = uint64_t;
struct OpConfig{
    opcode opc;
    std::string mnemonic;

    int args_sz_bytes;

    std::unique_ptr<VMOp> vm_op;

    OpConfig(opcode opc, std::string& name, int arg_sz_bytes, std::unique_ptr<VMOp> vm_op){
        this->opc = opc;
        this->mnemonic = name;
        this->args_sz_bytes = arg_sz_bytes;
        this->vm_op = std::move(vm_op);
    }
};

struct VMConfig{
    std::map<std::string, RegisterConfig> registers_symtable;
    std::map<opcode, OpConfig> ops_symtable;

    std::unique_ptr<RPN_Calculator> rpn_calc;
    std::unique_ptr<VMRegisters> vmr;
    std::unique_ptr<VMMem> vmm;
    //TODO: VMConfig

    int opc_sz;
};