#include <stdio.h>
#include <memory>

#include "llvm/ADT/APFloat.h"

#include "Context.h"
#include "Module.h"
#include "Logic.h"

namespace ir {

std::unique_ptr<Module> create_module() {
  Context context;
  std::unique_ptr<Module> module = std::make_unique<Module>("test_ip.sv", context);
  Design* design = Design::Create("test_ip", module.get());

  Register* r0   = Register::Create("r0", design, 7, 0);
  Register* r1   = Register::Create("r1", design);
  Wire*     w0   = Wire::Create("w0", design, 13, 0);
  Wire*     w1   = Wire::Create("w1", design, 4);

  return module;
}

} // end namespace ir

int main() {
  std::unique_ptr<ir::Module> module = ir::create_module();
  module->print(std::cout);

  // IRGen::genLLVMIR(m);


  return 0;
}
