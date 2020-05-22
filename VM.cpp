#include "VM.h"

#include <fstream>

VM::VM(std::unique_ptr<VMConfig> config) : config(std::move(config)){
    
}

void VM::run(const std::string& exe_path, mem_add start_add){
    //load exe file
    std::ifstream t(exe_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    
    auto str = buffer.str();
    auto bytes = str.c_str();
    auto sz = str.size();
    config->vmm->set(start_add, (byte*)bytes, (uint32_t)sz);
}