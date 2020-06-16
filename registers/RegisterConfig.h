#ifndef REGISTER_CONFIG_H
#define REGISTER_CONFIG_H

#include <iostream>

#include "Register.h"

struct RegisterConfig{
    std::string name;
    reg_sz sz;
    reg_code code;
    Register::Type type;

    #ifdef DEBUG_LOG
    friend std::ostream& operator<<(std::ostream& os, const RegisterConfig& reg_config);
    #endif
};

#endif