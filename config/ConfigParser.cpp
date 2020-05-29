#include "ConfigParser.h"
#include "op/VMOpParser.h"
#include "op/Args.h"

#include "Debug.h"

std::unique_ptr<VMConfig> ConfigParser::parse(const std::string& input){
    LOG_CALL()

    auto config = std::make_unique<VMConfig>();

    //init rpn calculator
    config->rpn_calc = std::make_unique<RPN_Calculator>();

    auto sections = split_into_sections(input);

    //TODO: parse mem config
    if(sections.count("memory") == 0){
        LOG_FUNC_MSG("no memory section in config")
        return {};//error
    }

    config->vmm = std::make_unique<VMMem>(stol(sections["memory"][0]));
    LOG_MSG("VMMem created - size: " + sections["memory"][0])

    if(sections.count("regcode") == 0){
        LOG_FUNC_MSG("no regcode size specified");
        return {};
    }

    config->reg_code_sz = stoi(sections["regcode"][0]);

    //init Args::size_map
    Args::size_map[Args::Type::R8] = config->reg_code_sz;
    Args::size_map[Args::Type::R16] = config->reg_code_sz;
    Args::size_map[Args::Type::R32] = config->reg_code_sz;
    Args::size_map[Args::Type::R64] = config->reg_code_sz;

    //parse registers config
    if(sections.count("register") == 0){
        LOG_FUNC_MSG("no register config")
        return {}; //TODO: handle error, registers not specified
    }

    for(auto& line : sections["register"]){
        LOG_MSG("parse(" + line + ")")
        auto reg_info = parse_reg_config(line);
        config->registers_symtable[reg_info.name] = reg_info;
    }

    std::vector<Register> registers{};
    for(auto& reg_info : config->registers_symtable){
        registers.push_back({reg_info.second.name, reg_info.second.code, reg_info.second.sz, reg_info.second.type});
    }
    config->vmr = std::make_unique<VMRegisters>(registers);

    LOG_FUNC_MSG("registers config parsed")


    //parse op config
    if(sections.count("opcode") == 0){
        LOG_FUNC_MSG("opcode size not specified")
        return {};
    }

    config->opc_sz = stoi(sections["opcode"][0]);

    VMOpParser parser(*(config->rpn_calc), *(config->vmr), *(config->vmm));
    for(auto& inst : sections["inst"]){
        LOG_MSG("parse(" + inst + ")")
        auto op_info = parser.parse(inst);
        config->ops_symtable[op_info.opc] = std::move(op_info);
    }

    LOG_FUNC_MSG("ops parsed")

    return config;
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
            section = std::string(line.begin() + pos + 1, line.end());
            insert_section_if_valid(section_name, section);
        }
    }

    return sections;
}

RegisterConfig ConfigParser::parse_reg_config(const std::string& input){
    std::vector<std::string> temp{};
    split(input, temp, ' ');

    //register code name type size

    RegisterConfig reg_config;
    reg_config.code = stol(temp[0]);
    reg_config.name = temp[1];
    reg_config.type = Register::type_map[temp[2]];
    reg_config.sz = stoi(temp[3]);

    LOG_TAG_MSG("register created", reg_config)

    return reg_config;
}