#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <string>

#include "Value.h"
#include "Context.h"
#include "Scope.h"
#include "Design.h"

namespace ir {

class Design;

class Procedure final : public Scope {

 public:
  struct Records {
    std::vector<std::string> _registers;  ///< record the registers
    std::vector<std::string> _wires;      ///< record the wires
  };

 public:
  // static methods
  static Procedure* Create(const std::string& id, Design* m) {
    return new Procedure(id, m);
  }

 public:
  Procedure(const std::string& id, Design* m);

 public:
  virtual Context& GetContext() const override;

  /// Print the design to an output stream.
  virtual void Print(std::ostream& os) const override;

 private:
  virtual void _record(Value* v) override;

 private:
  // Design* _parent_design; ///< parent design for the procedure
  Records _records;
};

} // end namespace ir

#endif // _PROCEDURE_H_