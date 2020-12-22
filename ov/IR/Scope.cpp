#include "Scope.h"

namespace ir {

Symbol& Scope::Define(Value* v) {
  Symbol& sym = GetSymbolTable().Define(v);

  AppendLocal(v);

  return sym;
}

Symbol& Scope::Resolve(const std::string& name, bool& ok) {
  Symbol& sym = this->GetSymbolTable().Resolve(name, ok);
  if (!ok) {
    Scope* scope = GetParent();
    sym = scope->Resolve(name, ok);
  }

  return sym;
}

Value*  Scope::ResolveValue(const std::string& name, bool& ok) {
  Symbol& sym = Resolve(name, ok);
  Value* v = sym.GetValue();

  return v;
}

void Scope::PrintInstruction(std::ostream& os, unsigned lv) const {
  std::string indent = Indent(lv);

  // Module is the root node
  if (this->GetType()->IsModuleTy()) {
    os << indent << GetID() << std::endl;
  }

  for (Instruction* inst : _instructions) {
    inst->PrintInstruction(os, lv + 1);
  }
}

void Scope::PrintSimulation(std::ostream& os, unsigned lv) const {
  std::string indent = Indent(lv);

  for (Instruction* inst : _instructions) {
    inst->PrintSimulation(os, lv + 1);
  }
}

} // end namespace ir