#ifndef VM_H
#define VM_H

#include "config/VMConfig.h"

//! \class VM 
class VM{
public:
    //! creates VM based on config
    //! @param config valid VMConfig created by ConfigParser
    VM(std::unique_ptr<VMConfig> config);

    //! starts vm
    //! @param exe_path executable file's path
    //! @param start_add address at which file should be loaded
    void run(const std::string& exe_path, mem_add start_add);

private:
    void load_exe(const std::string& exe_path, mem_add start_add);

    std::unique_ptr<VMConfig> config; //! vm config
};

#endif