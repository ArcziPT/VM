#ifndef RPN_MICRO_OP_H
#define RPN_MICRO_OP_H

#include <vector>
#include <map>

#include "MicroOp.h"
#include "alu_rpn/RPN_Converter.h"
#include "registers/VMRegisters.h"
#include "memory/VMMem.h"
#include "alu_rpn/RPN_Calculator.h"
#include "Args.h"
#include "registers/FlagConfig.h"

//! 
//! \class RPN_MicroOp changes instruction encoded as string to executable operation.
//! Provides function to call the operation, which it wraps. 
//!
class RPN_MicroOp: public MicroOp{
public:
    //! create ne micro operation
    //! @param rpn_calc - vm's calculator which is used for executing micro operation
    //! @param vmr - vm's registers
    //! @param vmm - vm's memory
    //! @param flags_config - configuration of flags
    //! @param argsInfo - information about operation's operands
    //! @param inst - string containing instruction's code
    RPN_MicroOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, std::map<std::string, FlagConfig>& flags_config, const std::map<std::string, Args::Info>& argsInfo, const std::string& inst);
    RPN_MicroOp(const RPN_MicroOp& rpn_op);

    //! execute
    //! @param bytes - operation's operands
    void operator()(const std::vector<uint8_t>& bytes);
    //! execute but return value
    //! @param bytes - operation's operands
    uint64_t calculate(const std::vector<uint8_t>& bytes);

private:
    VMRegisters& vmr; //!< vm's registers
    VMMem& vmm; //!< vm's memory
    RPN_Calculator& rpn_calc; //!< vm's rpn calculator with predefined functions (for example screen managing, setting flags)
    std::map<std::string, FlagConfig>& flags_config; //!< registers' flags config

    std::map<std::string, Args::Info> argsInfo; //!< arguments' information
    std::unique_ptr<RPN> rpn; //!< rpn stack (micro operation)

    bool empty = false; //!< if micro operation is no-op

    bool saveResult = false; //!< instruction contains assigment statement
    std::string dest; //!< assigment' destination (arg's name or register's name, ...)
};

#endif