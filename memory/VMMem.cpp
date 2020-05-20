#include "VMMem.h"

#include <iostream>

VMMem::VMMem(uint32_t mem_sz, int word_sz){
    this->mem_sz = mem_sz;
    this->word_sz = word_sz;

    mem = new uint8_t[mem_sz];
}

reg_val VMMem::read(mem_add add, int nbytes){
    if(add > mem_sz)
        return 0; //TODO: error handling

    reg_val v = 0;
    //TODO: big/little endian
    for(uint8_t* b = mem + add*word_sz; b < mem + add*word_sz + nbytes; b++){
        v << 8;
        v += *b;
    }

    return v;
}

void VMMem::set(mem_add add, reg_val val, int nbytes){
    if(add > mem_sz)
        return; //TODO: error handling

    uint8_t* vp = (uint8_t*)(&val);
    for(uint8_t* b = mem + add*word_sz + nbytes; b >= mem + add*word_sz; b--){
        *b = *vp;
        vp++;
    }
}