#include "Design.h"

namespace ir {

Design::Design(const std::string& id, Module* m)
  : _parent_module(m), Scope(id) { 

    Context& context = this->GetContext();
    const Type* t = context.GetType(static_cast<unsigned>(Type::DesignTyID));
    this->SetType(t);
    _parent_module = m;

    m->Define(this);
}

Context& Design::GetContext() const {
  return _parent_module->GetContext();
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

void Design::Print(std::ostream& os) const {
  os << "  Design " << GetID() << std::endl;
  for (const std::string& r : _records._registers) {
    Register* reg = GetRegister(r);
    reg->Print(os);
  }

  for (const std::string& w : _records._wires) {
    Wire* wire = GetWire(w);
    wire->Print(os);
  }

}

void Design::_record(Value* v) {
  switch (v->GetType()->GetTypeID())
  {
  case Type::RegisterTyID:
    _records._registers.push_back(v->GetID()); break;
  case Type::WireTyID:
    _records._wires.push_back(v->GetID()); break;
  default:
    assert(0 && "invalid value type");
    break;
  }

}

} // end namespace ir