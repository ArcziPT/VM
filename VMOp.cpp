//TODO: create args info table, containing:
            // -id
            // -type
            // -value



            //instructions are separeted by ';'

            //TODO: parse instructions
            
            //if it contains '=' then use RPN_Calculator
            //TODO: in place of ids put arguments' values

            //else -> it has to be call to one of the predefined functions

#include "VMOp.h"

VMOp::VMOp(VMRegisters& vmr, VMMem& vmm, std::vector<std::string>& values): vmr(vmr), vmm(vmm){
    std::vector<std::string> args;
    std::vector<std::string> instructions;
    split(values[2], args, ',');
    split(values[3], instructions, ';');

    for(auto& arg : args){
        std::vector<std::string> s;
        split(arg, s, '#');

        Args::Info arg_info;
        arg_info.type = Args::type_map[s[0]];
        arg_info.name = s[1];
    }

    //TODO: parse instructions
    for(auto& inst : instructions){
        if(inst.find('=') != std::string::npos){
            //use rpn_calc
        }else{
            //TODO: create predefined functions
        }
        /*
         * TODO:
         * create vector representing instructions sequence (rpn and predefined)
         * which then will be used when op is called 
         */
    }
}

void VMOp::extract_args_values(std::vector<uint8_t>& bytes){
    /*int pos = 0;
    for(auto& arg_info : args_info){
        arg_info.val = bytes[pos, pos+size_map[arg_info.type]];
        pos += size_map[arg_info.type];
    }*/
}

void VMOp::operator()(std::vector<uint8_t>& bytes){
    extract_args_values(bytes);
    
    //TODO: finish
}