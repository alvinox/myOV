#ifndef _IRBUILDER_H_
#define _IRBUILDER_H_

#include "Instruction.h"
#include "Scope.h"
#include "Design.h"
#include "Logic.h"

namespace ir {

class IRBuilder {
 public:
  IRBuilder() : _scope(nullptr) { }

 public:
  void SetInsertPoint(Scope* s) { _scope = s; }

  Instruction* CreateDesign     (Design* design);
  Instruction* CreateProcedure  (Procedure* proc);
  Instruction* CreateRegister   (Register* reg);
  Instruction* CreateWire       (Wire* wire);
  Instruction* CreateSetValue   (Logic* l, Value* v);
  Instruction* CreateGetValue   (Logic* l);
  Instruction* CreateAssign     (Logic* l, Value* v);
 
 private:
  Instruction* _insert(Instruction* inst) { return _scope->AppendInstruction(inst); }

 private:
  Scope* _scope;
};

} // end namespace ir

#endif // _IRBUILDER_H_