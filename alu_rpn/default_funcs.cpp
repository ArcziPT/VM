#include "default_funcs.h"

reg_val default_funcs::add(const std::vector<reg_val>& r){
    return r[0] + r[1];
}

reg_val default_funcs::sub(const std::vector<reg_val>& r){
    return r[0] - r[1];
}

reg_val default_funcs::mul(const std::vector<reg_val>& r){
    return r[0] * r[1];
}

reg_val default_funcs::div(const std::vector<reg_val>& r){
    return r[0] / r[1];
}