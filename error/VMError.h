#ifndef VM_ERROR_H
#define VM_ERROR_H

#include <map>

class VMError{
public:
    enum Type{
        NO_REG_CONFIG,
        NO_MEM_CONFIG,
        NO_OPC_SZ_CONFIG,
        NO_REGC_SZ_CONFIG,
        NO_OP_CONFIG,
        NO_FLAGS_CONFIG,
        NO_IP_REG_CONFIG,
        WRONG_REG_CONFIG,
        WRONG_OP_CONFIG,
        WRONG_MEM_CONFIG,
        ILLEGAL_OP,
        WRONG_ADDR,
        REGC_NOT_EXIST,
        FUNC_NOT_DEFINED,
        UNEXPECTED_EOF,
        INVALID_ARG
    };

    static VMError& get_instance();
    void set_error(Type error);
    bool is_error_set();
    Type get_error();

    void print_msg_exit(const std::string& who);
    void print_msg(const std::string& who);

    void rem_error();

    VMError(const VMError&) = delete;
    VMError operator=(const VMError&) = delete;

    std::map<Type, std::string> error_msg_map = {
        {Type::NO_REG_CONFIG, "no register config"},
        {Type::NO_MEM_CONFIG, "no memory config"},
        {Type::NO_OPC_SZ_CONFIG, "no opcode size config"},
        {Type::NO_REGC_SZ_CONFIG, "no registers' code size config"},
        {Type::NO_OP_CONFIG, "no operations config"},
        {Type::NO_FLAGS_CONFIG, "no flags config"},
        {Type::NO_IP_REG_CONFIG, "no ip register configuration"},
        {Type::WRONG_REG_CONFIG, "wrong register config"},
        {Type::WRONG_OP_CONFIG, "wrong operation config"},
        {Type::WRONG_MEM_CONFIG, "wrong memory config"},
        {Type::ILLEGAL_OP, "illegal operation (wrong opcode)"},
        {Type::WRONG_ADDR, "wrong address"},
        {Type::REGC_NOT_EXIST, "wrong register code"},
        {Type::FUNC_NOT_DEFINED, "function was not defined"},
        {Type::UNEXPECTED_EOF, "unexpected eof"},
        {Type::INVALID_ARG, "invalid argument for operation"}
    };

private:
    VMError(){};

    Type error;
    bool isErrorSet = false;
};

#endif