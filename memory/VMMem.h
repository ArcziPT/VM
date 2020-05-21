#ifndef VM_MEM_H
#define VM_MEM_H

#include "registers/VMRegisters.h"

using mem_add = uint64_t;

class VMMem{
public:
    VMMem(uint32_t mem_sz);

    reg_val read(mem_add add, int nbytes);
    void set(mem_add add, reg_val val, int nbytes);

private:
    uint8_t* mem = nullptr;
    uint32_t mem_sz = 0;

};

#endif