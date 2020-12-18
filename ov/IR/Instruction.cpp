#include "Instruction.h"

namespace ir {

const std::string& Instruction::IDtoString(InstID tid) {
  assert(tid < InstIDCount);
  return NameMap[tid];
}

std::map<Instruction::InstID, std::string> Instruction::NameMap = {
    {DesignInstID, "Design"},
    // InstantiateInstID,
    // ProcessInstID,
    // CallInstID,
    // ProcedureInstID,
    // RegisterInstID,
    // WireInstID,
    
    // SetValue8InstID,
    // GetValue8InstID,
    // SetValue16InstID,
    // GetValue16InstID,
};

void Instruction::Print(std::ostream& os, unsigned lv) const {
  std::string indent = Indent(lv);
  const std::string& name = IDtoString(tid);
  os << indent << name << " ";
}

} // end namespace ir