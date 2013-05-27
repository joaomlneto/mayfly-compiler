// $Id: PFevaluator.cpp,v 1.1 2013-02-16 16:10:14 ist13500 Exp $
#include "semantics/PFevaluator.h"

/**
 * Postfix for ix86.
 * @var create and register an evaluator for ASM targets.
 */
mayfly::semantics::PFevaluator mayfly::semantics::PFevaluator::_self("asm");

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: PFevaluator.cpp,v $
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.10  2013/02/12 17:43:57  david
// Further code simplification (evaluators).
//
// Revision 1.9  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.8  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.7  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.6  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
