// $Id: ExpressionType.h,v 1.7 2013/02/11 20:56:50 david Exp $ -*- c++ -*-
#ifndef __CDK8_SEMANTICS_EXPRESSIONTYPE_H__
#define __CDK8_SEMANTICS_EXPRESSIONTYPE_H__

#include <cstdlib>

/**
 * This is a quick and very dirty approach to type information.
 * It is defined this way (even though it's not extensible at all)
 * for simplicity.
 *
 * Nevertheless, new types can be added simply by using other
 * integer values other than the ones listed.
 */
struct ExpressionType {
  typedef unsigned long int type;
  size_t _size = 0; // in bytes
  type _name = TYPE_UNSPEC;

  // For supporting simple complex types (nullptr by default)
  ExpressionType *_subtype = nullptr;

  static const type TYPE_UNSPEC  = 0;

  static const type TYPE_INT     = 1UL<<0;
  static const type TYPE_DOUBLE  = 1UL<<1;
  static const type TYPE_BOOLEAN = 1UL<<2;
  static const type TYPE_STRING  = 1UL<<3;
  static const type TYPE_POINTER = 1UL<<4;
  static const type TYPE_STRUCT  = 1UL<<5;
  static const type TYPE_VOID    = 1UL<<30;

  static const type TYPE_ERROR   = 1UL<<31;

  inline ExpressionType() :
    _size(0), _name(TYPE_UNSPEC), _subtype(nullptr) {
  }
  inline ExpressionType(size_t size, type name) :
    _size(size), _name(name), _subtype(nullptr) {
  }
  inline size_t size() {
    return _size;
  }
  inline type name() {
    return _name;
  }
  inline ExpressionType *subtype() {
    return _subtype;
  }
};

#endif

// $Log: ExpressionType.h,v $
// Revision 1.7  2013/02/11 20:56:50  david
// *** empty log message ***
//
// Revision 1.6  2013/02/10 19:18:23  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.5  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.4  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.3  2012/03/06 15:07:46  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
