#include "VMOpParser.h"

//OPcode: 
// - size 16/32/64 bit (depends on VM config)
// - args size: TODO: let config specify it
//      - r8/16/32/64 - 8/16/32/64
//      - mem8/16/32/64 - ... 
//      - im8/16/32/64 - ...
// - example of op config
//      opcode mnemonic(<args>)->{<basic_inst>}
//      0x1f add (r32)r1,(r32)r2 {r1=r1+r2}
//      adds r1 to r2 and save it in r1 
//      (r32 - means register of size 32, mem  memory address)    
//
//  Predefined instructions:
//      - functions, which use the flag register

using opcode = uint64_t;

struct OpConfig{
    opcode opc;
    std::string mnemonic;
    int args_sz; //size of args in bytes

    //vector contains argument's data in bytes
    std::function<void(VMRegisters&, VMMem&, std::vector<uint8_t>) op;
};

void VMOpParser::parse(VMConfig& config, const std::vector<std::string>& lines){
    std::map<opcode, OpConfig> ops; 

    for(auto& line : lines){
        std::vector<std::string> values;
        //TODO: split line by ' ' into values

        OpConfig op_config;
        op_config.opc = stoi(values[0]);
        op_config.mnemonic = values[1];
        
        std::vector<std::string> args;
        //TODO: split values[2] by ',' into args
        //TODO: get type and calculate total size
        op_config.args_sz = 2; //TEMP

        op_config.op = [args, values](VMRegisters& vmr, VMMem& vmm, std::vector<uint8_t>& bytes) -> void{
            //TODO: create args info table, containing:
            // -id
            // -type
            // -value

            //instructions are separeted by ';'

            //TODO: in place of ids put arguments' values

            //TODO: parse instructions
            //if it contains '=' then use RPN_Calculator
            //else -> it has to be call to one of the predefined functions
        };
    }
}