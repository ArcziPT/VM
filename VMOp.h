#ifndef VM_OP_H
#define VM_OP_H

#include "VMMem.h"
#include "utils.h"

namespace Args{
    enum Type{
        R8,
        R16,
        R32,
        R64,
        M8,
        M16,
        M32,
        M64,
        I8,
        I16,
        I32,
        I64,
    };

    struct Info{
        std::string name;
        Type type;
        reg_val val;
    };

    static std::map<std::string, Type> type_map = {
        {"r8", Type::R8},
        {"r16", Type::R16},
        {"r32", Type::R32},
        {"r64", Type::R64},
        {"m8", Type::M8},
        {"m16", Type::M16},
        {"m32", Type::M32},
        {"m64", Type::M64},
        {"i8", Type::I8},
        {"i16", Type::I16},
        {"i32", Type::I32},
        {"i64", Type::I64}
    };

    static std::map<Type, int> size_map = {
        {Type::R8, 1},
        {Type::R16, 2},
        {Type::R32, 4},
        {Type::R64, 8},
        {Type::M8, 1},
        {Type::M16, 2},
        {Type::M32, 4},
        {Type::M64, 8},
        {Type::I8, 1},
        {Type::I16, 2},
        {Type::I32, 4},
        {Type::I64, 8}
    };
}

class VMOp{
public:
    VMOp(VMRegisters& vmr, VMMem& vmm, std::vector<std::string>& values);

    void operator()(std::vector<uint8_t>& bytes);

private:
    VMRegisters& vmr;
    VMMem& vmm;

    void extract_args_values(std::vector<uint8_t>& bytes);

    std::vector<Args::Info> args_info;
    //std::vector<std::function<void(std::vector<uint8_t>&)>> inst_seq;
};

#endif