#include "VMALU.h"

void VMALU::add(reg_code rs, reg_code rd){
    reg_val val = vm_registers.read_value(rs) + vm_registers.read_value(rd);

    check_overflow(val, rd);
    vm_registers.set_value(rd, val);
}

void VMALU::add(reg_val v, reg_code rd){
    reg_val val = vm_registers.read_value(rd) + v;

    check_overflow(val, rd);
    vm_registers.set_value(rd, val);
}

void VMALU::sub(reg_code rs, reg_code rd){
    reg_val val = vm_registers.read_value(rs) - vm_registers.read_value(rd);

    check_overflow(val, rd);
    vm_registers.set_value(rd, val);
}

void VMALU::mul(reg_code rs, reg_code rd){
    reg_val val = vm_registers.read_value(rs) * vm_registers.read_value(rd);

    check_overflow(val, rd);
    vm_registers.set_value(rd, val);
}

void VMALU::inc(reg_code r){
    reg_val val = vm_registers.read_value(r);
    val += 1;

    check_overflow(val, r);
    vm_registers.set_value(r, val);
}
    
void VMALU::dec(reg_code r){
    reg_val val = vm_registers.read_value(r);
    val -= 1;

    check_overflow(val, r);
    vm_registers.set_value(r, val);
}

void VMALU::check_overflow(reg_val v, reg_code r){
    //check if value (v) fits in register (r)

    if(v > ~(~(reg_val)(0x0) << vm_registers.get_sz(r))){
        //TODO: set flag register
    }
}