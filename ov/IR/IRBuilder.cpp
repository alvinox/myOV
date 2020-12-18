#include "IRBuilder.h"

namespace ir {

Instruction* IRBuilder::CreateDesign(Design* design) {
  return _insert(new Instruction(Instruction::DesignInstID, {design}));
}

} // end namespace ir