#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <string>
#include <map>
#include <assert.h>

#include "Util.h"
#include "Value.h"

namespace ir {

class Instruction {


 public:
  enum InstID {
    DesignInstID,
    InstantiateInstID,
    ProcessInstID,
    CallInstID,
    ProcedureInstID,
    RegisterInstID,
    WireInstID,
    
    SetValue8InstID,
    GetValue8InstID,
    SetValue16InstID,
    GetValue16InstID,

    InstIDCount,
  };

 public:
  static const std::string& IDtoString(InstID tid);
  static std::map<InstID, std::string> NameMap;

 public:
  explicit Instruction(InstID tid, const std::vector<Value*>& ops)
   : tid(tid) { 

   }
 public:
  unsigned OperandWidths() const { return static_cast<unsigned>(operands.size()); }
  void Print(std::ostream& os, unsigned lv = 0) const;
 public:
  InstID tid;
  std::vector<Value*> operands;
};

} // end namespace ir

#endif // _INSTRUCTION_H_