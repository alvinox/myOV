#include "Logic.h"

namespace ir {
  Register::Register(const std::string& id, Design* d, unsigned hi, unsigned lo) 
    : Logic(id, d, hi, lo) {

    const Type* t = d->context().getType(static_cast<unsigned>(Type::RegisterTyID));
    this->setType(t);

  }

  Wire::Wire(const std::string& id, Design* d, unsigned hi, unsigned lo) 
    : Logic(id, d, hi, lo) {

    const Type* t = d->context().getType(static_cast<unsigned>(Type::WireTyID));
    this->setType(t);

  }

} // end namespace ir