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

// void Design::Print(std::ostream& os) const {
//   os << "  Design " << GetID() << std::endl;

  // for (const std::string& r : _records._registers) {
  //   Register* reg = GetRegister(r);
  //   reg->Print(os);
  // }

  // for (const std::string& w : _records._wires) {
  //   Wire* wire = GetWire(w);
  //   wire->Print(os);
  // }

  // for (const std::string& p : _records._procedures) {
  //   Procedure* proc = GetProcedure(p);
  //   proc->Print(os);
  // }

// }

// void Design::_record(Value* v) {
//   switch (v->GetType()->GetTypeID())
//   {
//   case Type::ProcedureTyID:
//     _records._procedures.push_back(v->GetID()); break;
//   case Type::RegisterTyID:
//     _records._registers.push_back(v->GetID()); break;
//   case Type::WireTyID:
//     _records._wires.push_back(v->GetID()); break;
//   default:
//     assert(0 && "invalid value type");
//     break;
//   }

// }

} // end namespace ir