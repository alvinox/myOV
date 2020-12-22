#include "Instruction.h"
#include "Design.h"
#include "Procedure.h"
#include "Logic.h"
#include "Expression.h"

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

    {AssignInstID,         "Assign"},
};

void Instruction::PrintInstruction(std::ostream& os, unsigned lv) const {
  std::string indent = Indent(lv);
  const std::string& ins = IDtoString(tid);

  switch (tid) {
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
      os << std::endl;
      break;
    }

    case WireInstID: {
      Wire* w = dynamic_cast<Wire*>(operands[0]);
      os << indent << w->GetID() << "(" << ins << w->RangeStr() << ")";
      os << std::endl;
      break;
    }

    case SetValue8InstID:
    case SetValue16InstID: {
      Logic* lhs = dynamic_cast<Logic*>(operands[0]);
      Value* rhs = operands[1];
      os << indent << ins << " " << lhs->GetID() << " " << rhs->GetID();
      os << std::endl;
      break;
    }

    case GetValue8InstID:
    case GetValue16InstID: {
      Logic* lhs = dynamic_cast<Logic*>(operands[0]);
      os << indent << ins << " " << lhs->GetID();
      os << std::endl;
      break;
    }

    case AssignInstID: {
      Logic* lv = dynamic_cast<Logic*>(operands[0]);
      Value* rv = operands[1];
      std::string rv_str = rv->GetID();
      if (rv->GetType()->IsExpressionTy()) {
        rv_str = dynamic_cast<Expr*>(rv)->GetExpr();
      }
      os << indent << ins << " " << lv->GetID() << " = " << rv_str;
      os << std::endl;
      break;
    }

    default:
      break;
  }
}

void Instruction::PrintSimulation(std::ostream& os, unsigned lv) const {
  std::string indent = Indent(lv);
  const std::string& ins = IDtoString(tid);

  switch (tid) {
    case DesignInstID: {
      Design* d = dynamic_cast<Design*>(operands[0]);
      os << indent << "struct " << d->GetID() << " {" << std::endl;
      d->PrintSimulation(os, lv);
      os << indent << "};";
      os << std::endl;
      break;
    }

    case ProcedureInstID: {
      Procedure* p = dynamic_cast<Procedure*>(operands[0]);
      Scope* s = p->GetParent();
      std::string proto = Procedure::GetSimProtoType(s->GetID());
      os << indent << s->GetID() << "_" << p->GetID() << "(" << proto << ") {" << std::endl;
      p->PrintSimulation(os, lv);
      os << indent << "};";
      os << std::endl;
      break;
    }

    case RegisterInstID: {
      Register* r = dynamic_cast<Register*>(operands[0]);
      os << indent << "Variable " << r->GetID() << ";";
      os << "  // reg bits " << r->GetBits();
      os << std::endl;
      break;
    }

    case WireInstID: {
      Wire* w = dynamic_cast<Wire*>(operands[0]);
      os << indent << "Variable " << w->GetID() << ";";
      os << "  // wire bits " << w->GetBits();
      os << std::endl;
      break;
    }

  }
}

} // end namespace ir