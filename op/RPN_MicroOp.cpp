#include "RPN_MicroOp.h"

#include "utils.h"

RPN_MicroOp::RPN_MicroOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, const std::map<std::string, Args::Info>& argsInfo, const std::string& inst)
                                        : rpn_calc(rpn_calc), vmr(vmr), vmm(vmm), argsInfo(argsInfo){
    RPN_Converter rpn_converter;
    std::vector<std::string> temp{};

    split(inst, temp, '=');
    if(temp.size() > 1){
        saveResult = true;
        dest = temp[0];
    }

    rpn = rpn_converter.convert(temp[1]);
}

RPN_MicroOp::RPN_MicroOp(const RPN_MicroOp& rpn_op): vmm(rpn_op.vmm), vmr(rpn_op.vmr), rpn_calc(rpn_op.rpn_calc){
    saveResult = rpn_op.saveResult;
    dest = rpn_op.dest;
    argsInfo = rpn_op.argsInfo;
    rpn = std::make_unique<RPN>(*rpn_op.rpn);
}

void RPN_MicroOp::operator()(const std::vector<uint8_t>& bytes){
    auto res = calculate(bytes);

    if(saveResult){
        if(argsInfo.count(dest) > 0){
            switch(argsInfo[dest].type)
            {
                case Args::Type::M64:
                case Args::Type::M32:
                case Args::Type::M16:
                case Args::Type::M8:
                    mem_add add = 0;
                    for(int i=argsInfo[dest].pos; i<argsInfo[dest].pos + argsInfo[dest].sz; i++){
                        add << 8;
                        add += bytes[i];
                    }
                    vmm.set(add, res);
                    break;
                case Args::Type::R64:
                case Args::Type::R32:
                case Args::Type::R16:
                case Args::Type::R8:
                    vmr[dest].set_value(res);
                    break;
            }
        }else{
            vmr[dest].set_value(res);
        }
    }
}

reg_val RPN_MicroOp::calculate(const std::vector<uint8_t>& bytes){
    for(auto& token : rpn->stack){
        if(token.type == Token::Type::var){
            if(argsInfo.count(token.data) > 0){
                token.val = 0;
                for(int i=0; i<argsInfo[token.data].sz; i++){
                    token.val << 8;
                    token.val += bytes[argsInfo[token.data].pos + i];
                }
            }else if(vmr.contains(token.data)){
                token.val = vmr[token.data].get_value();
            }
        }
    }

    //TODO: calculate the rpn
    return rpn_calc.calculate(*rpn);
}