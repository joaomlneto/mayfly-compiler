// $Id: Symbol.h,v 1.7 2013-05-20 19:31:32 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_SYMBOL_H__
#define __MF_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/semantics/ExpressionType.h>

// uncomment next line for debug prints
//#define __SYMBOL_DEBUG__

class Symbol {
protected:
	ExpressionType *_type;
	std::string _name;

public:
	inline Symbol(ExpressionType *type, const std::string &name) :
		_type(type), _name(name) {
#ifdef __SYMBOL_DEBUG__
		std::cout << "[SYMBOL] [CONSTRUCTOR] " << name << " with expressiontype " << type->name() << std::endl;
#endif
	}

	inline Symbol(ExpressionType *type, const char *name) :
		_type(type), _name(name) {
	}

	virtual ~Symbol() {
	}

	inline ExpressionType *type() const {
		return _type;
	}
	inline const std::string &name() const {
		return _name;
	}

	virtual const std::string symbolType() const = 0;

};

#endif

// $Log: Symbol.h,v $
// Revision 1.7  2013-05-20 19:31:32  ist164787
// misc fixes
//
// Revision 1.6  2013-05-15 16:00:47  ist164787
// fixed bug in flex and byacc - doubles with capital E were not recognized (only with undercase e), expressions within parenthesis can be indexed - its also a left value. this case was not covered previously
//
// Revision 1.5  2013-05-11 22:15:30  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.4	2013-05-09 21:20:16	ist164787
// minor changes
//
// Revision 1.3	2013-05-09 18:06:49	ist164787
// Changed Symbol.h
//
// Revision 1.2	2013-05-09 15:51:23	ist164787
// Small changes on FunctionDefinition and StackCounter
//
// Revision 1.1	2013-05-07 19:03:05	ist164787
// added missing files... oops
//
// Revision 1.1	2013-02-16 16:10:14	ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.3	2013/02/09 18:57:47	david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.2	2012/04/10 19:09:47	david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.1	2012/02/18 19:37:58	david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to Symbol, to emphasize
// that it is language-specific.
//
