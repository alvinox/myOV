#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "Util.h"
#include "Value.h"
#include "SymbolTable.h"
#include "Instruction.h"

namespace ir {

class Design;
class Register;
class Wire;
class Procedure;

class Scope : public Value {
 public:
  class Collection {
   // this util class is used for dispatch instructions by Type 
   public:
    void Clear();
    void Collect(const std::vector<Instruction*> ins);
  
   public:
    std::vector<Design*>      designs;       // design    definition
    std::vector<Register*>    regs;          // register  definition
    std::vector<Wire*>        wires;         // wire      definition
    std::vector<Procedure*>   procs;         // procedure definition
    std::vector<Instruction*> reg_setvalues; // nonblocking assignments
    std::vector<Instruction*> reg_getvalues; // nonblocking assignments
    std::vector<Instruction*> statements;    // other statements
  };

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
  void Collect() { collection.Collect(_instructions); }

 public:
  Collection collection; ///< dispatch instructions

 private:
  SymbolTable _symtab;
  Scope*      _parent; ///< parent scope
  std::vector<Value*> _locals; ///< local values

  std::vector<Instruction*> _instructions;
};

} // end namespace ir

#endif // _SCOPE_H_