#include "ConfigParser.h"

void ConfigParser::parse(const std::string& config){
    auto sections = split_into_sections(config);

    //TODO: parse mem config

    //parse registers info
    if(sections.count("registers:") == 0)
        return; //TODO: handle error, registers not specified

    std::vector<RegisterConfig> regs_config;
    for(auto& line : sections["registers:"]){
        regs_config.push_back(parse_reg_config(line));
    }
    //TODO: update config

    //auto ops_config = vmopsparser.parse(config, sections["ops:"]);
}

std::unordered_map<std::string, std::vector<std::string>> ConfigParser::split_into_sections(const std::string& config){
    std::unordered_map<std::string, std::vector<std::string>> sections{};
    
    std::vector<std::string> lines;
    //TODO: split config by '\n'


    auto insert_section_if_valid = [&sections](const std::string& s_name, const std::string& s) -> void{
        if(s_name != ""){
            if(sections.count(s_name) == 0)
                sections[s_name] = std::vector<std::string>{};
            sections[s_name].push_back(s);
        }
    };

    std::string section_name = "";
    std::string section;
    for(auto& line : lines){
        int pos = line.find(' ');
        if(pos != std::string::npos){
            section_name = std::string(line.begin(), line.begin() + pos);
            section = std::string(line.begin() + pos, line.end());
            insert_section_if_valid(section_name, section);
        }
    }

    return sections;
}

RegisterConfig ConfigParser::parse_reg_config(const std::string& config){
    //TODO: parse reg config

    return {};
}