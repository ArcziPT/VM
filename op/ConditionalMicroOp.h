#ifndef CONDITIONAL_MICRO_OP_H
#define CONDITIONAL_MICRO_OP_H

#include <vector>
#include "RPN_MicroOp.h"

//!
//! \class ConditionalMicroOp uses three RPN_MicroOp to create conditional one
//! 
class ConditionalMicroOp: public MicroOp{
public:
    //! creates new micro operation
    //! @param condition - rpn micro operation, which will be evaluated
    //! @param ctrue - rpn micro operaion, which will be executed when condition is true
    //! @param cfalse - rpn micro operation, which will be executed when condition is false
    ConditionalMicroOp(const RPN_MicroOp& condition, const RPN_MicroOp& ctrue, const RPN_MicroOp& cfalse) : 
                                        condition(condition), ctrue(ctrue), cfalse(cfalse) {};

    //! execute micro operation
    //! @param bytes array of bytes containing args for RPN_MicroOps
    void operator()(const std::vector<uint8_t>& bytes);

private:
    RPN_MicroOp condition; //!< condition microp op
    RPN_MicroOp ctrue; //!< microop executed if condition is true
    RPN_MicroOp cfalse; //!< microop executed if condition is false
};

#endif