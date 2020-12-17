#include "Design.h"

namespace ir {

Design::Design(const std::string& id, Module* m)
  : _design_id(id), _parent_module(m), _context(m->getContext()) { 
    const Type* t = _context.getType(static_cast<unsigned>(Type::DesignTyID));
    this->setType(t);

    m->Define(this);
  }

void Design::print(std::ostream& os) {
  os << _design_id;
}

} // end namespace ir