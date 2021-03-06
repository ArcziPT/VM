#include "VMMem.h"

#include <iostream>
#include <cstring>

#include "Debug.h"

#include <sstream>

//TODO: seting/reading memory depends on host's endianess

VMMem::VMMem(uint32_t mem_sz){
    this->mem_sz = mem_sz;

    mem = new byte[mem_sz];
}

reg_val VMMem::read(mem_add add, int nbytes){
    std::stringstream stream;
    stream << std::hex << add;
    std::string result( stream.str() );
    LOG_MSG("Read " + std::to_string(nbytes) + "B at 0x" + result)

    if(add > mem_sz)
        return 0; //error

    reg_val v = 0;
    for(int i=0; i<nbytes; i++){
        v<<8;
        v += *(mem+add+i);
    }

    return v;
}

std::vector<byte> VMMem::read_bytes(mem_add add, int nbytes){
    std::vector<byte> bytes{};

    for(int i=0; i<nbytes; i++){
        bytes.push_back(*(mem+add+i));
    }

    return bytes;
}

void VMMem::set(mem_add add, reg_val val, int nbytes){
    std::stringstream stream;
    stream << std::hex << add;
    std::string result( stream.str() );
    stream << std::hex <<val;
    std::string result2 (stream.str());
    LOG_MSG("Set " + std::to_string(nbytes) + "B at 0x" + result + " to 0x" + result2)

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

byte* VMMem::get_base_add(){
    return mem;
}
