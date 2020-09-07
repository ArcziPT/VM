#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "VMConfig.h"

using Sections = std::unordered_map<std::string, std::vector<std::string>>;

//!
//! \class ConfigParser creates VMConfig from configuration file.
//!
class ConfigParser{
public:
    //! create configuration
    //! @param input - configuration file's content
    std::unique_ptr<VMConfig> parse(const std::string& input);

private:
    Sections split_into_sections(const std::string& input);
    RegisterConfig parse_reg_config(const std::string& input);

    void parse_mem_config(Sections& sections, const std::unique_ptr<VMConfig>& config);
    void parse_register_config(Sections& sections, const std::unique_ptr<VMConfig>& config);
    void parse_flag_config(Sections& sections, const std::unique_ptr<VMConfig>& config);
    void parse_op_config(Sections& sections, const std::unique_ptr<VMConfig>& config);
    void parse_screen_config(Sections& sections, const std::unique_ptr<VMConfig>& config);

    void add_flag_functions(const std::unique_ptr<VMConfig>& config);
};

#endif