#include "Module.h"

namespace ir {

Module::Module(const std::string& id, Context &c)
  : _context(c), Scope(id, nullptr) {
  const Type* t = _context.GetType(static_cast<unsigned>(Type::ModuleTyID));
  this->SetType(t);
}

Design* Module::GetDesign(const std::string& id) const {
  bool ok = false;
  Value* v = const_cast<Module*>(this)->ResolveValue(id, ok);
  if (!ok) return nullptr;

  Design* d = dynamic_cast<Design*>(v);
  return d;
}

} // end namespace ir