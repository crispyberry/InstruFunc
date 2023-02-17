#include <string>
#include <system_error>
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

struct InstruFuncPass : public FunctionPass{
  static char ID;
  InstruFuncPass() : FunctionPass(ID){}
  bool runOnFunction(Function &F) override{
    if (F.getName().startswith("insert_"))
        return false;

    if (!insert_begin_inst(F))
      return false;

    if (!insert_main_out(F))
      return false;

    return false;
  }

  bool insert_main_out(Function &F){
    if(F.getName() == "main"){

      LLVMContext &context = F.getParent()->getContext();

      //BasicBlock *lastBB = &*(std::find_if(F.begin(), F.end(), [](BasicBlock &BB) { return succ_begin(&BB) == succ_end(&BB); }));
      BasicBlock *lastBB = &*(--F.end());

      for (BasicBlock::iterator Ins = lastBB->begin(), EndIns = lastBB->end(); Ins != EndIns; ++Ins){
        ReturnInst *endInst = dyn_cast<ReturnInst>(Ins);
        if (!endInst)
          continue;
        FunctionCallee endFun = F.getParent()->getOrInsertFunction("insert_out", FunctionType::get(Type::getVoidTy(context), {}, false));
        CallInst *collect = nullptr;
        IRBuilder<> callBuilder(context);
        collect = callBuilder.CreateCall(endFun);
        if (!collect) {
          llvm::errs() << "Create Collect CallInst Failed\n";
          return false;
        }
        collect->insertBefore(endInst);
        return true;
      }
    }
    return false;
  }

  bool insert_begin_inst(Function &F){
    LLVMContext &context = F.getParent()->getContext();
    
    for(Function::iterator BB = F.begin(), End = F.end(); BB != End; ++BB){
    
    auto firstNonPhiInst = std::find_if(BB->begin(), BB->end(),
    [](Instruction &I) { return !isa<PHINode>(&I); });

      if (firstNonPhiInst != BB->end()) {
        Instruction *insertPoint = &*firstNonPhiInst;
        FunctionCallee beginFun = F.getParent()->getOrInsertFunction("insert_counter", FunctionType::get(
          Type::getVoidTy(context),Type::getInt8PtrTy(context), false
          ));
        CallInst *probe = nullptr;
        IRBuilder<> callBuilder(context);
        BasicBlock * BBForBuilder = &*BB;
        IRBuilder<> builder(BBForBuilder);
        probe = callBuilder.CreateCall(beginFun, {
              builder.CreateGlobalStringPtr(BB->getName()),
            });

        if (!probe) {
          llvm::errs() << "Create First CallInst Failed\n";
          return false;
        }
        probe->insertBefore(insertPoint);
      }
      else {
        continue;
      }
    }
    return true;
  }
};

char InstruFuncPass::ID = 0;
static RegisterPass<InstruFuncPass> X("instrufunc","InstrumentFunction",false, false);
static void registerSkeletonPass(const PassManagerBuilder &, legacy::PassManagerBase &PM){
  PM.add(new InstruFuncPass());
}

//static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerSkeletonPass);
