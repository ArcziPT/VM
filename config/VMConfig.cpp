#include "VMConfig.h"

#ifdef DEBUG_LOG
    std::ostream& operator<<(std::ostream& os, const RegisterConfig& reg_config){
        os<<"name="<<reg_config.name<<" sz="<<reg_config.sz<<" code="<<reg_config.code;
        return os;
    };
#endif