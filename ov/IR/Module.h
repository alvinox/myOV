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
  explicit Module(const std::string& id, Context &c);

 public:

  /// Get the global data context.
  /// @returns Context - a container for global information
  virtual Context& GetContext() const override { return _context; }

  /// Look up the specified design in the module symbol table. If it does not
  /// exist, return null.
  Design* GetDesign(const std::string& id) const;

 private:
  Context& _context;      ///< The Context from which types and
                          ///< constants are allocated.
}; // end class Module

} // end namespace ir

#endif // _MODULE_H_