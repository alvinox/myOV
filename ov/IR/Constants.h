#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// class ConstantData : public Value {
//  public:
//   void operator=(const ConstantData&) = delete;
//   ConstantData(const ConstantData&) = delete;
// };

// class ConstantInt final : public ConstantData {
//  public:
//   static Value* get(Context& context, const APInt& v);
//  public:

//   ConstantInt(const APInt& v);
//  private:
//   APInt _val;
// }

// class ConstantFP final : public ConstantData {
//  public:
//   static Value* get(Context& context, const APFloat& v);
//  public:
//   ConstantFP(const APFloat& v);
//  private:
//   APFloat _val;
// }
#include <sstream>

#include "Value.h"
#include "Context.h"

namespace ir {

class Constant : public Value {
 public:
  Constant(const std::string& id)
    : Value(id, nullptr) { }
};

class ConstantInt final : public Constant {
 friend class Context;
 public:
  static Value* Get(Context& context, int v);

 private:
  ConstantInt(Context& context, int v);

 private:
  int _val;
};

class ConstantFloat final : public Constant {
 public:
  static Value* Get(Context& context, float v);
 public:

  ConstantFloat(float v);
 private:
  float _val;
};

} // end namespace ir

#endif // _CONSTANTS_H_