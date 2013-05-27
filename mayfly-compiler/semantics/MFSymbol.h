// $Id: MFSymbol.h,v 1.1 2013-02-16 16:10:14 ist13500 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_SYMBOL_H__
#define __MF_SEMANTICS_SYMBOL_H__

#include <string>

class MFSymbol {
  int _type;
  std::string _name;
  int _value;

public:
  inline MFSymbol(int type, const std::string &name, int value) :
    _type(type), _name(name), _value(value) {
  }

  inline MFSymbol(int type, const char *name, int value) :
    _type(type), _name(name), _value(value) {
  }

  virtual ~MFSymbol() {
  }

  inline int type() const {
    return _type;
  }
  inline const std::string &name() const {
    return _name;
  }
  inline int value() const {
    return _value;
  }
  inline int value(int v) {
    return _value = v;
  }
};

#endif

// $Log: MFSymbol.h,v $
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.3  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.2  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.1  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
