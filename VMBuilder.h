#ifndef VM_BUILDER_H
#define VM_BUILDER_H

#include "VM.h"
#include "config/ConfigParser.h"

/**
*   \class VMBuilder used for building customized VM 
*   from specified config file.
*/
class VMBuilder{
public:
    //! function builds VM from config file and returns uniqe ptr 
    //! @param config_path path to config file
    std::unique_ptr<VM> build(const std::string& config_path);

private:
    ConfigParser parser;

    std::string config_path;
    std::string config_file;
    void read_config_file();
};

#endif