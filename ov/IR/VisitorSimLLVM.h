#ifndef _VISITOR_SIM_LLVM_H_
#define _VISITOR_SIM_LLVM_H_

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "Visitor.h"

namespace ir {

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::Value *> NamedValues;

class VisitorSimLLVM final : public Visitor {
 public:
  static void Pass(Module* module);

 public:
  VisitorSimLLVM()
    : Visitor(SimulationLLVMIR) { }

 public:
  virtual void visit(Module*    module) override;
  virtual void visit(Design*    design) override;
  virtual void visit(Procedure* proc  ) override;
  virtual void visit(Register*  reg   ) override;
  virtual void visit(Wire*      wire  ) override;

 private:
  void _init();

 private:
  llvm::StructType* _DesignStruct = nullptr;
  std::vector<llvm::Type*> _design_elements;

  llvm::StructType* _variable8  = nullptr;
  llvm::StructType* _variable16 = nullptr;
};

} // end namespace ir


#endif // _VISITOR_SIM_LLVM_H_