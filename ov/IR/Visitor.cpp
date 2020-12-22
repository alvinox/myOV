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

//-------------------------- VisitorSimC --------------------//

void VisitorSimC::Pass(Module* module) {
  VisitorSimC* v = new VisitorSimC();
  module->accept(v);

  std::cout << v->ostr.str();
  delete v;
}

void VisitorSimC::visit(Module* module) {
  module->Collect();

  std::string indent = Indent(lv);
  ostr << indent << module->GetID() << std::endl;

  for (Design* d : module->collection.designs) {
    IncrIndent();
    d->accept(this);
    DecrIndent();
  }
}

void VisitorSimC::visit(Design* design) {
  design->Collect();

  std::string indent = Indent(lv);
  ostr << indent << "struct " << design->GetID() << " {" << std::endl;

  IncrIndent();
  for (Register* r : design->collection.regs) {
    r->accept(this);
  }

  for (Wire* w : design->collection.wires) {
    w->accept(this);
  }
  ostr << indent << "};" << std::endl;
  DecrIndent();

  for (Procedure* p : design->collection.procs) {
    p->accept(this);
  }

}

void VisitorSimC::visit(Register*  reg   ) {
  std::string indent = Indent(lv);
  ostr << indent << "Variable " << reg->GetID() << ";";
  ostr << "  // reg bits " << reg->GetBits();
  ostr << std::endl;
}

void VisitorSimC::visit(Wire*      wire  ) {
  std::string indent = Indent(lv);
  ostr << indent << "Variable " << wire->GetID() << ";";
  ostr << "  // wire bits " << wire->GetBits();
  ostr << std::endl;
}

void VisitorSimC::visit(Procedure* proc  ) {
  auto InstructionShiftin = [&](const std::vector<Instruction*> instructions) {
    for (Instruction* inst : instructions) {
      inst->PrintSimulationC(ostr, lv+1);
      ostr << std::endl;
    }
  };

  proc->Collect();

  std::string indent = Indent(lv);
  Scope* s = proc->GetParent();
  std::string proto = Procedure::GetSimProtoType(s->GetID());
  ostr << indent << s->GetID() << "_" << proc->GetID() << "(" << proto << ") {" << std::endl;

  InstructionShiftin(proc->collection.reg_getvalues);
  InstructionShiftin(proc->collection.statements);
  InstructionShiftin(proc->collection.reg_setvalues);

  ostr << indent << "}" << std::endl;
}

} // end namespace ir