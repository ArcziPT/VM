#include <fstream>

#include "VM.h"
#include "Debug.h"
#include "error/VMError.h"

VM::VM(std::unique_ptr<VMConfig> config) : config(std::move(config)){
    
}

/**
 * Main function of VM:
 * -loads exe file
 * -set ip register at he begining
 * -start main loop:
 *      -read opcode
 *      -run operaion
*/
void VM::run(const std::string& exe_path, mem_add start_add){
    //load exe file
    load_exe(exe_path, start_add);

    //set ip register to start of the exe
    auto& ip_reg = config->vmr->get_ip_reg();
    ip_reg.set_value(start_add);


    bool* exit_flag = config->vmr->get_exit_flag();
    while(*exit_flag != true){
        //read opcode of next instruction
        opcode opc = config->vmm->read(ip_reg.get_value(), config->opc_sz);

        LOG_OBJECT(opc)

        //! check if opcode exists
        //! ilegal instruction
        if(config->ops_symtable.count(opc) == 0){
            //wait before exit to allow to see screen
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10s);

            VMError::get_instance().set_error(VMError::Type::ILLEGAL_OP);
            VMError::get_instance().print_msg_exit("VM");
        }

        //! retrive operation info
        auto& op = config->ops_symtable[opc];
        
        //read args for an operation
        std::vector<byte> args = config->vmm->read_bytes(ip_reg.get_value() + config->opc_sz, op.args_sz_bytes);
        
        //update ip to next istruction's address
        ip_reg.set_value(ip_reg.get_value() + config->opc_sz + op.args_sz_bytes);

        //execute op
        (*op.vm_op)(args);
        
        LOG_MSG("op executed")
    }
}

void VM::load_exe(const std::string& exe_path, mem_add start_add){
    std::ifstream t(exe_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    
    auto str = buffer.str();
    auto bytes = str.c_str();
    auto sz = str.size();

    //! load file to vm' memory
    config->vmm->set(start_add, (byte*)bytes, (uint32_t)sz);
    LOG_MSG("exe loaded")
}