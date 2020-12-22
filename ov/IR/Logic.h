#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <string>
#include <sstream>
#include <assert.h>

#include "Value.h"
#include "Design.h"

namespace ir {

class Design;

class Logic : public Value {
 public:
 protected:
  Logic(const std::string& id, Scope* p, unsigned hi, unsigned lo)
    : _parent_scope(p), _hi(hi), _lo(lo), Value(id) {
      assert(hi >= lo && "higher bit is less than lower bit");
    }

 public:
   virtual Context& GetContext() const { return _parent_scope->GetContext(); };

   unsigned GetBits() const { return _hi - _lo + 1; }

   std::string GetCType() const; ///< get type of C when generate Simulation code

   std::string RangeStr() const;

 private:
  std::string _id;
  Scope* _parent_scope; ///< parent design/process/procedure for the logic

  unsigned _hi;
  unsigned _lo;
};

class Register final : public Logic {
 public:
  static Register* Create(const std::string& id, Scope* s, unsigned hi = 0, unsigned lo = 0) {
    return new Register(id, s, hi, lo);
  }
 public:
  Register(const std::string& id, Scope* s, unsigned hi = 0, unsigned lo = 0);
 
 public:
  virtual void accept(Visitor* visitor) override;
 private:
};

class Wire final : public Logic {
 public:
  static Wire* Create(const std::string& id, Scope* s, unsigned hi = 0, unsigned lo = 0) {
    return new Wire(id, s, hi, lo);
  }
 public:
  Wire(const std::string& id, Scope* s, unsigned hi = 0, unsigned lo = 0);

 public:
  virtual void accept(Visitor* visitor) override;

 private:
};

} // end namespace ir

#endif // _LOGIC_H_