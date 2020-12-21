#include "Instruction.h"
#include "Design.h"
#include "Procedure.h"
#include "Logic.h"

namespace ir {

const std::string& Instruction::IDtoString(InstID tid) {
  assert(tid < InstIDCount);
  return NameMap[tid];
}

std::map<Instruction::InstID, std::string> Instruction::NameMap = {
    {DesignInstID,         "Design"},
    {InstantiateInstID,    "Instant"},
    {ProcessInstID,        "Process"},
    {ProcedureInstID,      "Proc"},
    {CallInstID,           "Call"},
    {RegisterInstID,       "Reg"},
    {WireInstID,           "Wire"},
    
    {SetValue8InstID,      "SetValue8"},
    {GetValue8InstID,      "GetValue8"},
    {SetValue16InstID,     "SetValue16"},
    {GetValue16InstID,     "GetValue16"},
};

void Instruction::Print(std::ostream& os, unsigned lv) const {
  std::string indent = Indent(lv);
  const std::string& ins = IDtoString(tid);

  switch (tid)
  {
    case DesignInstID: {
      Design* d = dynamic_cast<Design*>(operands[0]);
      os << indent << d->GetID() << "(" << ins << ")" << std::endl;
      d->PrintInstruction(os, lv);
      break;
    }

    case ProcedureInstID: {
      Procedure* p = dynamic_cast<Procedure*>(operands[0]);
      os << indent << p->GetID() << "(" << ins << ")" << std::endl;
      p->PrintInstruction(os, lv);
      break;
    }

    case RegisterInstID: {
      Register* r = dynamic_cast<Register*>(operands[0]);
      os << indent << r->GetID() << "(" << ins << r->RangeStr() << ")";
      break;
    }

    case WireInstID: {
      Wire* w = dynamic_cast<Wire*>(operands[0]);
      os << indent << w->GetID() << "(" << ins << w->RangeStr() << ")";
      break;
    }

    case SetValue8InstID: {
      Logic* lhs = dynamic_cast<Logic*>(operands[0]);
      Value* rhs = operands[1];
      os << indent << ins << " " << lhs->GetID() << " " << rhs->GetID();
    }

  default:
    break;
  }
}

} // end namespace ir