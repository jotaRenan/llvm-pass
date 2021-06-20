#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

#define DEBUG_TYPE "MakeDot"

namespace {
  struct MakeDot : public ModulePass {
      static char ID;
      MakeDot() : ModulePass(ID) {}

      void createEdges() {}

      void formatInstruction(Instruction &inst) { 
      }

      std::stringstream basicBlockToNode(BasicBlock &basic_block) {
        std::string bb_name = basic_block.getName().str(); // gets basic block name as identifier, as it is unique
        std::stringstream node;
        node << bb_name << "[shape=record,label=\"{" << bb_name << ":\\l\\l\n";
        for (const Instruction &inst : basic_block ) {
          node << "\\l";
        }
        node << "}\"];\n";
        return node;
      }

      bool runOnModule (Module &module) override {
          std::string file_name = "teste.dot";
          std::ofstream output(file_name);
          for (Function &function: module) {
            if (function.isDeclaration()) { 
              continue; // if F is an external function being called, skip to the next function
            }

            output << "digraph \"CFG for '" << function.getName().str() << "' function\" {\n";
            for (BasicBlock &basic_block: function) {
              output << basicBlockToNode(basic_block).rdbuf();
              
            }
            output << "}\n";
          }
          output.close();
      
          return false; // always return false as it does not modify the module
      }

  };
}


char MakeDot::ID = 0;
static RegisterPass<MakeDot> X("makeDot", "Convert bytecode to dot");