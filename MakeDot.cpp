#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Constants.h"


using namespace llvm;

#define DEBUG_TYPE "MakeDot"

namespace {
  struct MakeDot : public ModulePass {
      static char ID;
      int anonymousInstCounter;
      MakeDot() : ModulePass(ID) {
        anonymousInstCounter = 0;
      }

      void createEdges() {}

      std::string createInstructionName() {
        std::string name = '%' + std::to_string(anonymousInstCounter);
        anonymousInstCounter++;
        return name;
      }

      std::stringstream formatOperand(Value* operand) {
        std::stringstream fOp;
        if (operand->hasName()) { // outputs operand name if it exists
          fOp << " " << operand->getName().str();
        } else if (ConstantInt *constant = dyn_cast<ConstantInt>(operand)) { // else outputs value if operand is a constant
          fOp << " " << constant->getZExtValue();
        }
        return fOp;
      }

      std::stringstream formatInstruction(Instruction &inst) { 
        std::stringstream fInst;
        if (!inst.hasName() && !inst.getType()->isVoidTy()) { // if instruction does not have a name and is not void create a name for it
          std::string instName = createInstructionName();
          inst.setName(instName); // set instruction name so it can be referenced later
        }
        if (inst.hasName()) { // output instruction name if it exists
          fInst << inst.getName().str() << " = ";
        }
        fInst << inst.getOpcodeName(); // output opcode
        for(unsigned int i=0; i < inst.getNumOperands(); i++) {	// output instruction's operands
          Value* operand = inst.getOperand(i);
          fInst << formatOperand(operand).rdbuf();
        }
        return fInst;
      }

      std::stringstream basicBlockToNode(BasicBlock &basic_block) {
        std::string bb_name = basic_block.getName().str(); // gets basic block name as identifier, as it is unique
        std::stringstream node;
        node << '\t' << bb_name << "[shape=record,\n\t\tlabel=\"{" << bb_name << ":\\l\\l\n";
        for (Instruction &inst : basic_block) {
          node << "\t\t\t" << formatInstruction(inst).rdbuf() << " \\l\n";
        }
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
              output << "\t\t}\"\n";
              output << "\t];\n";
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