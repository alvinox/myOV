#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <string>
#include <vector>

#include "Design.h"
#include "Type.h"
#include "Argument.h"

namespace ir {

class Design;

class ProcessType final : public Type {
 public:
  static ProcessType* get(Type* result, std::vector<Type*> params);
 public:
   ProcessType(Type* result, std::vector<Type*> params);
   ProcessType(const ProcessType &) = delete;
   ProcessType &operator=(const ProcessType &) = delete;

 public:
  /// Parameter type accessors.
  Type *getParamType(unsigned i) const { return _params[i]; }
  
  /// Return the number of fixed parameters this function type requires.
  unsigned getNumParams() const { return static_cast<unsigned>(_params.size()); }

  /// Methods for support type inquiry through isa, cast, and dyn_cast.
  static bool classof(const Type *t) {
    return t->getTypeID() == ProcessTyID;
  }

 private:
  Type* _return_ty;
  std::vector<Type*> _params;
};

class Process final : public Value {
 public:
  // static methods
  static Process* Create(ProcessType *pt, const std::string& id, Design* d) {
    return new Process(pt, id, d);
  }

  // static members

 public:
  // constructor/destructor
  Process(ProcessType *pt, const std::string& id, Design* d);

 private:
  Design* _parent_design; ///< parent design for the process

  std::string _process_id; ///< Human readable identifier for the process
  std::vector<Type*> _return_types;  ///< types of the return value
  std::vector<Argument> _arguments; ///< the formal arguments
};

} // end namespace ir

#endif // _PROCESS_H_