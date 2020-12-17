#ifndef _TYPE_SYSTEM_H_
#define _TYPE_SYSTEM_H_

#include "Context.h"

namespace ir {

class Context;

class Type {
 public:
  enum TypeID {
    VoidTyID = 0,    ///<  0: type with no size
    // HalfTyID,     ///<  1: 16-bit floating point type
    FloatTyID,       ///<  1: 32-bit floating point type
    DoubleTyID,      ///<  2: 64-bit floating point type
    IntegerTyID,     ///<  3: Arbitrary bit width integers
    RegisterTyID,    ///<  4: Register
    WireTyID,        ///<  5: Wire
    MemoryTyID,      ///<  6: Memory

    DesignTyID,      ///<  7: Processes
    ProcessTyID,     ///<  8: Processes
    ProcedureTyID,   ///<  9: Procedure
    StructTyID,      ///< 10: Structures

    TyIDCount,
  };

 explicit Type(Context& c, TypeID tid)
   : _context(c), _tid(tid) { }

 public:
  /// Return the type id for the type. This will return one of the TypeID enum
  /// elements defined above.
  TypeID getTypeID() const { return _tid; }

  /// Return true if this is 'void'.
  bool isVoidTy() const { return getTypeID() == VoidTyID; }

  /// Return true if this is 'float', a 32-bit IEEE fp type.
  bool isFloatTy() const { return getTypeID() == FloatTyID; }

  /// Return true if this is 'double', a 64-bit IEEE fp type.
  bool isDoubleTy() const { return getTypeID() == DoubleTyID; }

  /// Return true if this is one of the six floating-point types
  bool isFloatingPointTy() const {
    return getTypeID() == FloatTyID ||
           getTypeID() == DoubleTyID;
  }

  /// Return true if this is an IntegerType of the given width.
  bool isIntegerTy(unsigned Bitwidth) const;

  bool isDesignTy() const { return getTypeID() == DesignTyID; }

 private:
  Context& _context;
  TypeID   _tid;
};

} // end namespace ir

#endif // _TYPE_SYSTEM_H_
