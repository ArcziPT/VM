#include "VMRegisters.h"
#include "error/VMError.h"

#include "Debug.h"

VMRegisters::VMRegisters(const std::vector<Register>& registers){
    this->registers = registers;

    //init maps
    for(auto& reg : this->registers){
        this->c_registers.insert({reg.get_code(), &reg});
        this->n_registers.insert({reg.get_name(), &reg});

        if(reg.get_type() == Register::Type::IP) ip_reg = this->c_registers[reg.get_code()];
    }

    if(ip_reg == nullptr)
        return; //error
}

Register& VMRegisters::operator[](reg_code r){
    if(c_registers.count(r) == 0){
        VMError::get_instance().set_error(VMError::Type::REGC_NOT_EXIST);
        VMError::get_instance().print_msg_exit("VMRegisters");
    }

    return *c_registers[r];
}

Register& VMRegisters::operator[](const std::string& r_name){
    if(n_registers.count(r_name) == 0){
        VMError::get_instance().set_error(VMError::Type::REGC_NOT_EXIST);
        VMError::get_instance().print_msg_exit("VMRegisters");
    }

    return *(n_registers[r_name]);
}

bool VMRegisters::contains(reg_code r){
    return c_registers.count(r) != 0;
}

bool VMRegisters::contains(const std::string& r_name){
    return n_registers.count(r_name) != 0;
}

Register& VMRegisters::get_ip_reg(){
    return *ip_reg;
}

void VMRegisters::set_exit_flag(){
    exit_flag = true;
}

bool* VMRegisters::get_exit_flag(){
    return &exit_flag;
}