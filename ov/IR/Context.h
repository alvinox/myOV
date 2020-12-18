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
    // try {
    //   Type* t = _type_map[tid];
    //   return t;
    // } catch {

    // }
  } 

 private:
  std::vector<Value*> _constants;
  std::map<unsigned, Type*> _type_map;
};

} // end namespace ir

#endif // _CONTEXT_H_