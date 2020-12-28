#ifndef _VISITOR_SIM_C_H_
#define _VISITOR_SIM_C_H_

#include "Visitor.h"

namespace ir {

class VisitorSimC final : public Visitor {
 public:
  static void Pass(Module* module);

 public:
  VisitorSimC()
    : Visitor(SimulationC), lv(0) { }

 public:
  virtual void visit(Module*    module) override;
  virtual void visit(Design*    design) override;
  virtual void visit(Procedure* proc  ) override;
  virtual void visit(Register*  reg   ) override;
  virtual void visit(Wire*      wire  ) override;

  void IncrIndent() { lv++; }
  void DecrIndent() { lv--; }

 public:
  unsigned lv;
  std::stringstream ostr;

};

} // end namespace ir

#endif // _VISITOR_SIM_C_H_