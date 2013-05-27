// $Id: CompilerFactory.cpp,v 1.2 2013/02/12 18:56:15 david Exp $ -*- c++ -*-
#include "CompilerFactory.h"

pf2asm::CompilerFactory pf2asm::CompilerFactory::_self("pf2asm");

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: CompilerFactory.cpp,v $
// Revision 1.2  2013/02/12 18:56:15  david
// Major code cleanup and simplification. Uses CDK8. C++11 is required.
//
// Revision 1.1  2009/03/04 20:22:24  david
// *** empty log message ***
//
// Revision 1.3  2009/02/28 21:01:06  david
// Minor cleanup.
//
// Revision 1.2  2009/02/28 19:58:03  david
// Introduced integer expressions with literals only (i.e., no variables).
// It is now possible to write 16*1024+8.
//
// Revision 1.1  2009/02/25 07:31:56  david
// First working version of pf2asm. This version still uses
// byacc.
//
// Revision 1.1  2009/02/23 20:53:38  david
// First PF implementation. Does not work with PF syntax nor
// does it do anything useful.
//
