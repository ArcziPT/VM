# INSTRUCTION


## Memory

`memory <x>` - declare x-bytes of memory


## Screen

`screen <width> <height>` - create screen with specified resolution
`font <path> <size>` - if you will print text, then vm's config has to include this line, where path is path of fontfile


## Registers

`regcode <x>` - specifies size in bytes of register code (it has to be included)

`register <code> <name> <type> <size>` - declare register (size in bits(8, 16, 32, 64), type(GEN, FLAG, IP)), one IP register has to be configured

#### FLAGS

`FLAG <name> <register_name> <position>` - create flag, which will be stored in register with specified name at the declared position (pos - which bit will hold flag's status)


## Instructions

`opcode <x>` - size of opcode in bytes

`inst <opcode> <name> <arg1,arg2,...> <inst1;inst2;...>` - creates new operation
<arg1,arg2,..> - list of arguments' declarations
<inst1;inst2;...> - list of subinstruction

How to declare arguments?
`<arg1,args2,...> = <type1#name1,type2#name2,...>` - name can be used in instructions
Type (the type of argument):
	- i8
	- i16
	- i32
	- i64 (immediate value followed by size in bits)
	- m8
	- m16
	- m32
	- m64 (memory address followed by its size in bits)
	- r8
	- r16
	- r32
	- r64 (code of register of specified size in bits)

How to declare subinstruction?
- Normal:
	`r1=r1+r2`, where r1 and r2 are names of arguments or name of register. If name of argument is surrounded by `[r]`, then value of r is pointer.
	If subinstruction contains `=`, then result of the right-hand side will bes saved in location specified by left-hand side.
- Conditional:
	`(condition)?(ctrue):(cfalse)` - condition, ctrue and cfalse are Normal subinstructions.
	If result of condition is true(!=0) ctrue will be executed, in the other case cfalse.

Every subinstruction can call predifined functions:
- `set_flag(FLAG_NAME)` - sets flag, with name=FLAG_NAME
- `isset_flag(FLAG_NAME)` - returns true if flag is set, false elsewhere.
- `unset_flag(FLAG_NAME)` - unset flag

- `put_text(t,x,y)` - put text (which is at memory address pointed by t), at x,y coordinates.
- `draw_line(sx,sy,fx,fy)` - draw line from (sx,sy) to (fx,fy)
- `set_color(r,g,b)` - sets color to specified RGB value

Examples:
- `inst 1 add r64#r1,r64#r2 r1=r1+r2` - add instruction (opcode 1), with arguments r1 (64-register), r2 (64-register), add theirs' values and save it in r1. 
- `inst 6 text i8#x,i8#y,m16#t put_text(t,x,y)` - text instruction (opcode 6), with arguments x(8-immediate), y (8-immediate), t (16 bit memorry address), calls put_text. 
- `inst 7 sflag i8#x set_flag(MY_FLAG)` - sflag instruction (opcode 7), calls set_flag, which will set MY_FLAG. (For now, there has to be at least one argument)
- `inst 8 iflag i8#x (isset_flag(MY_FLAG))?(draw_line(0,0,100,100)):(draw_line(100,0,0,100))` - if MY_FLAG is set, then draw line from (0,0) to (100,100), else draw_line from (100,0) to (0,100).


## Exe file

Executable file should contain sequence of opcodes and its' arguments (in binary), which will be executed.
Example:
- `01 a2 bc 06 cc cc ab cd 07 01`, size of opcode and register' code is 1, and we are using instruction from above example.
Steps:
- Execute instruction with opcode 1, where first register is the one with code 0xa2 (beacuse size of register's code is 1), and second one with 0xbc.
- Execute instruction with opcode 6, where x = 0xcc, y = 0xcc, t = 0xabcd.
- Execute instruction with opcode 7, where x = 0x1.
