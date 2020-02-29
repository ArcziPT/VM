#include "Register.h"

struct RegisterConfig{
    std::string name;
    reg_sz sz;
    Register::reg_type type;
};

struct OpConfig{
    std::string name;
    //TODO: Op config
};

struct VMConfig{
    //RegistersConfig
    std::vector<RegisterConfig> registers_config;

    //TODO: VMConfig
};