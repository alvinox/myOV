#include "VisitorSimC.h"
#include "Module.h"

namespace ir {

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
  ostr << indent << "#include \"sim_library.h\"" << std::endl;

  for (Design* d : module->collection.designs) {
    d->accept(this);
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
  ostr << indent << "void " << s->GetID() << "_" << proc->GetID();
  ostr << "(" << proto << ") {" << std::endl;

  InstructionShiftin(proc->collection.reg_getvalues);
  InstructionShiftin(proc->collection.statements);
  InstructionShiftin(proc->collection.reg_setvalues);

  ostr << indent << "}" << std::endl;
}

void VisitorSimC::visit(Register*  reg   ) {
  std::string indent = Indent(lv);
  std::string vtype = reg->GetVariableType();
  ostr << indent << vtype << " " << reg->GetID() << ";";
  ostr << "  // reg bits " << reg->GetBits();
  ostr << std::endl;
}

void VisitorSimC::visit(Wire*      wire  ) {
  std::string indent = Indent(lv);
  std::string vtype = wire->GetVariableType();
  ostr << indent << vtype << " " << wire->GetID() << ";";
  ostr << "  // wire bits " << wire->GetBits();
  ostr << std::endl;
}

} // end namespace ir