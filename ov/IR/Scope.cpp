#include "Scope.h"
#include "Design.h"

namespace ir {

//------------------------------------- Scope::Collection ---------------------------------//

void Scope::Collection::Clear() {
  designs.clear();
  regs.clear();
  wires.clear();
  procs.clear();
  reg_getvalues.clear();
  reg_setvalues.clear();
}

void Scope::Collection::Collect(const std::vector<Instruction*> ins) {
  Clear();
  for (Instruction* inst : ins) {
    const std::vector<Value*>& operands = inst->operands;
    switch (inst->tid) {
      case Instruction::DesignInstID: {
        Design* d = dynamic_cast<Design*>(operands[0]);
        designs.push_back(d);
        break;
      }
      case Instruction::ProcedureInstID: {
        Procedure* p = dynamic_cast<Procedure*>(operands[0]);
        procs.push_back(p);
        break;
      }
      case Instruction::RegisterInstID: {
        Register* r = dynamic_cast<Register*>(operands[0]);
        regs.push_back(r);
        break;
      }
      case Instruction::WireInstID: {
        Wire* w = dynamic_cast<Wire*>(operands[0]);
        wires.push_back(w);
        break;
      }
      case Instruction::SetValue8InstID:
      case Instruction::SetValue16InstID: {
        Value* lhs = operands[0];
        if (lhs->GetType()->IsRegisterTy()) {
          reg_setvalues.push_back(inst);
        } else {
          statements.push_back(inst);
        }
        break;
      }
      case Instruction::GetValue8InstID:
      case Instruction::GetValue16InstID: {
        Value* lhs = operands[0];
        if (lhs->GetType()->IsRegisterTy()) {
          reg_getvalues.push_back(inst);
        } else {
          statements.push_back(inst);
        }
        break;
      }
      default: statements.push_back(inst); break;
    }
  }
}

//------------------------------------- Scope ---------------------------------//

Symbol& Scope::Define(Value* v) {
  Symbol& sym = GetSymbolTable().Define(v);

  AppendLocal(v);

  return sym;
}

Symbol& Scope::Resolve(const std::string& name, bool& ok) {
  Symbol& sym = this->GetSymbolTable().Resolve(name, ok);
  if (!ok) {
    Scope* scope = GetParent();
    sym = scope->Resolve(name, ok);
  }

  return sym;
}

Value*  Scope::ResolveValue(const std::string& name, bool& ok) {
  Symbol& sym = Resolve(name, ok);
  Value* v = sym.GetValue();

  return v;
}

void Scope::PrintInstruction(std::ostream& os, unsigned lv) const {
  std::string indent = Indent(lv);

  // Module is the root node
  if (this->GetType()->IsModuleTy()) {
    os << indent << GetID() << std::endl;
  }

  for (Instruction* inst : _instructions) {
    inst->PrintInstruction(os, lv + 1);
  }
}

} // end namespace ir