#include "IRBuilder.h"

namespace ir {

Instruction* IRBuilder::CreateDesign(Design* design) {
  return _insert(new Instruction(Instruction::DesignInstID, {design}));
}

Instruction* IRBuilder::CreateProcedure  (Procedure* proc) {
  return _insert(new Instruction(Instruction::ProcedureInstID, {proc}));
}

Instruction* IRBuilder::CreateRegister(Register* reg) {
  return _insert(new Instruction(Instruction::RegisterInstID, {reg}));
}

Instruction* IRBuilder::CreateWire    (Wire* wire) {
  return _insert(new Instruction(Instruction::WireInstID, {wire}));
}

Instruction* IRBuilder::CreateSetValue(Logic* l, Value* v) {
  Instruction* inst = NULL;

  unsigned bits = l->GetBits();
  if (bits <= 8) {
    inst = new Instruction(Instruction::SetValue8InstID, {l, v});
  } else if (8 < bits && bits <= 16) {
    inst = new Instruction(Instruction::SetValue16InstID, {l, v});
  }

  return _insert(inst);
}

Instruction* IRBuilder::CreateGetValue   (Logic* l) {
  Instruction* inst = NULL;

  unsigned bits = l->GetBits();
  if (bits <= 8) {
    inst = new Instruction(Instruction::GetValue8InstID, {l});
  } else if (8 < bits && bits <= 16) {
    inst = new Instruction(Instruction::GetValue16InstID, {l});
  }

  return _insert(inst);
}

Instruction* IRBuilder::CreateAssign     (Logic* l, Value* v) {
  return _insert(new Instruction(Instruction::AssignInstID, {l, v}));
}

} // end namespace ir