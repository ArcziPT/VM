#include "VMOp.h"
#include "Args.h"
#include "error/VMError.h"

#include "Debug.h"

//Builds array of operands' information and then creates appropiate micro operations.
VMOp::VMOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, std::map<std::string, FlagConfig>& flags_config, std::vector<std::string>& values, const std::string& name): vmr(vmr), vmm(vmm), flags_config(flags_config), name(name){
    std::vector<std::string> args;
    std::vector<std::string> instructions;
    split(values[2], args, ','); //! arguments' declarations are separated by ','

    //create arguments' symtable
    std::map<std::string, Args::Info> args_symtable;
    int i=0;
    for(auto& arg : args){
        //argument declaration
        // type#name

        std::vector<std::string> s;
        split(arg, s, '#');

        Args::Info arg_info;
        arg_info.type = Args::type_map[s[0]]; //! get type
        arg_info.sz = Args::size_map[arg_info.type]; //! get size
        arg_info.name = s[1];
        arg_info.pos = i; //! set starting position

        args_symtable[arg_info.name] = arg_info;
        i += arg_info.sz; //! next argument's data will start after last byte of tis one
    }

    LOG_MSG("args_info created")

    args_sz = i; //! total size of arguments

    split(values[3], instructions, ';'); //! instructions are separeted by ';'
    for(auto& inst : instructions){
        //conditonal instruction
        if(inst.find('?', 0) != std::string::npos){
            //!  cndition, ctrue, cfalse must be in parentheses
            //! format: (condition)?(ctrue):(cfalse)
            
            //split
            //t[0] - condition's code
            //temp[0] - ctrue's code
            //temp[1] - cfalse' code
            std::vector<std::string> t;
            std::vector<std::string> temp;
            split(inst, t, '?');
            split(t[1], temp, ':');

            std::string s1="", s2="", s3="";

            //if condition is empty -> error
            if(t[0].size() <= 2){
                VMError::get_instance().set_error(VMError::Type::WRONG_OP_CONFIG);
                VMError::get_instance().print_msg_exit("VMOp");
            }

            //condition to string
            s1 = std::string(t[0].begin() + 1, t[0].end() - 1);

            //ctrue epmty
            if(temp[0].size() > 2)
                s2 = std::string(temp[0].begin() + 1, temp[0].end() - 1);

            //cfalse empty
            if(temp[1].size() > 2)
                s3 = std::string(temp[1].begin() + 1, temp[1].end() - 1);

            //! create rpn_microp to initialize conditional one
            RPN_MicroOp condition(rpn_calc, vmr, vmm, flags_config, args_symtable, s1), 
                        ctrue(rpn_calc, vmr, vmm, flags_config, args_symtable, s2), 
                        cfalse(rpn_calc, vmr, vmm, flags_config, args_symtable, s3);
            microOps.push_back(std::make_unique<ConditionalMicroOp>(condition, ctrue, cfalse));
            LOG_MSG("new conditional microop")
        
        //! rpn micro operation
        }else{
            //parse inst
            microOps.push_back(std::make_unique<RPN_MicroOp>(rpn_calc, vmr, vmm, flags_config, args_symtable, inst));
            LOG_MSG("new microop")
        }
    }
}


//! execute sequence of micro operations
void VMOp::operator()(std::vector<uint8_t>& bytes){
    LOG_MSG("################ OP " + name + " ################")
    for(auto& microOp : microOps){
        LOG_MSG("Microop called:")
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