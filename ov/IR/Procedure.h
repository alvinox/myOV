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
};

} // end namespace ir

#endif // _PROCEDURE_H_