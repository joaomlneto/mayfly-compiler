// $Id: VariableSymbol.h,v 1.6 2013-05-14 21:52:53 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_VARIABLESYMBOL_H__
#define __MF_SEMANTICS_VARIABLESYMBOL_H__

#include <string>
#include "semantics/Symbol.h"

class VariableSymbol : public Symbol {
public:
	const std::string TYPE = "VARIABLE";

protected:
	bool _is_global;
	bool _is_const;
	bool _is_local;

public:
	inline VariableSymbol(ExpressionType *type, const std::string &name, bool is_global, bool is_const) :
		Symbol(type, name), _is_global(is_global), _is_const(is_const) {
	}

	inline VariableSymbol(ExpressionType *type, const char *name, bool is_global, bool is_const) :
		Symbol(type, name), _is_global(is_global), _is_const(is_const) {
	}

	virtual ~VariableSymbol() {
	}

	inline bool is_global() { return _is_global; }
	inline bool is_const() { return _is_const; }
	inline bool is_local() { return _is_local; }

	const std::string symbolType() const {
		return TYPE;
	}

};

//const char *VariableSymbol::TYPE = "VARIABLE";

#endif

// $Log: VariableSymbol.h,v $
// Revision 1.6  2013-05-14 21:52:53  ist164787
// minor bugfixes
//
// Revision 1.5  2013-05-11 22:15:30  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.4  2013-05-09 21:20:16  ist164787
// minor changes
//
// Revision 1.3  2013-05-09 18:19:35  ist164787
// forgot to add variablesymbol file
//
//
