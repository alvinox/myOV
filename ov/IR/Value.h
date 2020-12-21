#ifndef _VALUE_H_
#define _VALUE_H_

#include <string>

#include "Type.h"

namespace ir {

class Type;
class Scope;
class Module;

class Value {
 public:
  Value(const std::string& id, const Type* type = nullptr)
    : _id(id), _type(type) { }

 public:

  const std::string& GetID() const { return _id; }
  void SetID(const std::string& id) { _id = id; }

  const Type* GetType() const { return _type; }
  void  SetType(const Type* t) { _type = t; }

  virtual void Print(std::ostream& os) const { os << _id; }

 private:
  std::string _id; // Human readable identifier
  const Type* _type;
};

} // end namespace ir

#endif // _VALUE_H_
