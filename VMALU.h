#include "VMRegisters.h"

//TODO: make us of rpn_calculator ????

class VMALU{
public:
    VMALU(VMRegisters& vm_registers) : vm_registers(vm_registers) {};
 
    //TODO: implement, oveflow checks, signed/unsigned versions

    void add(reg_code rs, reg_code rd);
    void add(reg_val v, reg_code rd);

    void sub(reg_code rs, reg_code rd);
    void mul(reg_code rs, reg_code rd);

    void inc(reg_code r);
    void dec(reg_code r);

private:
    VMRegisters& vm_registers;

    void check_overflow(reg_val v, reg_code r);
}