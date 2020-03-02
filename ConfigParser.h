#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "VMConfig.h"

class ConfigParser{
public:
    void parse(const std::string& config);

private:
    std::unordered_map<std::string, std::vector<std::string>> split_into_sections(const std::string& config);
    RegisterConfig parse_reg_config(const std::string& config);

    VMConfig config;
};

#endif