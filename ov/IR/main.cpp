#include <stdio.h>
#include <memory>

#include "Context.h"
#include "Constants.h"
#include "Module.h"
#include "Logic.h"
#include "IRBuilder.h"
#include "Expression.h"
#include "VisitorSimC.h"
#include "VisitorSimLLVM.h"

namespace ir {

Context   context;
IRBuilder builder;

Value* walk_procedure_reset(Value* node) {
  assert(node->GetType()->IsDesignTy());
  Design* design = dynamic_cast<Design*>(node);
  Context& context = design->GetContext();

  Procedure* proc = Procedure::Create("reset", design);
  builder.CreateProcedure(proc);
  builder.SetInsertPoint(proc);

  bool ok = false;
  Symbol& r0 = proc->Resolve("r0", ok);
  assert(ok && "undefined identifier");
  Logic* r0_logic = static_cast<Logic*>(r0.GetValue());
  builder.CreateSetValue(r0_logic, ConstantInt::Get(context, 0));

  Symbol& r1 = proc->Resolve("r1", ok);
  assert(ok && "undefined identifier");
  Logic* r1_logic = static_cast<Logic*>(r1.GetValue());
  builder.CreateSetValue(r1_logic, ConstantInt::Get(context, 0));

  builder.SetInsertPoint(design);
  return proc;
}

Value* walk_procedure_main(Value* node) {
  assert(node->GetType()->IsDesignTy());
  Design* design = dynamic_cast<Design*>(node);
  Context& context = design->GetContext();

  Procedure* proc = Procedure::Create("main", design);
  builder.CreateProcedure(proc);
  builder.SetInsertPoint(proc);

  bool ok = false;
  Symbol& w0 = proc->Resolve("w0", ok);
  Logic* w0_logic = static_cast<Logic*>(w0.GetValue());
  builder.CreateGetValue(w0_logic);

  Value* w0_auto7to0_mask = ConstantInt::Get(context, 0xFF);
  BinaryExpr* op0 = BinaryExpr::Create(BinaryExpr::BitAndOpID, w0_logic, w0_auto7to0_mask, proc);
  Wire* w0_auto7to0 = Wire::Create("w0_auto7to0", proc, 7, 0);
  builder.CreateAssign(w0_auto7to0, op0);

  Symbol& r0 = proc->Resolve("r0", ok);
  Logic* r0_logic = static_cast<Logic*>(r0.GetValue());
  builder.CreateSetValue(r0_logic, w0_auto7to0);

  Symbol& w1 = proc->Resolve("w1", ok);
  Logic* w1_logic = static_cast<Logic*>(w1.GetValue());
  builder.CreateGetValue(w1_logic);

  Value* w1_auto0to0_mask = ConstantInt::Get(context, 0x1);
  BinaryExpr* op1 = BinaryExpr::Create(BinaryExpr::BitAndOpID, w1_logic, w1_auto0to0_mask, proc);
  Wire* w1_auto0to0 = Wire::Create("w1_auto0to0", proc, 0, 0);
  builder.CreateAssign(w1_auto0to0, op1);
  Value* w1_auto1to1_mask = ConstantInt::Get(context, 0x2);
  BinaryExpr* op2 = BinaryExpr::Create(BinaryExpr::BitAndOpID, w1_logic, w1_auto1to1_mask, proc);
  Wire* w1_auto1to1 = Wire::Create("w1_auto1to1", proc, 1, 1);
  builder.CreateAssign(w1_auto1to1, op2);
  Value* w1_auto2to2_mask = ConstantInt::Get(context, 0x4);
  BinaryExpr* op3 = BinaryExpr::Create(BinaryExpr::BitAndOpID, w1_logic, w1_auto2to2_mask, proc);
  Wire* w1_auto2to2 = Wire::Create("w1_auto2to2", proc, 1, 1);
  builder.CreateAssign(w1_auto2to2, op3);

  Wire* r1_ssa0 = Wire::Create("r1_ssa0", proc, 0, 0);
  builder.CreateAssign(r1_ssa0, w1_auto0to0);
  Wire* r1_ssa1 = Wire::Create("r1_ssa1", proc, 0, 0);
  builder.CreateAssign(r1_ssa1, w1_auto1to1);

  TernaryExpr* select = TernaryExpr::Create(TernaryExpr::SelectOpID, w1_auto0to0, w1_auto1to1, w1_auto2to2, proc);
  Wire* r1_phi = Wire::Create("r1_phi", proc, 0, 0);
  builder.CreateAssign(r1_phi, select);

  Symbol& r1 = proc->Resolve("r1", ok);
  Logic* r1_logic = static_cast<Logic*>(r1.GetValue());
  builder.CreateSetValue(r1_logic, r1_phi);

  builder.SetInsertPoint(design);
  return proc;
}

Value* walk_procedure_pre_update(Value* node) {
  assert(node->GetType()->IsDesignTy());
  Design* design = dynamic_cast<Design*>(node);
  Context& context = design->GetContext();

  Procedure* proc = Procedure::Create("pre_update", design);
  builder.CreateProcedure(proc);
  builder.SetInsertPoint(proc);

  builder.SetInsertPoint(design);
  return proc;
}

Value* walk_design(Value* node) {
  assert(node->GetType()->IsModuleTy());
  Module* module = dynamic_cast<Module*>(node);

  Design* design = Design::Create("test_ip", module);
  builder.CreateDesign(design);
  builder.SetInsertPoint(design);

  Register* r0   = Register::Create("r0", design, 7, 0);
  builder.CreateRegister(r0);
  Register* r1   = Register::Create("r1", design);
  builder.CreateRegister(r1);
  Wire*     w0   = Wire::Create("w0", design, 13, 0);
  builder.CreateWire(w0);
  Wire*     w1   = Wire::Create("w1", design, 4);
  builder.CreateWire(w1);

  Value* proc = walk_procedure_reset(design);
         proc = walk_procedure_main(design);
         proc = walk_procedure_pre_update(design);

  builder.SetInsertPoint(module);
  return design;
}

Value* walk_module() {
  Module* module = new Module("test_ip.sv", context);
  builder.SetInsertPoint(module);

  Value* design = walk_design(module);

  return module;
}

} // end namespace ir

int main() {
  ir::Value* root_node = ir::walk_module();
  ir::Module* module = dynamic_cast<ir::Module*>(root_node);

  module->PrintInstruction(std::cout); // for debug

  ir::VisitorSimC::Pass(module);
  ir::VisitorSimLLVM::Pass(module);
  return 0;
}
