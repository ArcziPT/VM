#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <string>

//change if needed
using reg_val = uint64_t;
using reg_code = uint16_t;
using reg_sz = uint16_t;

class Register{ 
public:
    enum reg_type{
        GENERAL,
        IP,
        FLAGS
    };

    Register(const std::string& name, reg_code code,
                            reg_sz sz, reg_type type) : name(name), code(code),
                                                        sz(sz), type(type) {};
    
    void set_value(reg_val value);
    reg_type get_type();
    reg_val get_value();
    reg_sz get_sz();
    std::string get_name();
    reg_code get_code();

private:
    std::string name;
    reg_code code;
    reg_sz sz;
    reg_val value = 0;

    reg_type type;
};

/*template <typename reg, uint16_t sz>
class Register{ 
public:
    Register(const std::string& name, uint32_t code) : name(name), code(code) {};
    void set_value(reg value);
    reg get_value();
    std::string get_name();
    uint32_t get_code();

private:
    std::string name;
    uint32_t code;
    reg value;
};


template <typename reg, uint16_t sz>
void Register<reg, sz>::set_value(reg value){
    this->value = value;
}

template <typename reg, uint16_t sz>
reg Register<reg, sz>::get_value(){
    return value;
}

template <typename reg, uint16_t sz>
std::string Register<reg, sz>::get_name(){
    return name;
}

template <typename reg, uint16_t sz>
uint32_t Register<reg, sz>::get_code(){
    return code;
}

using Register_8 = Register<uint8_t, 8>;
using Register_16 = Register<uint16_t, 16>;
using Register_32 = Register<uint32_t, 32>;
using Register_64 = Register<uint64_t, 64>;*/

#endif