#include <stdio.h>
#include <memory>

#include "llvm/ADT/APFloat.h"

#include "Context.h"
#include "Module.h"
#include "Logic.h"

namespace ir {

Module* create_module() {
  Context context;
  Module* module = new Module("test_ip.sv", context);

  Design* design = Design::Create("test_ip", module);

  Register* r0   = Register::Create("r0", design, 7, 0);
  Register* r1   = Register::Create("r1", design);
  Wire*     w0   = Wire::Create("w0", design, 13, 0);
  Wire*     w1   = Wire::Create("w1", design, 4);

  ////////////// Procedure reset ////////////////
  bool ok = false;
  Procedure* proc_reset = Procedure::Create("reset", design);
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
  ir::Module* module = ir::create_module();
  module->Print(std::cout);

  // IRGen::genLLVMIR(m);


  return 0;
}
