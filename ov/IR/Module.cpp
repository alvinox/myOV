#include "Module.h"

namespace ir {

Symbol& Module::Define(Design* design) {
  const std::string& name = design->ID();

  Symbol& sym = _symtab.Define(name, design);
  return sym;
}

void Module::print(std::ostream& os) {
  std::vector<Value*> designs;

  SymbolTable::const_iterator it = _symtab.begin();
  for (; it != _symtab.end(); ++it) {
    Value* v = it->getValue();
    const Type* t = v->getType();
    Type::TypeID tid = t->getTypeID();

    switch (tid)
    {
    case Type::DesignTyID: designs.push_back(v); break;
    
    default:
      break;
    }
  }

  for (auto v : designs) {
    v->print(os);
  }

}

} // end namespace ir