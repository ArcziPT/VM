#ifndef MICRO_OP_H
#define MICRO_OP_H

#include <vector>
#include <stdint.h>

class MicroOp{
public:
    virtual void operator()(const std::vector<uint8_t>& bytes) = 0;
};

#endif