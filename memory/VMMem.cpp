#include "VMMem.h"

#include <iostream>
#include <cstring>

//TODO: seting/reading memory depends on host's endianess

VMMem::VMMem(uint32_t mem_sz){
    this->mem_sz = mem_sz;

    mem = new byte[mem_sz];
}

reg_val VMMem::read(mem_add add, int nbytes){
    if(add > mem_sz)
        return 0; //TODO: error handling

    reg_val v = 0;
    for(uint8_t* b = mem + add; b < mem + add + nbytes; b++){
        v << 8;
        v += *b;
    }

    return v;
}

void VMMem::set(mem_add add, reg_val val, int nbytes){
    if(add > mem_sz)
        return; //TODO: error handling

    uint8_t* vp = (uint8_t*)(&val);
    for(uint8_t* b = mem + add + nbytes-1; b >= mem + add; b--){
        *b = *vp;
        vp++;
    }
}

void VMMem::set(mem_add add, byte* bytes, int nbytes){
    if(add > mem_sz || add + nbytes > mem_sz)
        return;

    memcpy(mem + add, bytes, nbytes); 
}  
