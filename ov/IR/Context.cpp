#include "Context.h"

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
  }

} // end namespace ir