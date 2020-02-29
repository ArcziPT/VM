#include "VMRegisters.h"

VMRegisters::VMRegisters(const std::vector<Register>& registers){
    for(auto reg : registers){
        this->registers.insert({reg.get_code(), reg});

        if(reg.get_type() == Register::IP) ip_reg = &this->registers[reg.get_code()];
        if(reg.get_type() == Register::FLAGS) flag_reg = &this->registers[reg.get_code()];
    }
}

Register& VMRegisters::operator[](reg_code r){
    if(registers.count(r) == 0); //handle error

    return registers[r];
}

void VMRegisters::set_value(reg_code r, reg_val val){
    if(registers.count(r) == 0)
        return; //handle error

    registers[r].set_value(val);
}

reg_val VMRegisters::read_value(reg_code r){
    if(registers.count(r) == 0)
        return; //handle error

    return registers[r].get_value();
}

void VMRegisters::copy(reg_code rs, reg_code rd){
    if(registers.count(rs) == 0 or registers.count(rd) == 0)
        return; //handle error

    registers[rd].set_value(registers[rs].get_value());
}

reg_sz VMRegisters::get_sz(reg_code r){
    if(registers.count(r) == 0)
        return; //handle error

    return registers[r].get_sz();
}