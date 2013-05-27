// $Id: MFScanner.h,v 1.1 2013-02-16 16:10:15 ist13500 Exp $ -*- c++ -*-
#ifndef __MFSCANNER_H__
#define __MFSCANNER_H__

#undef yyFlexLexer
#define yyFlexLexer MFScanner
#include <FlexLexer.h>

#endif

// $Log: MFScanner.h,v $
// Revision 1.1  2013-02-16 16:10:15  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.12  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.11  2012/04/10 19:09:46  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
