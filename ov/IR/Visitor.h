#ifndef _VISITOR_H_
#define _VISITOR_H_

#include <string>
#include <sstream>

#include "Module.h"

namespace ir {

class Module;
class Design;
class Register;
class Wire;
class Procedure;

class Visitor {
 public:
  enum VisitorID {
    SimulationC = 0,   ///< generate C code for simulation
    SimulationLLVMIR,  ///< generate LLVMIR for simulation
  };

  static std::string GetPassName(VisitorID tid);

 public:
  Visitor(VisitorID tid)
    : _tid(tid) { }

 public:
  virtual void visit(Module*    module) = 0;
  virtual void visit(Design*    design) = 0;
  virtual void visit(Register*  reg   ) = 0;
  virtual void visit(Wire*      wire  ) = 0;
  virtual void visit(Procedure* proc  ) = 0;

 private:
  VisitorID _tid;
};

class VisitorSimC final : public Visitor {
 public:
  static void Pass(Module* module);

 public:
  VisitorSimC()
    : Visitor(SimulationC), lv(0) { }

 public:
  virtual void visit(Module*    module) override;
  virtual void visit(Design*    design) override;
  virtual void visit(Register*  reg   ) override;
  virtual void visit(Wire*      wire  ) override;
  virtual void visit(Procedure* proc  ) override;

  void IncrIndent() { lv++; }
  void DecrIndent() { lv--; }

 public:
  unsigned lv;
  std::stringstream ostr;

};

} // end namespace ir

#endif // _VISITOR_H_