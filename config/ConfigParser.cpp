#include "ConfigParser.h"
#include "op/VMOpParser.h"

std::unique_ptr<VMConfig> ConfigParser::parse(const std::string& input){
    auto config = std::make_unique<VMConfig>();

    //init rpn calculator
    config->rpn_calc = std::make_unique<RPN_Calculator>();

    auto sections = split_into_sections(input);

    //TODO: parse mem config
    if(sections.count("memory") == 0)
        return;//error

    config->vmm = std::make_unique<VMMem>(stol(sections["memory"][0]));


    //parse registers config
    if(sections.count("register") == 0)
        return; //TODO: handle error, registers not specified

    for(auto& line : sections["register"]){
        auto reg_info = parse_reg_config(line);
        config->registers_symtable[reg_info.name] = reg_info;
    }

    std::vector<Register> registers{};
    for(auto& reg_info : config->registers_symtable){
        registers.push_back({reg_info.second.name, reg_info.second.code, reg_info.second.sz, reg_info.second.type});
    }
    config->vmr = std::make_unique<VMRegisters>(registers);


    //parse op config
    VMOpParser parser(*(config->rpn_calc), *(config->vmr), *(config->vmm));
    for(auto& inst : sections["inst"]){
        auto op_info = parser.parse(inst);
        config->ops_symtable[op_info.opc] = std::move(op_info);
    }
}

std::unordered_map<std::string, std::vector<std::string>> ConfigParser::split_into_sections(const std::string& input){
    std::unordered_map<std::string, std::vector<std::string>> sections{};
    
    std::vector<std::string> lines;
    //TODO: split config by '\n'
    split(input, lines, '\n');


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

RegisterConfig ConfigParser::parse_reg_config(const std::string& input){
    //TODO: parse reg config

    return {};
}