#include "RPN_MicroOp.h"

#include "utils.h"
#include "Debug.h"

RPN_MicroOp::RPN_MicroOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, const std::map<std::string, Args::Info>& argsInfo, const std::string& inst)
                                        : rpn_calc(rpn_calc), vmr(vmr), vmm(vmm), argsInfo(argsInfo){

    if(inst.empty()){
        empty = true;
        rpn = std::make_unique<RPN>();
        return;
    }

    RPN_Converter rpn_converter;
    std::vector<std::string> temp{};

    split(inst, temp, '=');
    if(temp.size() == 2){
        saveResult = true;
        dest = temp[0];
        rpn = rpn_converter.convert(temp[1]);
    }else{
        rpn = rpn_converter.convert(temp[0]);
    }
}

RPN_MicroOp::RPN_MicroOp(const RPN_MicroOp& rpn_op): vmm(rpn_op.vmm), vmr(rpn_op.vmr), rpn_calc(rpn_op.rpn_calc){
    saveResult = rpn_op.saveResult;
    dest = rpn_op.dest;
    argsInfo = rpn_op.argsInfo;
    empty = rpn_op.empty;
    rpn = std::make_unique<RPN>(*rpn_op.rpn);
}

void RPN_MicroOp::operator()(const std::vector<uint8_t>& bytes){
    if(empty)
        return;

    auto res = calculate(bytes);

    auto set_mem = [this, &bytes, res](int sz) -> void{
        mem_add add = 0;
        for(int i=argsInfo[dest].pos; i<argsInfo[dest].pos + argsInfo[dest].sz; i++){
            add << 8;
            add += bytes[i];
        }
        vmm.set(add, res, sz);
    };

    auto set_reg = [this, &bytes, res]() -> void{
        reg_code code = 0;
        for(int i=argsInfo[dest].pos; i<argsInfo[dest].pos + argsInfo[dest].sz; i++){
            code << 8;
            code += bytes[i];
        }
        vmr[code].set_value(res);
    };

    if(saveResult){
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
                    //dest is variable name, so it has to be translated to register code
                    set_reg();
                    break;
            }
        }else{
            //dest is register's name, so it can be used
            vmr[dest].set_value(res);
        }
    }
}

reg_val RPN_MicroOp::calculate(const std::vector<uint8_t>& bytes){
    if(empty)
        return 0;//rpn can be empty only when it is part of conditional microop, but then calculate() is not called
    
    for(auto& token : rpn->stack){
        if(token.type == Token::Type::var){
            if(argsInfo.count(token.data) > 0){
                reg_val t = 0;
                for(int i=0; i<argsInfo[token.data].sz; i++){
                    t << 8;
                    t += bytes[argsInfo[token.data].pos + i];
                }

                switch(argsInfo[token.data].type){
                    case Args::Type::I64:
                    case Args::Type::I32:
                    case Args::Type::I16:
                    case Args::Type::I8:
                        token.val = t;
                        break;
                    case Args::Type::R64:
                    case Args::Type::R32:
                    case Args::Type::R16:
                    case Args::Type::R8:
                        token.val = vmr[t].get_value();
                        break;
                    case Args::Type::M64:
                        token.val = vmm.read(t, 8);
                        break;
                    case Args::Type::M32:
                        token.val = vmm.read(t, 4);
                        break;
                    case Args::Type::M16:
                        token.val = vmm.read(t, 2);
                        break;
                    case Args::Type::M8:
                        token.val = vmm.read(t, 1);
                        break;
                }
            }else if(vmr.contains(token.data)){
                token.val = vmr[token.data].get_value();
            }
            LOG_OBJECT(token.data)
            LOG_OBJECT(token.val)
        }
    }

    //TODO: calculate the rpn
    return rpn_calc.calculate(*rpn);
}