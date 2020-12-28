#include "VisitorSimLLVM.h"
#include "Module.h"

namespace ir {

/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,
                                                llvm::Type * Type,
                                                llvm::StringRef VarName) {
  llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                         TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(Type, nullptr, VarName);
}

//-------------------------- VisitorSimLLVM --------------------//

void VisitorSimLLVM::Pass(Module* module) {
  VisitorSimLLVM* v = new VisitorSimLLVM();
  v->_init();

  module->accept(v);

  // Print out all of the generated code.
  TheModule->print(llvm::errs(), nullptr);

  delete v;
}

void VisitorSimLLVM::visit(Module* module) {
  // Make the module, which holds all the code.
  TheModule = std::make_unique<llvm::Module>(module->GetID(), TheContext);

  module->Collect();

  for (Design* d : module->collection.designs) {
    d->accept(this);
  }
}

void VisitorSimLLVM::visit(Design* design) {
  design->Collect();

  _DesignStruct = llvm::StructType::create(TheContext, "struct." + design->GetID());
  for (Register* r : design->collection.regs) {
    r->accept(this);
  }

  for (Wire* w : design->collection.wires) {
    w->accept(this);
  }
  _DesignStruct->setBody(_design_elements);

  for (Procedure* p : design->collection.procs) {
    p->accept(this);
  }

}

void VisitorSimLLVM::visit(Procedure* proc  ) {
  std::vector<std::string> args = {
    "obj", "d", "q", "mem", "wire",
  };

  // codegen ProtoType
  llvm::PointerType* DesignStructPtr = llvm::PointerType::get(_DesignStruct, 0);
  std::vector<llvm::Type *> types = {DesignStructPtr};
  std::vector<llvm::Type *> pools(args.size() - 1, llvm::Type::getInt8PtrTy(TheContext));
  types.insert(types.end(), pools.begin(), pools.end());
  llvm::Type* returnType = llvm::Type::getVoidTy(TheContext);
  llvm::FunctionType *FT = llvm::FunctionType::get(returnType, types, false);

  Scope* s = proc->GetParent();
  std::string func_name = s->GetID() + "_" + proc->GetID();
  llvm::Function *TheFunction =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage, func_name, TheModule.get());

  unsigned idx = 0;
  for (auto &arg : TheFunction->args()) {
    arg.setName(args[idx++]);
  }

  // codegen Body
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  NamedValues.clear();
  size_t size = TheFunction->arg_size();
  for (auto &Arg : TheFunction->args()) {
  
    llvm::Type* type = nullptr;
    if (idx == 0) {
      // the design
      type = DesignStructPtr;
    } else {
      // memory pool
      type = llvm::Type::getInt8PtrTy(TheContext);
    }
  
    std::string arg_name = std::string(Arg.getName()) + ".addr";
    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, type, arg_name);
    Alloca->setAlignment(llvm::MaybeAlign(8));
   
    // Store the initial value into the alloca.
    llvm::StoreInst *Store = Builder.CreateStore(&Arg, Alloca);
    Store->setAlignment(llvm::MaybeAlign(8));

    // Add arguments to variable symbol table.
    NamedValues[std::string(Arg.getName())] = Alloca;
  }

  Builder.CreateRetVoid();
}

void VisitorSimLLVM::visit(Register*  reg   ) {
  llvm::Type * v = nullptr;
  
  unsigned bits = reg->GetBits();
  if (bits <= 8) {
    v = _variable8;
  } else if (8 < bits && bits <= 16) {
    v = _variable16;
  }
  _design_elements.push_back(v);
}

void VisitorSimLLVM::visit(Wire*      wire  ) {
  llvm::Type * v = nullptr;
  
  unsigned bits = wire->GetBits();
  if (bits <= 8) {
    v = _variable8;
  } else if (8 < bits && bits <= 16) {
    v = _variable16;
  }
  _design_elements.push_back(v);
}

void VisitorSimLLVM::_init() {
  _variable8  = llvm::StructType::create(TheContext, "strut.Variable8");
  _variable16 = llvm::StructType::create(TheContext, "strut.Variable16");
}




} // end namespace ir