#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>
#include <sstream>

#include "Value.h"
#include "Scope.h"

namespace ir {

class Expr : public Value {
 public:
  Expr(const std::string& id) : Value(id, nullptr) { }
  virtual ~Expr() { };

  virtual std::string GetOperator() const = 0;
  virtual std::string GetExpr() const = 0;

 private:
};

class UnaryExpr final : public Expr {

};

class BinaryExpr final : public Expr {
 public:
  enum BinaryID {
    LogicAndOpID,   // logic and: &&
    BitAndOpID,     // bitwise and: &

    BinaryIDCount,
  };

  static BinaryExpr* Create(BinaryID tid, Value* lhs, Value* rhs, Scope* s) {
    return new BinaryExpr(tid, lhs, rhs, s);
  }

 public:
  BinaryExpr(BinaryID tid, Value* lhs, Value* rhs, Scope* s);
  virtual ~BinaryExpr();

 public:
  virtual std::string GetOperator() const override;
  virtual std::string GetExpr() const override;

 private:
  BinaryID _tid;
  Value*   _lhs;    ///< left  hand side
  Value*   _rhs;    ///< right hand side
  Scope*   _parent; ///< parent scope
};

class TernaryExpr final : public Expr {
 public:
  enum TernaryID {
    SelectOpID,   // select: :?

    TernaryIDCount,
  };

  static TernaryExpr* Create(TernaryID tid, Value* expr1, Value* expr2, Value* expr3, Scope* s) {
    return new TernaryExpr(tid, expr1, expr2, expr3, s);
  }

 public:
  TernaryExpr(TernaryID tid, Value* expr1, Value* expr2, Value* expr3, Scope* s);
  virtual ~TernaryExpr();

 public:
  virtual std::string GetOperator() const override;
  virtual std::string GetExpr() const override;

 private:
  TernaryID _tid;
  Value*    _expr1;
  Value*    _expr2;
  Value*    _expr3;
  Scope*    _parent;
};

} // end namespace ir

#endif // _EXPRESSION_H_