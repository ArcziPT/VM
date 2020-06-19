#ifndef VM_MEM_H
#define VM_MEM_H

#include "registers/VMRegisters.h"

using mem_add = uint64_t; //!< \typedef mem_add
using byte = uint8_t; //!< \typedef byte


//!
//! \class VMMem provides API for memory manipulation.
//! 
class VMMem{
public:
    //! creates new vm's memory with specified size in bytes
    VMMem(uint32_t mem_sz);

    //! @param add - address in memory
    //! @param nbytes - number of bytes to read
    reg_val read(mem_add add, int nbytes);
    std::vector<byte> read_bytes(mem_add add, int n_bytes);

    //! @param add - address in memory
    //! @param val - value to save
    //! @param nbytes - number of bytes to save
    void set(mem_add add, reg_val val, int nbytes);
    void set(mem_add add, byte* bytes, int nbytes);

    //! returns address of vm's memory in host's address space
    byte* get_base_add();

private:
    byte* mem = nullptr;
    uint32_t mem_sz = 0;

};

#endif