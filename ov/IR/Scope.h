#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "Util.h"
#include "Value.h"
#include "SymbolTable.h"
#include "Instruction.h"

namespace ir {

class Scope : public Value {
 public:
  Scope(const std::string& id, Scope* p)
    : _parent(p), Value(id) {}

  virtual ~Scope() {
    for (Value* v : _locals) {
      delete v;
    }

    for (Instruction* inst : _instructions) {
      delete inst;
    }
  }

 public:
  virtual Context& GetContext() const = 0;

  SymbolTable& GetSymbolTable() { return _symtab; }

  Scope* GetParent() const { return _parent; }

  Symbol& Define (Value* v);
  Symbol& Resolve(const std::string& name, bool& ok);
  Value*  ResolveValue(const std::string& name, bool& ok);
  
  void AppendLocal(Value* v) { _locals.push_back(v); }

  Instruction* AppendInstruction(Instruction* inst) {
    _instructions.push_back(inst); 
    return inst;
  }
  void PrintInstruction(std::ostream& os, unsigned lv = 0) const;

 private:
  SymbolTable _symtab;
  Scope*      _parent; ///< parent scope
  std::vector<Value*> _locals; ///< local values

  std::vector<Instruction*> _instructions;
};

} // end namespace ir

#endif // _SCOPE_H_