#ifndef VM_REGISTERS_H
#define VM_REGISTERS_H

#include <vector>
#include <map>
#include <memory>

#include "Register.h"


//!
//! \class VMRegisters manages VM's registers.
//! Allows to get access to registers by theirs name or code.
class VMRegisters{
public:
    //! creates VMRegisters with access to given registers
    //! @param registers array of registers, which will be managed by this class
    VMRegisters(const std::vector<Register>& registers);

    //! returns register with specified code
    //! @param r register's code
    Register& operator[](reg_code r);
    //! returns register with specified name
    //! @param r_name name of register
    Register& operator[](const std::string& r_name);

    //! checks if such a register exsist
    bool contains(reg_code r);
    bool contains(const std::string& r_name);

    //! returns ip register
    Register& get_ip_reg();

    void set_exit_flag();
    bool* get_exit_flag();

private:
    std::vector<Register> registers; //!< array of managed registers
    std::map<reg_code, Register*> c_registers; //!< maps code to register in vector registers
    std::map<std::string, Register*> n_registers; //!< maps name to register in vector registers

    //special purpose register
    Register* ip_reg = nullptr; //!< pointer at ip register in vector registers

    bool exit_flag = false; //!< if set to true, executable which is running on VM should be terminated
};

#endif