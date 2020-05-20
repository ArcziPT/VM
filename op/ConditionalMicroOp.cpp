#include "ConditionalMicroOp.h"

void ConditionalMicroOp::operator()(const std::vector<uint8_t>& bytes){
    if(condition.calculate(bytes) != 0)
        ctrue(bytes);
    else
        cfalse(bytes);
    
}