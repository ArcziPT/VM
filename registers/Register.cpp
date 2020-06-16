#include "Register.h"
#include "Debug.h"

std::map<std::string, Register::Type> Register::type_map = {{"GEN", Register::Type::GENERAL}, {"IP", Register::Type::IP}, {"FLAG", Register::Type::FLAG}};

void Register::set_value(reg_val value){
    reg_val mask = (0x1 << (sz - 1));
    mask += mask - 1;

    //truncate value to (sz) bits
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