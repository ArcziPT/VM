#ifndef VM_OP_H
#define VM_OP_H

#include "memory/VMMem.h"
#include "utils.h"
#include "ConditionalMicroOp.h"
#include "RPN_MicroOp.h"
#include "alu_rpn/RPN_Calculator.h"

#include <memory>

//!
//! \class VMOp wrapps sequence of micro operations 
//!
class VMOp{
public:
    //! create operation
    //! @param rpn_calc reference to vm's rpn_calculator
    //! @param vmr reference to vm's registers
    //! @param vmm reference to vm's memory
    //! @param flags_config reference to configuration of flags
    //! @param values array of strings conatining arguments' declarations and sequence of microops' instructions
    VMOp(RPN_Calculator& rpn_calc, VMRegisters& vmr, VMMem& vmm, std::map<std::string, FlagConfig>& flags_config, std::vector<std::string>& values, const std::string& name);

    //! execute
    //! @param bytes - operands
    void operator()(std::vector<uint8_t>& bytes);

    //! get arguments' size in bytes
    int get_args_sz();

    #ifdef DEBUG_LOG
    friend std::ostream& operator<<(std::ostream& os, const VMOp& vmop);
    #endif

private:
    VMRegisters& vmr;
    VMMem& vmm;
    std::map<std::string, FlagConfig>& flags_config;

    int args_sz; //!< arguments' size

    std::vector<std::unique_ptr<MicroOp>> microOps; //!< array of micro operations

    std::string name;
};

#endif