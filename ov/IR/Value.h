#ifndef _VALUE_H_
#define _VALUE_H_

#include "Type.h"

namespace ir {

class Value {
 public:

  const Type* getType() const { return _type; }
  void  setType(const Type* t) { _type = t; }

  virtual void print(std::ostream& os) {}

 private:
  const Type* _type;
};

} // end namespace ir

#endif // _VALUE_H_
