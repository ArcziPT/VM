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
    Register& VMRegisters::operator[](const std::string& r_name);

    bool contains(reg_code r);
    bool contains(const std::string& r_name);

    void set_value(reg_code r, reg_val val);
    reg_val read_value(reg_code r);

    reg_sz get_sz(reg_code r);

    void copy(reg_code rs, reg_code rd);

    void inc_ip(reg_val delta);

private:
    std::vector<Register> registers;
    std::map<reg_code, Register*> c_registers;
    std::map<std::string, Register*> n_registers;

    //special purpose registers
    Register* ip_reg = nullptr;
    Register* flag_reg = nullptr;
};