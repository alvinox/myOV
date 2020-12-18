#include "Procedure.h"

namespace ir {

Procedure::Procedure(const std::string& id, Design* d)
  : Scope(id, d) {

    Context& context = this->GetContext();
    const Type* t = context.GetType(static_cast<unsigned>(Type::ProcedureTyID));
    this->SetType(t);

    d->Define(this);
}

Context& Procedure::GetContext() const {
  return GetParent()->GetContext();
}

void Procedure::Print(std::ostream& os) const {
  os << "    Proc " << GetID() << std::endl;
  // for (const std::string& r : _records._registers) {
  //   Register* reg = GetRegister(r);
  //   reg->Print(os);
  // }

  // for (const std::string& w : _records._wires) {
  //   Wire* wire = GetWire(w);
  //   wire->Print(os);
  // }
}

void Procedure::_record(Value* v) {
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