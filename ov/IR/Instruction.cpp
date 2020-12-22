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

void Instruction::PrintSimulationC(std::ostream& os, unsigned lv) const {
  std::map<InstID, std::string> FUNC = {
    {SetValue8InstID , "setvalue8"    },
    {SetValue16InstID, "setvalue16"   },
    {GetValue8InstID , "getvalue8"    },
    {GetValue16InstID, "getvalue16"   },
  };

  auto GetPool = [&](InstID tid, Value* v) -> std::string {
    switch (tid) {
      case SetValue8InstID:
      case SetValue16InstID: {
        if (v->GetType()->IsRegisterTy()) {
          return "d";
        } else if (v->GetType()->IsWireTy()) {
          return "wire";
        }
        break;
      }

      case GetValue8InstID:
      case GetValue16InstID: {
        if (v->GetType()->IsRegisterTy()) {
          return "q";
        } else if (v->GetType()->IsWireTy()) {
          return "wire";
        }
        break;
      }

      default: assert(0); break;
    }
  };

  std::string indent = Indent(lv);

  switch (tid) {
    case SetValue8InstID:
    case SetValue16InstID: {
      Value* lhs = operands[0];
      Value* rhs = operands[1];
      std::string func = FUNC[tid];
      std::string pool = GetPool(tid, lhs);
      os << indent << func << "(" << pool << ", &obj->" << lhs->GetID();
      os << ", " << rhs->GetID() << ");";
      break;
    }

    case GetValue8InstID:
    case GetValue16InstID: {
      Value* lv = operands[0];
      assert(lv->GetType()->IsLogicTy());
      Logic* lhs = static_cast<Logic*>(lv);

      std::string ctype = lhs->GetCType();
      std::string func  = FUNC[tid];
      std::string pool  = GetPool(tid, lhs);

      os << indent << ctype << " " << lhs->GetID() << " = ";
      os << func << "(" << pool << ", &obj->" << lhs->GetID() << ");";
      break;
    }
    case AssignInstID: {
      Value* lv = operands[0];
      assert(lv->GetType()->IsLogicTy());
      Logic* lhs = static_cast<Logic*>(lv);
      Value* rhs = operands[1];

      std::string ctype = lhs->GetCType();
      std::string rv_str = rhs->GetID();
      
      if (rhs->GetType()->IsExpressionTy()) {
        rv_str = dynamic_cast<Expr*>(rhs)->GetExpr();
      }
      os << indent << ctype << " " << lhs->GetID() << " = " << rv_str << ";";
      break;
    }
    default: assert(0 && "unsupported instruction"); break;
  }
}

} // end namespace ir