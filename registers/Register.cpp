#include "Register.h"


void Register::set_value(reg_val value){
    this->value = value;
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