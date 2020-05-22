#include "VMBuilder.h"

#include <fstream>

std::unique_ptr<VM> VMBuilder::build(const std::string& config_path){
    this->config_path = config_path;
    read_config_file();

    auto config = parser.parse(config_file);
    auto vm = std::make_unique<VM>(std::move(config));

    return vm;
}

void VMBuilder::read_config_file(){
    std::ifstream t("file.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    config_file = buffer.str();
}