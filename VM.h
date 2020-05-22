#ifndef VM_H
#define VM_H

#include "config/VMConfig.h"

class VM{
public:
    VM(std::unique_ptr<VMConfig> config);

    void run(const std::string& exe_path, mem_add start_add);
    

private:
    std::unique_ptr<VMConfig> config;
};

#endif