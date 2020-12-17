#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <string>

#include "Value.h"
#include "Design.h"

namespace ir {

class Design;

class Logic : public Value {
 public:
 protected:
  Logic(const std::string& id, Value* p, unsigned hi, unsigned lo)
    : _id(id), _parent(p), _hi(hi), _lo(lo) {
      assert(hi >= lo && "higher bit is less than lower bit");
    }

 public:

 private:
  std::string _id;
  Value* _parent; ///< parent design/process/procedure for the logic

  unsigned _hi;
  unsigned _lo;
};

class Register final : public Logic {
 public:
  static Register* Create(const std::string& id, Design* d, unsigned hi = 0, unsigned lo = 0) {
    return new Register(id, d, hi, lo);
  }
 public:
  Register(const std::string& id, Design* d, unsigned hi = 0, unsigned lo = 0);
 private:
};

class Wire final : public Logic {
 public:
  static Wire* Create(const std::string& id, Design* d, unsigned hi = 0, unsigned lo = 0) {
    return new Wire(id, d, hi, lo);
  }
 public:
  Wire(const std::string& id, Design* d, unsigned hi = 0, unsigned lo = 0);
 private:
};

} // end namespace ir

#endif // _LOGIC_H_