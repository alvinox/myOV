#include "Procedure.h"

namespace ir {

const char* Procedure::SimProtoType = 
"struct %s* obj, char* d, char* q, char* mem, char* wire";

std::string Procedure::GetSimProtoType(const std::string& p) {
  char buf[256];
  sprintf(buf, Procedure::SimProtoType, p.c_str());
  return std::string(buf);
}

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
}

} // end namespace ir