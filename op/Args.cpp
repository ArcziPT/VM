#include "Args.h"

std::map<Args::Type, int> Args::size_map = {
        {Args::Type::R8, -1},
        {Args::Type::R16, -1},
        {Args::Type::R32, -1},
        {Args::Type::R64, -1},
        {Args::Type::M8, 1},
        {Args::Type::M16, 2},
        {Args::Type::M32, 4},
        {Args::Type::M64, 8},
        {Args::Type::I8, 1},
        {Args::Type::I16, 2},
        {Args::Type::I32, 4},
        {Args::Type::I64, 8}
    };

    std::map<std::string, Args::Type> Args::type_map = {
        {"r8", Args::Type::R8},
        {"r16", Args::Type::R16},
        {"r32", Args::Type::R32},
        {"r64", Args::Type::R64},
        {"m8", Args::Type::M8},
        {"m16", Args::Type::M16},
        {"m32", Args::Type::M32},
        {"m64", Args::Type::M64},
        {"i8", Args::Type::I8},
        {"i16", Args::Type::I16},
        {"i32", Args::Type::I32},
        {"i64", Args::Type::I64}
    };