#include "ConfigParser.h"

void ConfigParser::parse(const std::string& config){
    auto sections = split_into_sections(config);

    //TODO: parse mem config

    //parse registers info
    if(sections.count("registers:") == 0)
        return; //TODO: handle error, registers not specified

    std::vector<RegisterConfig> regs_config;
    for(auto& line : sections["registers:"]){
        RegisterConfig reg_config;

        //TODO: split line by ' '
        //reg_config.name = line[0]
        //...
        regs_config.push_back(reg_config);
    }
    //TODO: update config

    //auto ops_config = vmopsparser.parse(config, sections["ops:"]);
}

std::unordered_map<std::string, std::string> ConfigParser::split_into_sections(const std::string& config){
    std::unordered_map<std::string, std::string> sections{};
    
    std::vector<std::string> lines;
    //TODO: split config by '\n'


    auto insert_section_if_valid = [&sections](const std::string& s_name, const std::string& s) -> void{
        if(s_name != ""){
            sections.insert({s_name, s});
        }
    };
    std::string section_name = "";
    std::string section = "";
    for(auto& line : lines){
        //if line has ':' at the end add treat next lines 
        //as a one section until an eof or the next such a case
        /*if(){
            insert_section_if_valid(section_name, section);

            section_name = line;
        }else{
            section += line;
        }*/
    }

    insert_section_if_valid(section_name, section);

    return sections;
}