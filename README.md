# Bytecodes to dot
This project defines a LLVM pass that transform bytecode programs to the dot format.
It respects the following requirements:
* Each instruction must be printed with an opcode
* All the arguments of an instruction must be printed next to this instruction
* Arguments that do not have names, such as `getelementptr` in function calls, should not be printed
* Type information should not be printed

## How to run
TBD

## Authors
This project was developed by [João Pedro Rosa](https://github.com/jotaRenan) and [Paula Ribeiro](https://github.com/paula-mr) for the Static Analysis (DCC888) course from UFMG.