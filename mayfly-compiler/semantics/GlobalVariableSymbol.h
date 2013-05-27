// $Id: GlobalVariableSymbol.h,v 1.3 2013-05-14 21:52:52 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_GLOBALVARIABLESYMBOL_H__
#define __MF_SEMANTICS_GLOBALVARIABLESYMBOL_H__

#include <string>
#include "semantics/Symbol.h"

class GlobalVariableSymbol : public VariableSymbol {
public:
	const std::string TYPE = "GLOBAL VARIABLE";

protected:
	std::string _label;

public:
	inline GlobalVariableSymbol(ExpressionType *type, const std::string &name, bool is_global, bool is_const, std::string label) :
		VariableSymbol(type, name, is_global, is_const), _label(label) {
	}

	inline GlobalVariableSymbol(ExpressionType *type, const char *name, bool is_global, bool is_const, std::string label) :
		VariableSymbol(type, name, is_global, is_const), _label(label) {
	}

	virtual ~GlobalVariableSymbol() {
	}

	inline std::string label() {
		return _label;
	}

	const std::string symbolType() const {
		return TYPE;
	}

};

#endif

// $Log: GlobalVariableSymbol.h,v $
// Revision 1.3  2013-05-14 21:52:52  ist164787
// minor bugfixes
//
// Revision 1.2  2013-05-14 14:41:24  ist164787
// bugfixes in many expressions when dealing with leftvalues, bugfix in print nodes; fixed a bug for increment node on typevalidator
//
// Revision 1.1  2013-05-11 22:15:29  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.4  2013-05-09 21:20:16  ist164787
// minor changes
//
// Revision 1.3  2013-05-09 18:19:35  ist164787
// forgot to add GlobalVariableSymbol file
//
//
