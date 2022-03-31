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

      // 2. 记录开始时间
      Value* beginTime = nullptr;
      if (!insert_begin_inst(F, beginTime))
        return false;
      
      // 3. 方法结束时统计方法耗时，开始的时间记录作为参数
      insert_return_inst(F, beginTime);
      return false;
  }

  bool insert_begin_inst(Function &F, Value*& beginTime)
    {
      // 0.函数最开始的BasicBlock
      LLVMContext &context = F.getParent()->getContext();
      BasicBlock &bb = F.getEntryBlock();
      
      // 1. 获取要插入的函数
      FunctionCallee beginFun = F.getParent()->getOrInsertFunction("insert_begin",FunctionType::get(Type::getInt64Ty(context), {}, false));

      // 2. 构造函数
      // Value *beginTime = nullptr;
      CallInst *inst = nullptr;
      IRBuilder<> builder(context);
      //builder.SetInsertPoint(bb.getNextNode());
      inst = builder.CreateCall(beginFun);

      if (!inst) {
        llvm::errs() << "Create First CallInst Failed\n";
        return false;
      }

      // 3. 获取函数开始的第一条指令
      Instruction *beginInst = dyn_cast<Instruction>(bb.begin());

      // 4. 将inst插入
      inst->insertBefore(beginInst);
      
      // 5.根据返回值记录开始时间
      beginTime = inst;

      return true;
    }

  void insert_return_inst(Function &F, Value* beginTime)
    {
      LLVMContext &context = F.getParent()->getContext();
      for (Function::iterator I = F.begin(), E = F.end(); I != E; ++I)
      {
          
        //  函数结尾的BasicBlock
        BasicBlock &BB = *I;
        for (BasicBlock::iterator I1 = BB.begin(), E1 = BB.end(); I1 != E1; ++I1)
        {
          ReturnInst *IST = dyn_cast<ReturnInst>(I1);
          if (!IST)
            continue;
          
          // end_func 类型
          FunctionType *endFuncType = FunctionType::get(
            Type::getVoidTy(context),
            {Type::getInt8PtrTy(context),Type::getInt64Ty(context)},
            false
          );

          // end_func
          FunctionCallee endFunc = BB.getModule()->getOrInsertFunction("insert_end", endFuncType);

          // 构造end_func
          IRBuilder<> builder(&BB);
          IRBuilder<> callBuilder(context);
          CallInst* endCI = callBuilder.CreateCall(endFunc,
            {
              builder.CreateGlobalStringPtr(BB.getParent()->getName()),
              beginTime
            }
          );

          // 插入end_func(struction)
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
