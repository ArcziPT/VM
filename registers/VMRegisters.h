#ifndef VM_REGISTERS_H
#define VM_REGISTERS_H

#include <vector>
#include <map>
#include <memory>

#include "Register.h"

//TODO: overload operator[]
//TODO: flag register functions
//TODO: create masks for flag register based on config file

class VMRegisters{
public:
    VMRegisters(const std::vector<Register>& registers);

    Register& operator[](reg_code r);
    Register& operator[](const std::string& r_name);

    bool contains(reg_code r);
    bool contains(const std::string& r_name);

    Register& get_ip_reg();

    //
    void set_exit_flag();
    bool* get_exit_flag();

private:
    std::vector<Register> registers;
    std::map<reg_code, Register*> c_registers;
    std::map<std::string, Register*> n_registers;

    //special purpose registers
    Register* ip_reg = nullptr;
    Register* flag_reg = nullptr;

    bool exit_flag = false;
};

#endif