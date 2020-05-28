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

#include "Debug.h"

VMOp::VMOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, std::vector<std::string>& values): vmr(vmr), vmm(vmm){
    std::vector<std::string> args;
    std::vector<std::string> instructions;
    split(values[2], args, ',');

    //symtable
    //std::map is implemented as red-black tree
    std::map<std::string, Args::Info> args_symtable;
    int i=0;
    for(auto& arg : args){
        std::vector<std::string> s;
        split(arg, s, '#');

        Args::Info arg_info;
        arg_info.type = Args::type_map[s[0]];
        arg_info.sz = Args::size_map[arg_info.type];
        arg_info.name = s[1];
        arg_info.pos = i;

        args_symtable[arg_info.name] = arg_info;
        i += arg_info.sz;
    }

    LOG_MSG("args_info created")

    args_sz = i;


    //TODO: parse instructions  
    split(values[3], instructions, ';');
    for(auto& inst : instructions){
        //conditonal instruction
        if(inst.find('?', 0) != std::string::npos){
            std::vector<std::string> t{};
            std::vector<std::string> temp;
            split(inst, t, '?');
            split(t[1], temp, ':');

            RPN_MicroOp condition(rpn_calc, vmr, vmm, args_symtable, t[0]), ctrue(rpn_calc, vmr, vmm, args_symtable, temp[0]), cfalse(rpn_calc, vmr, vmm, args_symtable, temp[1]);
            microOps.push_back(std::make_unique<ConditionalMicroOp>(condition, ctrue, cfalse));
            LOG_MSG("new conditional microop")
        }else{
            //parse inst
            microOps.push_back(std::make_unique<RPN_MicroOp>(rpn_calc, vmr, vmm, args_symtable, inst));
            LOG_MSG("new microop")
        }
    }
}

void VMOp::operator()(std::vector<uint8_t>& bytes){
    for(auto& microOp : microOps){
        LOG_MSG("microop called")
        (*microOp)(bytes);
    }
}

int VMOp::get_args_sz(){
    return args_sz;
}

#ifdef DEBUG_LOG
    std::ostream& operator<<(std::ostream& os, const VMOp& vmop){
        os<<"number_of_microops="<<vmop.microOps.size();
        return os;
    };
#endif