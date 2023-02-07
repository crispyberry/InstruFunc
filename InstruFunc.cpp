#include <string>
#include <system_error>
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

struct InstruFuncPass : public FunctionPass
{
  static char ID;
  InstruFuncPass() : FunctionPass(ID){}
  bool runOnFunction(Function &F) override{
    if (F.getName().startswith("insert_"))
        return false;

      // Record beginTime
      Value* beginTime = nullptr;
      if (!insert_begin_inst(F, beginTime))
        return false;
      
      // When the method ends, the statistical method takes time, and the starting time is recorded as a parameter
      insert_return_inst(F, beginTime);
      return false;
  }

  bool insert_begin_inst(Function &F, Value*& beginTime)
    {
      // 0.The BasicBlock at the beginning of the function
      LLVMContext &context = F.getParent()->getContext();
      BasicBlock &bb = F.getEntryBlock();
      
      // 1.Get the function to insert
      FunctionCallee beginFun = F.getParent()->getOrInsertFunction("insert_begin",FunctionType::get(Type::getInt64Ty(context), {}, false));

      // 2.construct this function
      // Value *beginTime = nullptr;
      CallInst *inst = nullptr;
      IRBuilder<> builder(context);
      //builder.SetInsertPoint(bb.getNextNode());
      inst = builder.CreateCall(beginFun);

      if (!inst) {
        llvm::errs() << "Create First CallInst Failed\n";
        return false;
      }

      // 3.Get the first instruction at the beginning of the function
      Instruction *beginInst = dyn_cast<Instruction>(bb.begin());

      // 4. inset inst
      inst->insertBefore(beginInst);
      
      // 5.Record the start time according to the return value
      beginTime = inst;

      return true;
    }

  void insert_return_inst(Function &F, Value* beginTime)
    {
      LLVMContext &context = F.getParent()->getContext();
      for (Function::iterator I = F.begin(), E = F.end(); I != E; ++I)
      {
          
        BasicBlock &BB = *I;
        for (BasicBlock::iterator I1 = BB.begin(), E1 = BB.end(); I1 != E1; ++I1)
        {
          ReturnInst *IST = dyn_cast<ReturnInst>(I1);
          if (!IST)
            continue;

          FunctionType *endFuncType = FunctionType::get(
            Type::getVoidTy(context),
            {Type::getInt8PtrTy(context),Type::getInt64Ty(context)},
            false
          );

          // end_func
          FunctionCallee endFunc = BB.getModule()->getOrInsertFunction("insert_end", endFuncType);

          IRBuilder<> builder(&BB);
          IRBuilder<> callBuilder(context);
          CallInst* endCI = callBuilder.CreateCall(endFunc,
            {
              builder.CreateGlobalStringPtr(BB.getParent()->getName()),
              beginTime
            }
          );

          endCI->insertBefore(IST);
        }
      }
    }
};

char InstruFuncPass::ID = 0;
static RegisterPass<InstruFuncPass> X("instrufunc","InstrumentFunction",false, false);
static void registerSkeletonPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) 
{
  PM.add(new InstruFuncPass());
}

static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerSkeletonPass);
