#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "VMConfig.h"

//!
//! \class ConfigParser creates VMConfig from configuration file.
//!
class ConfigParser{
public:
    //! create configuration
    //! @param input - configuration file's content
    std::unique_ptr<VMConfig> parse(const std::string& input);

private:
    std::unordered_map<std::string, std::vector<std::string>> split_into_sections(const std::string& input);
    RegisterConfig parse_reg_config(const std::string& input);
};

#endif