#ifndef _DESIGN_H_
#define _DESIGN_H_

#include <string>

#include "Value.h"
#include "Context.h"
#include "Scope.h"
#include "Logic.h"
#include "Module.h"
#include "Process.h"
#include "Procedure.h"
#include "SymbolTable.h"

namespace ir {

class Module;
class Process;
class Procedure;
class Register;
class Wire;

class Design final : public Scope {
 public:
  // static methods
  static Design* Create(const std::string& id, Module* m) {
    return new Design(id, m);
  }

  // static members

 public:
  // constructor/destructor
  Design(const std::string& id, Module* m);
  
  Design(const Design&) = delete;
  void operator=(const Design&) = delete;
  
 public:
  virtual Context& GetContext() const override;

  /// Look up the specified template parameter in the design symbol table. If it does not
  /// exist, return null.
  // Process* GetTemplateParam(const std::string& id);

  /// Look up the specified process in the design symbol table. If it does not
  /// exist, return null.
  // Process* GetProcess(const std::string& id);

  /// Look up the specified procedure in the design symbol table. If it does not
  /// exist, return null.
  Procedure* GetProcedure(const std::string& id) const;

  /// Look up the specified register in the design symbol table. If it does not
  /// exist, return null.
  Register* GetRegister(const std::string& id) const;

  /// Look up the specified wire in the design symbol table. If it does not
  /// exist, return null.
  Wire* GetWire(const std::string& id) const;

  /// Look up the specified memory in the design symbol table. If it does not
  /// exist, return null.
  // Memory* GetMemory(const std::string& id);

 private:
};

} // end namespace ir

#endif // _DESIGN_H_