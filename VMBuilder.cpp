#include "VMBuilder.h"

#include <fstream>

#include "Debug.h"

std::unique_ptr<VM> VMBuilder::build(const std::string& config_path){
    this->config_path = config_path;
    read_config_file();

    auto config = parser.parse(config_file);
    auto vm = std::make_unique<VM>(std::move(config));

    LOG_MSG("vm built")

    return vm;
}

void VMBuilder::read_config_file(){
    std::ifstream t(config_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    config_file = buffer.str();
}