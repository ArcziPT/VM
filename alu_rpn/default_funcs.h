#ifndef DEFAULT_FUNCS_H
#define DEFAULT_FUNCS_H

#include "registers/Register.h"
#include <vector>

namespace default_funcs{
    reg_val add(const std::vector<reg_val>& r);
    reg_val sub(const std::vector<reg_val>& r);
    reg_val mul(const std::vector<reg_val>& r);
    reg_val div(const std::vector<reg_val>& r);
    reg_val xorr(const std::vector<reg_val>& r);
    reg_val andr(const std::vector<reg_val>& r);
    reg_val orr(const std::vector<reg_val>& r);
    reg_val notr(const std::vector<reg_val>& r);
}

#endif