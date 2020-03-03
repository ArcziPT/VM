#ifndef VMOP_PARSER_H
#define VMOP_PARSER_H

#include <vector>
#include <string>
#include <map>
#include <functional>

#include "VMOp.h"
#include "ConfigParser.h"
#include "utils.h"

using opcode = uint64_t;

struct OpConfig{
    opcode opc;
    std::string mnemonic;

    //vector contains argument's data in bytes
    //std::function<void(std::vector<uint8_t>&)> op;

    std::unique_ptr<VMOp> vm_op;
};

class VMOpParser{
public:
    VMOpParser(VMRegisters& vmr, VMMem& vmm): vmr(vmr), vmm(vmm) {};
    void parse(VMConfig& config, const std::vector<std::string>& lines);

private:
    VMRegisters& vmr;
    VMMem& vmm;
};

#endif