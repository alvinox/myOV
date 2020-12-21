#include <stdio.h>
#include <memory>

#include "llvm/ADT/APFloat.h"

#include "Context.h"
#include "Constants.h"
#include "Module.h"
#include "Logic.h"
#include "IRBuilder.h"

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
  builder.CreateSetValue(r0_logic, ConstantInt::get(context, 0));

  Symbol& r1 = proc->Resolve("r1", ok);
  assert(ok && "undefined identifier");
  Logic* r1_logic = static_cast<Logic*>(r1.GetValue());
  builder.CreateSetValue(r1_logic, ConstantInt::get(context, 0));

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

  return design;
}

Value* walk_module() {
  Module* module = new Module("test_ip.sv", context);
  builder.SetInsertPoint(module);

  Value* design = walk_design(module);

  Value* proc = walk_procedure_reset(design);

  // Design* design = Design::Create("test_ip", module);

  // Register* r0   = Register::Create("r0", design, 7, 0);
  // Register* r1   = Register::Create("r1", design);
  // Wire*     w0   = Wire::Create("w0", design, 13, 0);
  // Wire*     w1   = Wire::Create("w1", design, 4);

  ////////////// Procedure reset ////////////////
  // bool ok = false;
  // Procedure* proc_reset = Procedure::Create("reset", design);
  // Symbol& r0 = proc_reset->Resolve("r0", ok);
  // assert(ok && "undefined identifier");
  // proc_reset->Emit(Code::SetValue8, r0->GetValue(), ConstantInt(0));

  // Symbol& r1 = proc_reset->Resolve("r1", ok);
  // assert(ok && "undefined identifier");
  // proc_reset->SetReg(r1, ConstantInt(0));
/*
  ////////////// Procedure main ////////////////
  Procedure* proc_main = Procedure::Create("main", design);
  Symbol& w0 = proc_main->Resolve("w0", ok);
  proc_main->Emit(Code::GetValue16, w0->GetValue());
  Wire* w0_auto7to0 = Wire::Create("w0_auto7to0", proc_main, 7, 0);
  proc_main->Emit(Code::Mask, w0->GetValue(), w0_auto7to0);
  // Symbol& r0 = proc_reset->Resolve("r0", ok);
  proc_main->Emit(Code::SetValue8, r0->GetValue(), w0_auto7to0);

  Symbol& w0 = proc_main->Resolve("w1", ok);
  proc_main->Emit(Code::GetValue8, w1->GetValue());
  Wire* w1_auto0to0 = Wire::Create("w1_auto0to0", proc_main, 0, 0);
  proc_main->Emit(Code::Mask, w1->GetValue(), w1_auto0to0);
  Wire* w1_auto1to1 = Wire::Create("w1_auto1to1", proc_main, 1, 1);
  proc_main->Emit(Code::Mask, w1->GetValue(), w1_auto0to0);
  Wire* w1_auto2to2 = Wire::Create("w1_auto2to2", proc_main, 2, 2);
  proc_main->Emit(Code::Mask, w1->GetValue(), w1_auto2to2);

  proc_main->Emit(Code::Nop);
  // Symbol& r1 = proc_reset->Resolve("r1", ok);
  Register* r1_value = dynamic_cast<Register*>(r1->GetValue());
  Wire* r1_ssa0 = Wire::Create("r1_ssa0", proc_main);
  r1_ssa0->CopyBits(r1_value);
  proc_main->Emit(Code::SetLocal, w1_auto1to1);
  proc_main->Emit(Code::Assign, r1_ssa0);
  Wire* r1_ssa1 = Wire::Create("r1_ssa1", proc_main);
  r1_ssa1->CopyBits(r1_value);
  proc_main->Emit(Code::SetLocal, w1_auto2to2);
  proc_main->Emit(Code::Assign, r1_ssa1);

  proc_main->Emit(Code::SetLocal, w1_auto0to0);
  proc_main->Emit(Code::SetLocal, r1_ssa0);
  proc_main->Emit(Code::SetLocal, r1_ssa1);
  proc_main->Emit(Code::TernaryOp);
  Wire* r1_phi = Wire::Create("r1_phi", proc_main);
  proc_main->Emit(Code::Assign, r1_phi);

  proc_main->Emit(Code::SetValue8, r1->GetValue(), r1_phi);
*/
  return module;
}

} // end namespace ir

int main() {
  ir::Value* root_node = ir::walk_module();
  ir::Module* module = dynamic_cast<ir::Module*>(root_node);
  module->PrintInstruction(std::cout);

  // IRGen::genLLVMIR(m);


  return 0;
}
