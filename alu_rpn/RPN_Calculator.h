//
// Created by ArcziPT on 09.07.2019.
//

#ifndef CL_CALCULATOR_RPN_CALCULATOR_H
#define CL_CALCULATOR_RPN_CALCULATOR_H

#include "RPN_Converter.h"
#include "registers/Register.h"
#include <functional>
#include <variant>

//calc_func_ptr is used by hardcoded function whereas dynamic ones make use of rpn_func_ptr
using func_ptr = std::function<reg_val (const std::vector<reg_val>&)>;
// using rpn_func_ptr = std::function<std::unique_ptr<RPN> (const std::vector<reg_val>&)>;
// using func_ptr_variant = std::variant<calc_func_ptr, rpn_func_ptr>;

struct func_def{
    func_def() = default;
    func_def(int arg_num, const func_ptr& func){
        this->func = func;
        this->arg_num = arg_num;
    }

    func_ptr func;
    int arg_num;
};


class RPN_Calculator {
public:
    reg_val calculate(const RPN& rpn);
    void config(const std::map<std::string, func_def>& func_map, bool var_mode);

    bool error();

private:
    bool err = false;
    std::map<std::string, func_def> func_map;
};


#endif //CL_CALCULATOR_RPN_CALCULATOR_H
