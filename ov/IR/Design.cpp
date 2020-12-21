#include "Design.h"

namespace ir {

Design::Design(const std::string& id, Module* m)
  : Scope(id, m) { 

    Context& context = this->GetContext();
    const Type* t = context.GetType(static_cast<unsigned>(Type::DesignTyID));
    this->SetType(t);

    m->Define(this);
}

Context& Design::GetContext() const {
  return GetParent()->GetContext();
}

Procedure* Design::GetProcedure(const std::string& id) const {
  bool ok = false;
  Value* v = const_cast<Design*>(this)->ResolveValue(id, ok);
  if (!ok) return nullptr;

  Procedure* p = dynamic_cast<Procedure*>(v);
  return p;
}

Register* Design::GetRegister(const std::string& id) const {
  bool ok = false;
  Value* v = const_cast<Design*>(this)->ResolveValue(id, ok);
  if (!ok) return nullptr;

  Register* r = dynamic_cast<Register*>(v);
  return r;
}

Wire* Design::GetWire(const std::string& id) const {
  bool ok = false;
  Value* v = const_cast<Design*>(this)->ResolveValue(id, ok);
  if (!ok) return nullptr;

  Wire* w = dynamic_cast<Wire*>(v);
  return w;
}

} // end namespace ir