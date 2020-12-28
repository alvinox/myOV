#ifndef _VISITOR_H_
#define _VISITOR_H_

#include <assert.h>
#include <string>
#include <sstream>

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

} // end namespace ir

#endif // _VISITOR_H_