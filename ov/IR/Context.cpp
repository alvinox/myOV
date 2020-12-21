#include "Context.h"
#include "Constants.h"

namespace ir {

  Context::Context() {
    for (unsigned i = 0; i < static_cast<unsigned>(Type::TyIDCount); i++) {
      Type::TypeID tid = static_cast<Type::TypeID>(i);
      Type* t = new Type(*this, tid);
      _type_map[i] = t;
    }
  }

  Context::~Context() {
    for (auto p : _type_map)
      delete p.second;

    for (auto p : _integers)
      delete p.second;
  }

  Value* Context::GetInt(int v) {
    auto it = _integers.find(v);
    if (it != _integers.end()) {
      return it->second;
    } else {
      ConstantInt* c = new ConstantInt(*this, v);
      _integers[v] = c;
      return c;
    }
  }

} // end namespace ir