#include "Logic.h"
#include "Visitor.h"

namespace ir {

//---------------------  Logic  ------------------------//

std::string Logic::GetCType() const {
  unsigned bits = GetBits();
  if (bits <= 8) {
    return "uint8";
  } else if (8 < bits && bits <= 16) {
    return "uint16";
  }
}

std::string Logic::RangeStr() const {
  std::ostringstream   ostr;
  ostr << "[" << _hi << ":" << _lo << "]";
  return ostr.str();
}

//---------------------  Register  ------------------------//

Register::Register(const std::string& id, Scope* s, unsigned hi, unsigned lo) 
  : Logic(id, s, hi, lo) {

  const Type* t = s->GetContext().GetType(static_cast<unsigned>(Type::RegisterTyID));
  this->SetType(t);

  s->Define(this);

}

void Register::accept(Visitor* visitor) {
  visitor->visit(this);
}

//---------------------  Wire  ------------------------//

Wire::Wire(const std::string& id, Scope* s, unsigned hi, unsigned lo) 
  : Logic(id, s, hi, lo) {

  const Type* t = s->GetContext().GetType(static_cast<unsigned>(Type::WireTyID));
  this->SetType(t);

  s->Define(this);

}

void Wire::accept(Visitor* visitor) {
  visitor->visit(this);
}

} // end namespace ir