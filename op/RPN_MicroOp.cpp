#include "RPN_MicroOp.h"

#include "utils.h"
#include "Debug.h"
#include "error/VMError.h"

//Converts instruction in infix notation to rpn.
//If it contains assigment, then find the destination of it. 
RPN_MicroOp::RPN_MicroOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, 
                        VMMem& vmm, std::map<std::string, FlagConfig>& flags_config, 
                        const std::map<std::string, Args::Info>& argsInfo, 
                        const std::string& inst) : rpn_calc(rpn_calc), 
                        vmr(vmr), vmm(vmm), flags_config(flags_config), 
                        argsInfo(argsInfo){

    /// empty instruction
    if(inst.empty()){
        empty = true;
        rpn = std::make_unique<RPN>();
        return;
    }

    RPN_Converter rpn_converter;
    std::vector<std::string> temp{};

    //check for assigment
    split(inst, temp, '=');
    if(temp.size() == 2){
        saveResult = true; //when operation is executed we will save result
        dest = temp[0]; //to place, where dest points.

        if(dest[0] == '[' && dest[dest.size()-1] == ']'){
            ptr = true;
            dest = dest.substr(1, dest.size()-2);
        }

        rpn = rpn_converter.convert(temp[1]);
    }else{
        rpn = rpn_converter.convert(temp[0]);
    }
}

RPN_MicroOp::RPN_MicroOp(const RPN_MicroOp& rpn_op): vmm(rpn_op.vmm), vmr(rpn_op.vmr), rpn_calc(rpn_op.rpn_calc), flags_config(rpn_op.flags_config){
    saveResult = rpn_op.saveResult;
    dest = rpn_op.dest;
    argsInfo = rpn_op.argsInfo;
    empty = rpn_op.empty;
    rpn = std::make_unique<RPN>(*rpn_op.rpn);
}


/**
 * Calculates result of operation and saves it if save flag is set.
 */
void RPN_MicroOp::operator()(const std::vector<uint8_t>& bytes){
    if(empty)
        return;

    //caluclate result (execute micro operation)
    auto res = calculate(bytes);

    //! saves result at memory address specified by dest using (sz)-bytes 
    auto set_mem = [this, &bytes, res](int sz) -> void{
        mem_add add = 0;
        for(int i=argsInfo[dest].pos; i<argsInfo[dest].pos + argsInfo[dest].sz; i++){
            add << 8;
            add += bytes[i];
        }

        if(ptr){
            LOG_MSG("Save in memory (mem ptr)")
            add = vmm.read(add, sz);
        }else{
            LOG_MSG("Save in memory")
        }
        vmm.set(add, (reg_val)res, sz);
    };

    //! saves result in register with name specified by dest
    auto set_reg = [this, &bytes, res]() -> void{
        reg_code code = 0;
        for(int i=argsInfo[dest].pos; i<argsInfo[dest].pos + argsInfo[dest].sz; i++){
            code << 8;
            code += bytes[i];
        }

        if(!ptr){
            LOG_MSG("Save in register");
            vmr[code].set_value(res);
        }
        else{
            LOG_MSG("Save in memory (register ptr)")
            auto add = vmr[code].get_value();
            vmm.set(add, (reg_val)res, vmr[code].get_sz()/8);
        }
    };

    //if micro opeartion contains assigment
    if(saveResult){
        //if dest is one of arguments
        if(argsInfo.count(dest) > 0){
            switch(argsInfo[dest].type)
            {
                case Args::Type::M64:
                    set_mem(8);
                    break;
                case Args::Type::M32:
                    set_mem(4);
                    break;
                case Args::Type::M16:
                    set_mem(2);
                    break;
                case Args::Type::M8:
                    set_mem(1);
                    break;
                case Args::Type::R64:
                case Args::Type::R32:
                case Args::Type::R16:
                case Args::Type::R8:
                    //! dest is argument's name, so it has to be translated to register code
                    set_reg();
                    break;
            }

        //! dest is register's name, so it can be used
        }else{
            if(ptr){
                LOG_MSG("Save in memory (reg ptr)")
                auto add = vmr[dest].get_value();
                vmm.set(add, (reg_val)res, vmr[dest].get_sz()/8);
            }
            else{
                LOG_MSG("Save in register")
                vmr[dest].set_value(res);
            }

            //! when saving to register check for overflow
            //! OVERFLOW DETECTION
            if(res >> vmr[dest].get_sz() > 0){
                //! retrive OVERFLOW flag configuration and set it
                auto flag_config = flags_config["OVERFLOW"];
                auto val = vmr[flag_config.register_name].get_value();
                vmr[flag_config.register_name].set_value(val | (0x1 << flag_config.pos));
            }
        }
    }
}

/**
 * Replaces every token in rpn, with its value and then passes it to rpn_calculator to get result.
 */
reg_val RPN_MicroOp::calculate(const std::vector<uint8_t>& bytes){
    if(empty)
        return 0;//rpn can be empty only when it is part of conditional microop, but then calculate() is not called
   
    //! find value of every token in rpn
    for(auto& token : rpn->stack){
        //! only variables need to be find
        if(token.type == Token::Type::var){
            //if it is micro operation's argument
            if(argsInfo.count(token.data) > 0){
                reg_val t = 0;

                //retrive its value from bytes
                for(int i=0; i<argsInfo[token.data].sz; i++){
                    t << 8;
                    t += bytes[argsInfo[token.data].pos + i];
                }

                int sz = 1; //size in bytes of value pointed by token.val
                switch(argsInfo[token.data].type){
                    case Args::Type::I64:
                        sz *= 2;
                    case Args::Type::I32:
                        sz *= 2;
                    case Args::Type::I16:
                        sz *= 2;
                    case Args::Type::I8:
                        //if it is immidiate, then it is final value 
                        token.val = t;
                        break;
                    case Args::Type::R64:
                        sz *= 2;
                    case Args::Type::R32:
                        sz *= 2;
                    case Args::Type::R16:
                        sz *= 2;
                    case Args::Type::R8:
                        //if it is register's code, get its value
                        token.val = vmr[t].get_value();
                        break;
                    case Args::Type::M64:
                        sz *= 2;
                    case Args::Type::M32:
                        sz *= 2;
                    case Args::Type::M16:
                        sz *= 2;
                    case Args::Type::M8:
                        //if it is memory address, it is final value
                        token.val = t;
                        break;
                    default:
                        break;
                }

                //! if it is pointer
                if(token.ptr){
                    //! read pointed data
                    token.val = vmm.read(token.val, sz);
                }
            //! variable is register's name
            }else if(vmr.contains(token.data)){
                token.val = vmr[token.data].get_value();
                
                //! if it is pointer
                if(token.ptr){
                    token.val = vmm.read(token.val, vmr[token.data].get_sz());
                }

            //! variable is FLAG's name
            }else if(flags_config.count(token.data) > 0){
                //replace it by its internal id
                token.val = flags_config[token.data].flag_id;
            
            //! error
            }else{
                VMError::get_instance().set_error(VMError::Type::INVALID_ARG);
                VMError::get_instance().print_msg_exit("RPN_MicroOp");
            }
            LOG_OBJECT(token.ptr)
            LOG_OBJECT(token.data)
            LOG_OBJECT(token.val)
        }
    }

    //calculate result
    return rpn_calc.calculate(*rpn);
}