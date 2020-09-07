#include "ConditionalMicroOp.h"
#include "Debug.h"

//! calls condition micro operation and based on its result calls ctrue or cfalse
void ConditionalMicroOp::operator()(const std::vector<uint8_t>& bytes){
    auto result = condition.calculate(bytes);
    LOG_OBJECT(result);
    
    if(result != 0)
        ctrue(bytes);
    else
        cfalse(bytes);
}