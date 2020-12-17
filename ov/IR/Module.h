#ifndef _MODULE_H_
#define _MODULE_H_

#include <string>
#include <iostream>
#include <stack> 

#include "Context.h"
#include "Design.h"
#include "SymbolTable.h"

namespace ir {

class Design;

class Module {
 public:
  // constructor/destructor
  explicit Module(const std::string& id, Context &c)
    : _module_id(id), _context(c) { }

  ~Module() {
    _symtab.clear();
  }

 public:

  /// Get the global data context.
  /// @returns Context - a container for global information
  Context &getContext() const { return _context; }

  /// Define the specified design in the module symbol table.
  Symbol& Define(Design* design);

  /// Look up the specified design in the module symbol table. If it does not
  /// exist, return null.
  Design* getDesign(const std::string& id);
  
  /// Print the module to an output stream.
  void print(std::ostream& os);

 private:
  std::string _module_id; ///< Human readable identifier for the module
  Context& _context;      ///< The LLVMContext from which types and
                          ///< constants are allocated.
  SymbolTable _symtab;
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