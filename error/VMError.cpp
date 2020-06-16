#include "VMError.h"

#include <iostream>

VMError& VMError::get_instance(){
    static VMError vme;
    return vme;
}

void VMError::set_error(Type error){
    this->error = error;
    isErrorSet = true;
}

bool VMError::is_error_set(){
    return isErrorSet;
}

VMError::Type VMError::get_error(){
    return error;
}

void VMError::print_msg_exit(const std::string& who){
    std::cout<<"["<<who<<"]: "<<error_msg_map[error]<<std::endl;
    exit(error);
}

void VMError::print_msg(const std::string& who){
    std::cout<<"["<<who<<"]: "<<error_msg_map[error]<<std::endl;
}

void VMError::rem_error(){
    isErrorSet = false;
}