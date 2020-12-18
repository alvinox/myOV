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

    ModuleTyID,      ///<  8: Modules
    DesignTyID,      ///<  9: Designs
    ProcessTyID,     ///< 10: Processes
    ProcedureTyID,   ///< 11: Procedure
    StructTyID,      ///< 12: Structures

    TyIDCount,
  };

 explicit Type(Context& c, TypeID tid)
   : _context(c), _tid(tid) { }

 public:
  /// Return the type id for the type. This will return one of the TypeID enum
  /// elements defined above.
  TypeID GetTypeID() const { return _tid; }

  /// Return true if this is 'void'.
  bool IsVoidTy() const { return GetTypeID() == VoidTyID; }

  /// Return true if this is 'float', a 32-bit IEEE fp type.
  bool IsFloatTy() const { return GetTypeID() == FloatTyID; }

  /// Return true if this is 'double', a 64-bit IEEE fp type.
  bool IsDoubleTy() const { return GetTypeID() == DoubleTyID; }

  /// Return true if this is one of the six floating-point types
  bool IsFloatingPointTy() const {
    return GetTypeID() == FloatTyID ||
           GetTypeID() == DoubleTyID;
  }

  /// Return true if this is an IntegerType of the given width.
  bool IsIntegerTy(unsigned Bitwidth) const;

  bool IsRegisterTyID() const { return GetTypeID() == RegisterTyID; }

  bool IsWireTyID() const { return GetTypeID() == WireTyID; }

  bool IsModuleTy() const { return GetTypeID() == ModuleTyID; }

  bool IsDesignTy() const { return GetTypeID() == DesignTyID; }

 private:
  Context& _context;
  TypeID   _tid;
};

} // end namespace ir

#endif // _TYPE_SYSTEM_H_
