//
// Created by ArcziPT on 09.07.2019.
//

#ifndef CL_CALCULATOR_RPN_CONVERTER_H
#define CL_CALCULATOR_RPN_CONVERTER_H

#include <vector>
#include <cstring>
#include <iostream>
#include <memory>
#include <map>

#include "registers/Register.h"

//!
//! \struct Token - token's information. Every RPN consist of sequence of tokens.
//!
struct Token{
    std::string data; //!< token in string format
    reg_val val; //!< token's value (in case of Type::var it will be set later)
    bool ptr = false; //!< token is ptr, when it is surrounded by [] and it has Type::var
    
    enum Type{
        number,
        func,
        left_p,
        right_p,
        op,
        var
    } type;
};

//!
//! \struct RPN 
//!
struct RPN{
    std::vector<Token> stack;

    #ifdef DEBUG_LOG
    friend std::ostream& operator<<(std::ostream& os, const RPN& rpn);
    #endif
};

using RPN_ptr = std::unique_ptr<RPN>; //!< \typedef RPN_ptr

//!
//! \class converts infix notation to rpn
//!
class RPN_Converter {
public:
    RPN_ptr convert(const std::string& input);

private:
    std::map<std::string, int> precedence = {
        {"^", 4},
        {"*", 3},
        {"/", 3},
        {"+", 2},
        {"-", 2}
    };
    std::map<std::string, bool> left_associativity = {
        {"^", false},
        {"*", true},
        {"/", true},
        {"+", true},
        {"-", true}
    };
    bool var_mode = false;

    std::vector<Token> get_tokens(const std::string& input);
    bool has_greater_precedence(const std::string& op1, const std::string& op2);  //does op1 has greater precedence?
    bool has_equal_precedence(const std::string& op1, const std::string& op2);
};

#endif //CL_CALCULATOR_RPN_CONVERTER_H
