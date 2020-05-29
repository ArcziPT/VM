#ifndef ARGS_H
#define ARGS_H

#include <map>

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
        int pos;
        int sz;
    };

    //When arg is of type register, only register code is passed, but it is specified by config, so it has to be initialize
    extern std::map<Type, int> size_map;

    extern std::map<std::string, Type> type_map;
}

#endif