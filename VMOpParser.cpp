#include "VMOpParser.h"

//OPcode: 
// - size 16/32/64 bit (depends on VM config)
// - args size: TODO: let config specify it
//      - r8/16/32/64 - 8/16/32/64
//      - mem8/16/32/64 - ... 
//      - im8/16/32/64 - ...
// - example of op config
//      opcode mnemonic(<args>)->{<basic_inst>}
//      0x1f add r32#r1,r32#r2 {r1=r1+r2}
//      adds r1 to r2 and save it in r1 
//      (r32 - means register of size 32, mem  memory address)    
//
//  Predefined instructions:
//      - functions, which use the flag register


void VMOpParser::parse(VMConfig& config, const std::vector<std::string>& lines){
    std::map<opcode, OpConfig> ops; 

    for(auto& line : lines){
        std::vector<std::string> values;
        split(line, values);

        OpConfig op_config;
        op_config.opc = stoi(values[0]);
        op_config.mnemonic = values[1];

        op_config.vm_op = std::make_unique<VMOp>(vmr, vmm, values);
    }
}