#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <string>
#include <map>
#include <vector>

#include "Value.h"

namespace ir {

class Value;
class SymbolTable;

class Symbol {
 friend class SymbolTable;
 public:

  Value* GetValue() const { return _value; }

 private:
  Symbol(unsigned index, Value* value)
    : _index(index), _value(value) { }

 private:
  unsigned    _index;
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
  Symbol& cbegin() const;
  Symbol& cend()   const;
  
  Symbol& Define (Value* value);
  Symbol& Resolve(const std::string& name, bool& ok);

 private:
  std::map<std::string, unsigned> _map;
  SymbolList _v;
};

} // end namespace ir

#endif // _SYMBOL_TABLE_H_
