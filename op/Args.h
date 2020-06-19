#ifndef ARGS_H
#define ARGS_H

#include <map>

/**
 * \namespace Args consists of structures for managing operadns
 */ 
namespace Args{

    //! \enum Type - types of operations' arguments
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

    //!
    //! \struct Info basic information about operand.
    //!
    struct Info{
        std::string name; //!< argument's name
        Type type; //!< type
        int pos; //!< starting position in operation's array of arguments' bytes
        int sz; //!< size in bytes
    };

    extern std::map<Type, int> size_map; //!< maps arg's type to its size
    //!< When arg has a register type, only register code is passed, but it's size is specified by config, so it has to be initialized

    extern std::map<std::string, Type> type_map; //!< maps string literal to arg's type
}

#endif