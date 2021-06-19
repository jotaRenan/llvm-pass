# Bytecodes to dot

This project defines a LLVM pass that transform bytecode programs to the dot format.
It respects the following requirements:

- Each instruction must be printed with an opcode
- All the arguments of an instruction must be printed next to this instruction
- Arguments that do not have names, such as `getelementptr` in function calls, should not be printed
- Type information should not be printed

## How to run

1. Unpack this directory into /llvm/lib/Transforms
2. Edit the file CMakeLists.txt to add `add_subdirectory(llvm-pass)`
3. Rebuild llvm typing make in your build directory
4. Execute the pass

   `opt -load build/lib/MakeDot.dylib -enable-new-pm=0 -makeDot`

   - The dylib extension is for shared libraries on MacOS, if you're running on Linux you should use the .so extension
   - The -enable-new-pm=0 flag disables the new pass manager from LLVM and is necessary to run the pass if you're running the newest distribution of LLVM

## Authors

This project was developed by [João Pedro Rosa](https://github.com/jotaRenan) and [Paula Ribeiro](https://github.com/paula-mr) for the Static Analysis (DCC888) course from UFMG.
