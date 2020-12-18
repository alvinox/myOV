#ifndef _IRBUILDER_H_
#define _IRBUILDER_H_

#include "Instruction.h"
#include "Scope.h"
#include "Design.h"

namespace ir {

class Scope;
class Design;

class IRBuilder {
 public:
  IRBuilder() : _scope(nullptr) { }

 public:
  void SetInsertPoint(Scope* s) { _scope = s; }

  Instruction* CreateDesign(Design* design);
 
 private:
  Instruction* _insert(Instruction* inst) { return _scope->InsertInstruction(inst); }

 private:
  Scope* _scope;
};

} // end namespace ir

#endif // _IRBUILDER_H_