#include "Scope.h"

namespace ir {

Symbol& Scope::Define(Value* v) {
  Symbol& sym = GetSymbolTable().Define(v);

  _record(v);

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

} // end namespace ir