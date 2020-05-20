//
// Created by ArcziPT on 09.07.2019.
//

#include "RPN_Converter.h"
#include <cctype>
#include <sstream>
#include <stack>

RPN_ptr RPN_Converter::convert(const std::string &input) {
    auto rpn = std::make_unique<RPN>();

    std::vector<Token> output_queue;
    std::stack<Token> operator_stack;

    auto tokens = get_tokens(input);

    //actual algorithm converting tokens into rpn
    //https://en.wikipedia.org/wiki/Reverse_Polish_notation
    for(auto& token : tokens){
        switch(token.type){
            case Token::Type::var:
                output_queue.push_back(token);
                break;
            case Token::Type::number:
                output_queue.push_back(token);
                break;

            case Token::Type::func:
                operator_stack.push(token);
                break;

            case Token::Type::op:
                if(!operator_stack.empty()){
                    while((operator_stack.top().type == Token::Type::func or
                           (operator_stack.top().type == Token::Type::op and has_greater_precedence(operator_stack.top().data, token.data)) or
                           (has_equal_precedence(token.data, operator_stack.top().data) and left_associativity[operator_stack.top().data])) and
                          operator_stack.top().type != Token::Type::left_p)
                    {
                        output_queue.push_back(operator_stack.top());
                        operator_stack.pop();

                        if(operator_stack.empty())
                            break;
                    }
                }

                operator_stack.push(token);
                break;

            case Token::Type::left_p:
                operator_stack.push(token);
                break;

            case Token::Type::right_p:
                while(operator_stack.top().type != Token::Type::left_p){
                    output_queue.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                if(operator_stack.top().type == Token::Type::left_p)
                    operator_stack.pop();
                break;
        }
    }

    while(!operator_stack.empty()){
        output_queue.push_back(operator_stack.top());
        operator_stack.pop();
    }

    rpn->stack = output_queue;
    return rpn;
}

/*
 * change input into tokens:
 * - numbers
 * - functions
 * - operators and parenthesis
 *
 * Ignores ','
 */
std::vector<Token> RPN_Converter::get_tokens(const std::string &input) {
    std::vector<Token> tokens;

    std::stringstream num_stream;
    std::stringstream func_stream;

    //TODO: decimal point (.)
    for(auto it = input.begin(); it != input.end();){
        if(isdigit(*it)){
            while(it != input.end() and isdigit(*it)){
                num_stream << *it;
                it++;
            }

            std::string data;
            num_stream >> data;

            Token token;
            token.data = data;
            token.val = stol(data);
            token.type = Token::Type::number;

            tokens.push_back(token);
            num_stream.clear();

            if(it == input.end())
                break;
        }else if(*it == ','){
            it++;
            continue;
        }else if(*it != '(' and *it != ')' and precedence.count(std::string(1, *it)) == 0){ //not an operator
            while(it != input.end() and *it != '(' and *it != ')' and precedence.count(std::string(1, *it)) == 0){
                func_stream << *it;
                it++;
            }

            std::string data;
            func_stream >> data;

            Token token;
            token.val = data;

            if((it+1) != input.end() && *(it+1) == '(') 
                token.type = Token::Type::func;
            else
                token.type = Token::Type::var;
            

            tokens.push_back(token);
            func_stream.clear();

            if(it == input.end())
                break;
        }else{
            Token token;
            token.data = std::string(1, *it);

            if(token.data == "(")
                token.type = Token::Type::left_p;
            else if(token.data == ")")
                token.type = Token::Type::right_p;
            else
                token.type = Token::Type::op;

            tokens.push_back(token);
            it++;
        }
    }

    return tokens;
}

bool RPN_Converter::has_greater_precedence(const std::string &op1, const std::string &op2) {
    return precedence[op1] > precedence[op2];
}

bool RPN_Converter::has_equal_precedence(const std::string &op1, const std::string &op2) {
    return  precedence[op1] == precedence[op2];
}