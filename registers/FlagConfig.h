#ifndef FLAG_CONFIG_H
#define FLAG_CONFIG_H

#include <iostream>

struct FlagConfig{
    std::string flag_name;

    std::string register_name; //register containing this flag
    int pos; //which bit
    int flag_id; //internal id

    FlagConfig(std::string flag_name, std::string register_name, int pos) : flag_name(flag_name), register_name(register_name), pos(pos) {
        flag_id = next_id;
        next_id++;
    };

    FlagConfig() = default;

    FlagConfig(const FlagConfig& flag_config){
        pos = flag_config.pos;
        flag_name = flag_config.flag_name;
        register_name = flag_config.register_name;
        flag_id = flag_config.flag_id;
    }

private:
    static int next_id;
};

#endif