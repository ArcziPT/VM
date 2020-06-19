#ifndef REGISTER_CONFIG_H
#define REGISTER_CONFIG_H

#include <iostream>

#include "Register.h"


/**
 * \struct RegisterConfig contains information about registers of VM.
 */
struct RegisterConfig{
    std::string name; //! name of register
    reg_sz sz; //! register's size
    reg_code code; //! register's code
    Register::Type type; //! register's type

    #ifdef DEBUG_LOG
    friend std::ostream& operator<<(std::ostream& os, const RegisterConfig& reg_config);
    #endif
};

#endif