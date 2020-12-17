#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_

#include <assert.h>
#include <string>

#include "Type.h"
#include "Process.h"

namespace ir {

class Process;

class Argument {
 public:
  explicit Argument(Type* ty, const std::string& name, Process* p = nullptr, unsigned arg_no = 0);

 public:
  
  Process* getParent() const { return _parent_process; }
  void     setParent(Process* p) { _parent_process = p; }

  /// For example in "void foo(int a, float b)" a is 0 and b is 1.
  unsigned getArgNo() const {
    assert(_parent_process && "can't get number of unparented arg");
    return _arg_no;
  }

 private:
  Process* _parent_process;
  unsigned _arg_no; ///< offset of the formal argument
};

} // end namespace ir

#endif // _ARGUMENT_H_