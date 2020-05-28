#ifndef CONDITIONAL_MICRO_OP_H
#define CONDITIONAL_MICRO_OP_H

#include <vector>
#include "RPN_MicroOp.h"

class ConditionalMicroOp: public MicroOp{
public:
    ConditionalMicroOp(const RPN_MicroOp& condition, const RPN_MicroOp& ctrue, const RPN_MicroOp& cfalse) : 
                                        condition(condition), ctrue(ctrue), cfalse(cfalse) {};

    void operator()(const std::vector<uint8_t>& bytes);

private:
    RPN_MicroOp condition;
    RPN_MicroOp ctrue;
    RPN_MicroOp cfalse;
};

#endif