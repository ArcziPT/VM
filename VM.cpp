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

    //set ip to start of exe
    auto& ip_reg = config->vmr->get_ip_reg();
    ip_reg.set_value(start_add);

    bool* exit_flag = config->vmr->get_exit_flag();
    while(*exit_flag != true){
        opcode opc = config->vmm->read(ip_reg.get_value(), config->opc_sz);

        
    }
}