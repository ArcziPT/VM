#include "VMBuilder.h"

int main(int argc, char** argv){
    VMBuilder builder;
    
    if(argc < 3)
        return -1;


    auto vm = builder.build(argv[1]);
    vm->run(argv[2], 0x0);

    return 0;
}