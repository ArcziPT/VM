INC=-I/home/arczipt/Desktop/linux/vm -I/usr/include/SDL2
DEBUG_FLAGS="-g -D DEBUG_LOG"

SRC=../VMBuilder.cpp ../registers/Register.cpp ../registers/VMRegisters.cpp ../error/VMError.cpp ../screen/VMScreen.cpp ../VM.cpp main.cpp ../op/RPN_MicroOp.cpp ../op/VMOpParser.cpp ../op/VMOp.cpp ../op/ConditionalMicroOp.cpp ../alu_rpn/RPN_Calculator.cpp ../alu_rpn/default_funcs.cpp ../alu_rpn/RPN_Converter.cpp ../memory/VMMem.cpp ../registers/RegisterConfig.cpp ../registers/FlagConfig.cpp ../config/ConfigParser.cpp ../op/Args.cpp

main:
	g++ $(SRC) $(INC) -lSDL2 -lSDL2_ttf -pthread -o vm

debug:
	g++ -g -D DEBUG_LOG -fvar-tracking $(SRC) $(INC) -lSDL2 -lSDL2_ttf -pthread -o vmd
	
