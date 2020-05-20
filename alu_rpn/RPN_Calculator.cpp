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
            case Token::Type::number:
                stack.push(token.val);
                break;

            case Token::Type::var:
                std::cout<<"VAR: "<<token.val<<std::endl;
                err = true;
                return 0;

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
                std::vector<reg_val> args;
                for(int i = 0; i < def.arg_num; i++){
                    args.push_back(stack.top());
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

bool RPN_Calculator::error() {
    return err;
}
