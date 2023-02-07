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
    if (F.getName().startswith("insert_mem"))
        return false;

    if (!insert_begin_inst(F))
      return false;

    return false;
  }

  bool insert_begin_inst(Function &F){
    LLVMContext &context = F.getParent()->getContext();
    FunctionCallee beginFun = F.getParent()->getOrInsertFunction("insert_mem", FunctionType::get(Type::getVoidTy(context), {}, false));
 
    for(Function::iterator BB = F.begin(), End = F.end(); BB != End; ++BB){
      //errs()<<BB->getName()<<" "<<BB->getTerminator()->getNumSuccessors()<<"\n";
      Instruction *beginInst = dyn_cast<Instruction>(BB->begin());
      //beginInst->dump();
      //errs()<<"\n";
      CallInst *probe = nullptr;
      //IRBuilder<> builder(BB);
      IRBuilder<> callBuilder(context);
      probe = callBuilder.CreateCall(beginFun);
      if (!probe) {
        llvm::errs() << "Create First CallInst Failed\n";
        return false;
      }
      probe->insertAfter(beginInst);
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
