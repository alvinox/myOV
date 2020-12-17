#ifndef _DESIGN_H_
#define _DESIGN_H_

#include <string>

#include "Module.h"
#include "Context.h"
#include "SymbolTable.h"
#include "Process.h"
#include "Value.h"

namespace ir {

class Module;
class Process;


class Design final : public Value {
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
  const std::string& ID() const { return _design_id; }

  Context& context() const { return _context; }

  /// Look up the specified template parameter in the design symbol table. If it does not
  /// exist, return null.
  // Process* getTemplateParam(const std::string& id);

  /// Look up the specified register in the design symbol table. If it does not
  /// exist, return null.
  // Process* getRegister(const std::string& id);

  /// Look up the specified wire in the design symbol table. If it does not
  /// exist, return null.
  // Process* getWire(const std::string& id);

  /// Look up the specified memory in the design symbol table. If it does not
  /// exist, return null.
  // Process* getMemory(const std::string& id);

  /// Look up the specified process in the design symbol table. If it does not
  /// exist, return null.
  Process* getProcess(const std::string& id);

  /// Look up the specified procedure in the design symbol table. If it does not
  /// exist, return null.
  // Procedure* getProcedure(const std::string& id);
  
  /// Print the design to an output stream.
  virtual void print(std::ostream& os) override;

  
 private:
  Module* _parent_module; ///< parent module for the design

  std::string _design_id; ///< Human readable identifier for the design
  Context& _context;      ///< The Context from which types and
                          ///< constants are allocated.
  SymbolTable _symtab;   ///< Symbol table
  // SymbolTable<Value>     _template_params;  ///< Symbol table of template parameters defined by keyword 'tparm'
  // SymbolTable<Value>     _registers;        ///< Symbol table of registers           defined by keyword 'reg'
  // SymbolTable<Value>     _wires;            ///< Symbol table of wires               defined by keyword 'wire'
  // SymbolTable<Value>     _memories;         ///< Symbol table of memories            defined by keyword 'mem'
  // SymbolTable<Value>     _processes;        ///< Symbol table of processes           defined by keyword 'def'
  // SymbolTable<Procedure> _procedures;       ///< Symbol table of procedures          defined by keyword 'proc'
};

} // end namespace ir

#endif // _DESIGN_H_