#ifndef DEFAULT_FUNCS_H
#define DEFAULT_FUNCS_H

#include "Register.h"
#include <vector>

namespace default_funcs{
    static reg_val add(const std::vector<reg_val>& r);
    static reg_val sub(const std::vector<reg_val>& r);
    static reg_val mul(const std::vector<reg_val>& r);
    static reg_val div(const std::vector<reg_val>& r);
}

#endif