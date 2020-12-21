#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <vector>
#include <map>

#include "Type.h"
#include "Value.h"

namespace ir {

class Type;
class Value;

class Context {
 public:
  explicit Context();
  ~Context();
 
 public:
  const Type* GetType(unsigned tid) { 
      Type* t = _type_map[tid];
      return t;
  } 

  ///< if ConstantInt already exists in _integers, return _integers[v]
  ///< else create a new ConstantInt(v), add it to the map and return it
  Value* GetInt(int v);

 private:
  std::map<unsigned, Type*> _type_map;

  ///< constants map
  std::map<int, Value*> _integers;
};

} // end namespace ir

#endif // _CONTEXT_H_