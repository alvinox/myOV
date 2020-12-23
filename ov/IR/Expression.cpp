#include "Expression.h"

namespace ir {

//------------------- BinaryExpr ----------------------//

BinaryExpr::BinaryExpr(BinaryID tid, Value* lhs, Value* rhs, Scope* s) 
  : Expr("binary"), _tid(tid), _lhs(lhs), _rhs(rhs), _parent(s) {

  Context& context = s->GetContext();
  const Type* t = context.GetType(static_cast<unsigned>(Type::BinaryExprTyID));
  this->SetType(t);

  std::string op = GetOperator();
  this->SetID(op);

  s->AppendLocal(this);
}

std::string BinaryExpr::GetOperator() const {
  switch (_tid)
  {
    case LogicAndOpID: return "&&";
    case BitAndOpID:   return "&";
  
    default:
      break;
  }
}

std::string BinaryExpr::GetExpr() const {
  std::stringstream ostr;

  if (_lhs->GetType()->IsExpressionTy()) {
    ostr << dynamic_cast<Expr*>(_lhs)->GetExpr();
  } else {
    ostr << _lhs->GetID();
  }

  ostr << " " << GetID() << " ";

  if (_rhs->GetType()->IsExpressionTy()) {
    ostr << dynamic_cast<Expr*>(_rhs)->GetExpr();
  } else {
    ostr << _rhs->GetID();
  }

  return ostr.str();
}

//------------------- TernaryExpr ----------------------//

TernaryExpr::TernaryExpr(TernaryID tid, Value* expr1, Value* expr2, Value* expr3, Scope* s) 
  : Expr("ternary"), _tid(tid), _expr1(expr1), _expr2(expr2), _expr3(expr3), _parent(s) {

  Context& context = s->GetContext();
  const Type* t = context.GetType(static_cast<unsigned>(Type::TernaryExprTyID));
  this->SetType(t);

  std::string op = GetOperator();
  this->SetID(op);

  s->AppendLocal(this);
}

std::string TernaryExpr::GetOperator() const {
  switch (_tid)
  {
    case SelectOpID: return ":?";
  
    default:
      break;
  }
}

std::string TernaryExpr::GetExpr() const {
  std::stringstream ostr;

  if (_expr1->GetType()->IsExpressionTy()) {
    ostr << dynamic_cast<Expr*>(_expr1)->GetExpr();
  } else {
    ostr << _expr1->GetID();
  }

  ostr << " ? ";

  if (_expr2->GetType()->IsExpressionTy()) {
    ostr << dynamic_cast<Expr*>(_expr2)->GetExpr();
  } else {
    ostr << _expr2->GetID();
  }

  ostr << " : ";

  if (_expr3->GetType()->IsExpressionTy()) {
    ostr << dynamic_cast<Expr*>(_expr3)->GetExpr();
  } else {
    ostr << _expr3->GetID();
  }

  return ostr.str();
}

} // end namespace ir