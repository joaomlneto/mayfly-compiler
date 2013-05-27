// $Id: LocalVariableSymbol.h,v 1.2 2013-05-11 23:36:57 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_LOCALVARIABLESYMBOL_H__
#define __MF_SEMANTICS_LOCALVARIABLESYMBOL_H__

#include <string>
#include "semantics/Symbol.h"

class LocalVariableSymbol : public VariableSymbol {
public:
	const std::string TYPE = "LOCAL VARIABLE";

protected:
	int _local_offset;

public:
	inline LocalVariableSymbol(ExpressionType *type, const std::string &name, bool is_static, bool is_const, int local_offset) :
		VariableSymbol(type, name, is_static, is_const), _local_offset(local_offset) {
	}

	inline LocalVariableSymbol(ExpressionType *type, const char *name, bool is_static, bool is_const, int local_offset) :
		VariableSymbol(type, name, is_static, is_const), _local_offset(local_offset) {
	}

	virtual ~LocalVariableSymbol() {
	}

	inline const int local_offset() const {
		return _local_offset;
	}

	const std::string symbolType() const {
		return TYPE;
	}

};

#endif

// $Log: LocalVariableSymbol.h,v $
// Revision 1.2  2013-05-11 23:36:57  ist164787
// Function arguments working in proper order AFAIK. Left values only work as Right Values (and if identifier is local variable)... other stuff less important...
//
// Revision 1.1  2013-05-11 22:15:30  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.4  2013-05-09 21:20:16  ist164787
// minor changes
//
// Revision 1.3  2013-05-09 18:19:35  ist164787
// forgot to add LocalVariableSymbol file
//
//
