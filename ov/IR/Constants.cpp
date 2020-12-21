#include "Constants.h"

namespace ir {

ConstantInt::ConstantInt(Context& context, int v)
  : _val(v), Constant("int") {

  std::stringstream ostr;
  ostr << v;
  SetID(ostr.str());
  
  const Type* t = context.GetType(static_cast<unsigned>(Type::IntegerTyID));
  this->SetType(t);
}

Value* ConstantInt::Get(Context& context, int v) {
  return context.GetInt(v);
}


} // end namespace ir