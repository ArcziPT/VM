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

using func_ptr = std::function<reg_val (const std::vector<reg_val>&)>;

//!
//! \struct func_def - definition of function, which can be called by rpn_calculator
//!
struct func_def{
    func_def() = default;
    func_def(int arg_num, const func_ptr& func){
        this->func = func;
        this->arg_num = arg_num;
    }

    func_ptr func; //! function
    int arg_num; //! number of arguments
};

//!
//! \class RPN_Calculator - calculates result of expression in rpn notation.
//! If rpn contains fnctions' calls, then they are executed.
//!
class RPN_Calculator {
public:
    //! @param rpn - sequence of tokens representing expression in rpn notation to calculate.
    reg_val calculate(const RPN& rpn);

    void add_function(const std::string& name, func_def func);

private:
    std::map<std::string, func_def> func_map = {{"+", {2, &default_funcs::add}},
                                                {"-", {2, &default_funcs::sub}},
                                                {"*", {2, &default_funcs::mul}},
                                                {"/", {2, &default_funcs::div}},
                                                {"^", {2, &default_funcs::xorr}},
                                                {"&", {2, &default_funcs::andr}},
                                                {"|", {2, &default_funcs::orr}},
                                                {"!", {1, &default_funcs::notr}}};
};


#endif //CL_CALCULATOR_RPN_CALCULATOR_H
