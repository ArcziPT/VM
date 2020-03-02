#ifndef VMOP_PARSER_H
#define VMOP_PARSER_H

#include <vector>
#include <string>
#include <map>
#include <functional>

#include "VMRegisters.h"
#include "ConfigParser.h"

using opcode = uint64_t;

struct OpConfig{
    opcode opc;
    std::string mnemonic;
    std::function<void(VMRegisters&, VMMem&, std::vector<uint64_t>) op;
};

class VMOpParser{
public:
    void parse(VMConfig& config, const std::vector<std::string>& lines);

private:
    std::function<void(VMRegisters&, VMMem&, std::vector<uint64_t>)> parse_op_func(const std::string& args, const std::string& func);
};

#endif