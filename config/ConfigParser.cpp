#include "ConfigParser.h"
#include "op/VMOpParser.h"
#include "op/Args.h"
#include "error/VMError.h"

#include "Debug.h"

std::unique_ptr<VMConfig> ConfigParser::parse(const std::string& input){
    auto config = std::make_unique<VMConfig>();

    //init rpn calculator
    config->rpn_calc = std::make_unique<RPN_Calculator>();

    //! split file into sections
    //every line is a section and its name is specified at the begining 
    auto sections = split_into_sections(input);

    //! parse mem config
    if(sections.count("memory") == 0){
        VMError::get_instance().set_error(VMError::Type::NO_MEM_CONFIG);
        VMError::get_instance().print_msg_exit("ConfigParser");
    }

    config->vmm = std::make_unique<VMMem>(stol(sections["memory"][0]));
    LOG_MSG("VMMem created - size: " + sections["memory"][0])


    //! parse registers' config
    if(sections.count("regcode") == 0){
        VMError::get_instance().set_error(VMError::Type::NO_REGC_SZ_CONFIG);
        VMError::get_instance().print_msg_exit("ConfigParser");
    }

    config->reg_code_sz = stoi(sections["regcode"][0]);

    //init Args::size_map with register code size
    Args::size_map[Args::Type::R8] = config->reg_code_sz;
    Args::size_map[Args::Type::R16] = config->reg_code_sz;
    Args::size_map[Args::Type::R32] = config->reg_code_sz;
    Args::size_map[Args::Type::R64] = config->reg_code_sz;

    if(sections.count("register") == 0){
        VMError::get_instance().set_error(VMError::Type::NO_REG_CONFIG);
        VMError::get_instance().print_msg_exit("ConfigParser");
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

    LOG_MSG("registers config parsed")



    //parse FLAGS
    if(sections.count("FLAG") == 0){
        VMError::get_instance().set_error(VMError::Type::NO_FLAGS_CONFIG);
        VMError::get_instance().print_msg_exit("ConfigParser");
    }

    //indexed by flag_id
    for(auto& flag : sections["FLAG"]){
        std::vector<std::string> t{};
        split(flag, t, ' ');

        if(t.size() < 3)
            continue;

        auto flag_config = FlagConfig(t[0], t[1], stoi(t[2]));
        config->flags_config_map.insert({t[0], flag_config}); //indexed by name
        config->flags_config.push_back(flag_config); //indexed by flag_id
    }

    if(config->flags_config.size() == 0){
        VMError::get_instance().set_error(VMError::Type::NO_FLAGS_CONFIG);
        VMError::get_instance().print_msg_exit("ConfigParser");
    }

    //create special functions for setting, unsetting and checking status of a flag
    auto set_flag = [&vmr = *(config->vmr), &flags_config = config->flags_config](const std::vector<reg_val>& args) -> reg_val{
        auto& flag_config = flags_config[args[0]];
        auto& reg = vmr[flag_config.register_name];

        auto val = reg.get_value();
        val |= (0x1 << flag_config.pos);
    };

    auto unset_flag = [&vmr = *(config->vmr), &flags_config = config->flags_config](const std::vector<reg_val>& args) -> reg_val{
        auto& flag_config = flags_config[args[0]];
        auto& reg = vmr[flag_config.register_name];

        auto val = reg.get_value();
        val &= ~(0x1 << flag_config.pos);
    };

    auto isset_flag = [&vmr = *(config->vmr), &flags_config = config->flags_config](const std::vector<reg_val>& args) -> reg_val{
        auto& flag_config = flags_config[args[0]];
        auto& reg = vmr[flag_config.register_name];

        auto val = reg.get_value();
        //returns 1 if flag is set, 0 otherwise
        return (val & 0x1 << flag_config.pos);
    };

    //regsiter them in vm's rpn_calc
    config->rpn_calc->add_function("set_flag", func_def(1, set_flag));
    config->rpn_calc->add_function("unset_flag", func_def(1, unset_flag));
    config->rpn_calc->add_function("isset_flag", func_def(1, isset_flag));




    //parse op config
    if(sections.count("opcode") == 0){
        VMError::get_instance().set_error(VMError::Type::NO_OP_CONFIG);
        VMError::get_instance().print_msg_exit("ConfigParser");
    }

    config->opc_sz = stoi(sections["opcode"][0]);

    VMOpParser parser(*(config->rpn_calc), *(config->vmr), *(config->vmm), config->flags_config_map);
    for(auto& inst : sections["inst"]){
        LOG_MSG("parse(" + inst + ")")
        auto op_info = parser.parse(inst);
        config->ops_symtable[op_info.opc] = std::move(op_info);
    }

    LOG_MSG("ops parsed")



    //! parse screen config
    if(sections.count("screen") != 0){
        std::vector<std::string> t{};
        split(sections["screen"][0], t, ' ');

        config->vms = std::make_unique<VMScreen>(stoi(t[0]), stoi(t[1]));

        auto draw_line = [&vms = *(config->vms)](const std::vector<reg_val>& args) -> reg_val{
            vms.draw_line(args[0], args[1], args[2], args[3]);
            return 0;
        };

        auto clear = [&vms = *(config->vms)](const std::vector<reg_val>& args) -> reg_val{
            vms.clear();
            return 0;
        };

        auto set_color = [&vms = *(config->vms)](const std::vector<reg_val>& args) -> reg_val{
            vms.set_color(args[0], args[1], args[2]);
            return 0;
        };

        auto put_text = [&vms = *(config->vms), &vmm = *(config->vmm)](const std::vector<reg_val>& args) -> reg_val{
            char* text = (char*)vmm.get_base_add() + args[0];
            vms.put_text(text, args[1], args[2]);
            return 0;
        };

        config->rpn_calc->add_function("draw_line", func_def(4, draw_line));
        config->rpn_calc->add_function("clear", func_def(0, clear));
        config->rpn_calc->add_function("set_color", func_def(3, set_color));
        config->rpn_calc->add_function("put_text", func_def(3, put_text));

        if(sections.count("font") != 0){
            std::vector<std::string> t{};
            split(sections["font"][0], t, ' ');
            config->vms->set_font(t[0], stoi(t[1]));
        }
    }

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

    if(temp.size() < 4){
        VMError::get_instance().set_error(VMError::Type::WRONG_REG_CONFIG);
        VMError::get_instance().print_msg_exit("Register config parser");
    }

    RegisterConfig reg_config;
    try{
        reg_config.code = stol(temp[0]);
        reg_config.name = temp[1];
        reg_config.type = Register::type_map[temp[2]];
        reg_config.sz = stoi(temp[3]);
    }catch(const std::invalid_argument& ia){
        VMError::get_instance().set_error(VMError::Type::WRONG_REG_CONFIG);
        VMError::get_instance().print_msg_exit("Register config parser");
    }

    LOG_OBJECT(reg_config)

    return reg_config;
}