#include "Visitor.h"

namespace ir {

//-------------------------- Visitor --------------------//

std::string Visitor::GetPassName(VisitorID tid) {
  switch (tid)
  {
    case SimulationC:      return "simc";
    case SimulationLLVMIR: return "simllvm";
  
    default: assert(0);
  }
}

} // end namespace ir