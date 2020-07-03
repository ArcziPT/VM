#include "Register.h"
#include "Debug.h"

#include <vector>

std::map<std::string, Register::Type> Register::type_map = {{"GEN", Register::Type::GENERAL}, {"IP", Register::Type::IP}, {"FLAG", Register::Type::FLAG}};

Register::Register(const std::string& name, reg_code code, reg_sz sz, Type type) : name(name), code(code),
                                                        sz(sz), type(type) {
    //validate data
    bool valid = false;
    
    auto sizes = std::vector<reg_sz>{8, 16, 32, 64};
    for(auto x : sizes){
        if(x == sz)
            valid = true;
    }

    if(!valid)
        throw std::invalid_argument("Wrong size.");

    switch(type){
        case Register::Type::FLAG:
        case Register::Type::GENERAL:
        case Register::Type::IP:
            valid = true;
            break;
        default:
    }

    if(!valid)
        throw std::invalid_argument("Wrong type.");
};

void Register::set_value(reg_val value){
    //create mask
    reg_val mask = (0x1 << (sz - 1));
    mask += mask - 1;

    //truncate value to (sz)-bits
    this->value = (value & mask);
}

Register::Type Register::get_type(){
    return type;
}

reg_val Register::get_value(){
    return value;
}

reg_sz Register::get_sz(){
    return sz;
}

std::string Register::get_name(){
    return name;
}

reg_code Register::get_code(){
    return code;
}