#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <string>
#include <map>


using reg_val = uint64_t; //!< \typedef reg_val
using reg_code = uint16_t; //!< \typedef reg_code
using reg_sz = uint16_t; //!< \typedef reg_sz


/**
 * \class Register provides basic operations on registers. 
 */
class Register{ 
public:
    //! \enum type of register
    enum Type{
        GENERAL,
        IP,
        FLAG
    };

    static std::map<std::string, Type> type_map; //!< maps string conatinig type name to Register::Type

    Register(const std::string& name, reg_code code, reg_sz sz, Type type);
    
    void set_value(reg_val value);
    Register::Type get_type();
    reg_val get_value();
    reg_sz get_sz();
    std::string get_name();
    reg_code get_code();

private:
    std::string name; //!< register's name
    reg_code code; //!< register's code
    reg_sz sz; //!< size in bits
    reg_val value = 0; //!< current value

    Type type; //!< type
};


#endif