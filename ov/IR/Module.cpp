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

void Module::Print(std::ostream& os) const {
  os << "Module " << GetID() << std::endl;
  for (const std::string& d : _records._designs) {
    Design* design = GetDesign(d);
    design->Print(os);
  }
}

void Module::_record(Value* v) {
  if (v->GetType()->IsDesignTy()) {
    _records._designs.push_back(v->GetID());
  } else {
    assert(0 && "invalid value type");
  }
}

} // end namespace ir