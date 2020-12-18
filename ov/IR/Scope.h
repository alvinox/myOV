#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "Value.h"
#include "SymbolTable.h"

namespace ir {

class Scope : public Value {
 public:
  Scope(const std::string& id) 
    : Value(id) {}

  virtual ~Scope() {
    _symtab.Clear();
  }

  // Scope(const std::string& id, const Type* type) 
  //   : Value(id, type) {}
 public:
  virtual Context& GetContext() const = 0;

  Symbol& Define (Value* v);
  Symbol& Resolve(const std::string& name, bool& ok);
  Value*  ResolveValue(const std::string& name, bool& ok);
  

  SymbolTable& GetSymbolTable() { return _symtab; }

 private:
  virtual void _record(Value* v) = 0;

 private:
  SymbolTable _symtab;
};

} // end namespace ir

#endif // _SCOPE_H_