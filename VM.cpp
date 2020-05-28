#include "VM.h"

#include <fstream>

#include "Debug.h"

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
    LOG_MSG("exe loaded")

    //set ip to start of exe
    auto& ip_reg = config->vmr->get_ip_reg();
    ip_reg.set_value(start_add);

    bool* exit_flag = config->vmr->get_exit_flag();
    while(*exit_flag != true){
        //read opcode of next instruction
        opcode opc = config->vmm->read(ip_reg.get_value(), config->opc_sz);

        //ilegal instruction
        if(config->ops_symtable.count(opc) == 0)
            return; //error

        //retrive op info
        auto& op = config->ops_symtable[opc];
        
        //read args for an operation
        std::vector<byte> args = config->vmm->read_bytes(ip_reg.get_value() + config->opc_sz, op.args_sz_bytes);
        ip_reg.set_value(ip_reg.get_value() + config->opc_sz + op.args_sz_bytes);

        //execute op
        (*op.vm_op)(args);
    }
}