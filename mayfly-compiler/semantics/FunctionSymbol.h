// $Id: FunctionSymbol.h,v 1.5 2013-05-11 22:15:29 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_FUNCTIONSYMBOL_H__
#define __MF_SEMANTICS_FUNCTIONSYMBOL_H__

#include <string>
#include "semantics/Symbol.h"

class FunctionSymbol : public Symbol {
public:
	const std::string TYPE = "FUNCTION";

protected:
	bool _is_public;
	bool _is_defined;
	// arguments?

public:
	inline FunctionSymbol(ExpressionType *type, const std::string &name, bool is_public, bool is_defined) :
		Symbol(type, name), _is_public(is_public), _is_defined(is_defined) {
	}

	inline FunctionSymbol(ExpressionType *type, const char *name, bool is_public, bool is_defined) :
		FunctionSymbol(type, name, is_public, is_defined) {
	}

	virtual ~FunctionSymbol() {
	}

	bool is_public() { return _is_public; }
	bool is_defined() { return _is_defined; }

	void is_public(bool is_public) { _is_public = is_public; }
	void is_defined(bool is_defined) { _is_defined = is_defined; }

	const std::string symbolType() const {
		return "TYPE";
	}

};

#endif

// $Log: FunctionSymbol.h,v $
// Revision 1.5  2013-05-11 22:15:29  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.4  2013-05-11 18:18:41  ist164787
// function declarations working, part of vardecls working
//
// Revision 1.3  2013-05-10 22:22:09  ist164787
// forgot to add FunctionSymbol file; fixed return value POP
//
//
