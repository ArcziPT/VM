//
// Created by ArcziPT on 09.07.2019.
//

#ifndef CL_CALCULATOR_RPN_CALCULATOR_H
#define CL_CALCULATOR_RPN_CALCULATOR_H

#include "RPN_Converter.h"
#include "registers/Register.h"
#include "default_funcs.h"

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

    void add_function(const std::string& name, func_def func);

private:
    std::map<std::string, func_def> func_map = {{"+", {2, &default_funcs::add}},
                                                {"-", {2, &default_funcs::sub}},
                                                {"*", {2, &default_funcs::mul}},
                                                {"/", {2, &default_funcs::div}},
                                                {"^", {2, &default_funcs::xorr}}};
};


#endif //CL_CALCULATOR_RPN_CALCULATOR_H
