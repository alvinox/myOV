#include "Logic.h"

namespace ir {

//---------------------  Logic  ------------------------//
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

//---------------------  Wire  ------------------------//

Wire::Wire(const std::string& id, Scope* s, unsigned hi, unsigned lo) 
  : Logic(id, s, hi, lo) {

  const Type* t = s->GetContext().GetType(static_cast<unsigned>(Type::WireTyID));
  this->SetType(t);

  s->Define(this);

}

} // end namespace ir