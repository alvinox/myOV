#include "SymbolTable.h"

namespace ir {

Symbol SymbolTable::nil("nil", 0, nullptr);

void SymbolTable::clear() {
  for (Symbol s : _v) {
    delete s._value;
  }
}

Symbol& SymbolTable::Define (const std::string& name, Value* value) {
  unsigned index = static_cast<unsigned>(_v.size());
  Symbol sym(name, index, value);

  _v.push_back(sym);
  _map[name] = index;

  return _v[index];
}

Symbol& SymbolTable::Resolve(const std::string& name, bool& ok) {
  ok = false;
  if (_map.find(name) != _map.end()) {
    ok = true;
    return _v[_map[name]];
  }

  return nil;
}

} // end namespace ir