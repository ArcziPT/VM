INC=-I/home/arczipt/Desktop/linux/vm
DEBUG_FLAGS="-g -D DEBUG_LOG"

SRC=../VMBuilder.cpp ../registers/Register.cpp ../registers/VMRegisters.cpp ../VM.cpp main.cpp ../op/RPN_MicroOp.cpp ../op/VMOpParser.cpp ../op/VMOp.cpp ../op/ConditionalMicroOp.cpp ../alu_rpn/RPN_Calculator.cpp ../alu_rpn/default_funcs.cpp ../alu_rpn/RPN_Converter.cpp ../memory/VMMem.cpp ../config/VMConfig.cpp ../config/ConfigParser.cpp ../op/Args.cpp

main:
	g++ $(INC) -o vm $(SRC)

debug:
	g++ $(INC) -o vmd $(SRC) -g -D DEBUG_LOG -fvar-tracking
	
