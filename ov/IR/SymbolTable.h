#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <string>
#include <map>
#include <vector>

#include "Value.h"

namespace ir {

class SymbolTable;

class Symbol {
 friend class SymbolTable;
 public:
  // enum SymbolScope {
  //   ModuleScope,
  //   DesignScope,
  //   LocalScope,
  // };

  std::string getName() const { return _name; }
  Value* getValue() const { return _value; }

 private:
  Symbol(const std::string& name, unsigned index, Value* value)
    : _name(name), _index(index), _value(value) { }

 private:
  unsigned    _index;
  std::string _name;
  // SymbolScope _scope;
  Value*      _value;
};

class SymbolTable {
 private:
  typedef std::vector<Symbol> SymbolList;

 public:
  static Symbol nil;

  typedef SymbolList::const_iterator const_iterator;
  const_iterator begin() { return _v.cbegin(); }
  const_iterator end()   { return _v.cend(); }

 public:
  void clear();

  Symbol& cbegin() const;
  Symbol& cend()   const;

  Symbol& Define (const std::string& name, Value* value);
  Symbol& Resolve(const std::string& name, bool& ok);

 private:
  std::map<std::string, unsigned> _map;
  SymbolList _v;
};


} // end namespace ir

#endif // _SYMBOL_TABLE_H_
