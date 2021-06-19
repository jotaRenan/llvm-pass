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

      bool runOnModule (Module &M) override {
          std::string file_name = "teste.dot";
          std::ofstream output(file_name);
          for (Function &F: M) {
            output << "digraph \"CFG for '" << F.getName().str() << "' function\" {\n";
            for (BasicBlock &BB: F) {
              output << BB.getName().str() << "\n";
            }
          }
          output << "}\n";
          output.close();
      
          return false; // always return false as it does not modify the module
      }

  };
}


char MakeDot::ID = 0;
static RegisterPass<MakeDot> X("MakeDot", "Convert bytecode to dot");