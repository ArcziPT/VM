#include "ConditionalMicroOp.h"
#include "Debug.h"

//! calls condition micro operation and based on its result calls ctrue or cfalse
void ConditionalMicroOp::operator()(const std::vector<uint8_t>& bytes){
    if(condition.calculate(bytes) != 0)
        ctrue(bytes);
    else
        cfalse(bytes);
}