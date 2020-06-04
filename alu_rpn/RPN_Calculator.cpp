//
// Created by ArcziPT on 09.07.2019.
//

#include "RPN_Calculator.h"
#include <stack>
#include <functional>

reg_val RPN_Calculator::calculate(const RPN& rpn) {
    std::stack<reg_val> stack;

    //algorithm to calculate rpn expression
    //https://en.wikipedia.org/wiki/Reverse_Polish_notation
    for(auto& token : rpn.stack){
        switch(token.type){
            case Token::Type::var:
            case Token::Type::number:
                stack.push(token.val);
                break;

            case Token::Type::func:
            case Token::Type::op:
                //check if function exists
                if(func_map.count(token.data) == 0){
                    std::cout<<"Function(operator) \""<<token.data<<"\" not defined\n";
                    err = true;
                    return 0;
                }

                auto def = func_map[token.data];

                //get arguments from stack
                //order is reversed
                std::vector<reg_val> args(def.arg_num, 0);
                for(int i = 0; i < def.arg_num; i++){
                    args[def.arg_num-i-1] = stack.top();
                    stack.pop();
                }

                double ret;
                ret = def.func(args);

                stack.push(ret);
                break;
        }
    }

    return stack.top();
}

void RPN_Calculator::add_function(const std::string& name, func_def func){
    func_map.insert({name, func});
}

bool RPN_Calculator::error() {
    return err;
}
