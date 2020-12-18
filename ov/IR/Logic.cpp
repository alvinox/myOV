#include "Logic.h"

namespace ir {
//---------------------  Register  ------------------------//

Register::Register(const std::string& id, Scope* s, unsigned hi, unsigned lo) 
  : Logic(id, s, hi, lo) {

  const Type* t = s->GetContext().GetType(static_cast<unsigned>(Type::RegisterTyID));
  this->SetType(t);

  s->Define(this);

}

void Register::Print(std::ostream& os) const {
  os << "    Register " << GetID() << std::endl;
}

//---------------------  Wire  ------------------------//

Wire::Wire(const std::string& id, Scope* s, unsigned hi, unsigned lo) 
  : Logic(id, s, hi, lo) {

  const Type* t = s->GetContext().GetType(static_cast<unsigned>(Type::WireTyID));
  this->SetType(t);

  s->Define(this);

}

void Wire::Print(std::ostream& os) const {
  os << "    Wire " << GetID() << std::endl;
}

} // end namespace ir