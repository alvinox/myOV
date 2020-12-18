#ifndef _MODULE_H_
#define _MODULE_H_

#include <string>
#include <iostream>
#include <stack> 

#include "Context.h"
#include "Scope.h"
#include "Design.h"
#include "SymbolTable.h"

namespace ir {

class Design;

class Module final : public Scope {
 public:
  struct Records {
    std::vector<std::string> _designs; ///< record the designs
  };

 public:
  // constructor/destructor
  explicit Module(const std::string& id, Context &c);

 public:

  /// Get the global data context.
  /// @returns Context - a container for global information
  virtual Context& GetContext() const override { return _context; }


  /// Look up the specified design in the module symbol table. If it does not
  /// exist, return null.
  Design* GetDesign(const std::string& id) const;

  /// Print the module to an output stream.
  virtual void Print(std::ostream& os) const override;

 private:
  virtual void _record(Value* v) override;

 private:
  Context& _context;      ///< The Context from which types and
                          ///< constants are allocated.
  Records _records;
}; // end class Module


// class Procedure {
// };

// class TemplateParam final : public Value {
// };

// class Logic: public Value {
// };

// class Register : public Logic {
// };

// class Wire : public Logic {
// };

// class Memory : public Logic {
// };
} // end namespace ir

#endif // _MODULE_H_