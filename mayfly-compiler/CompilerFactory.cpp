// $Id: CompilerFactory.cpp,v 1.1 2013-02-16 16:10:14 ist13500 Exp $ -*- c++ -*-

#include "CompilerFactory.h"

/**
 * This object is automatically registered by the constructor in the
 * superclass' language registry.
 */
mayfly::CompilerFactory mayfly::CompilerFactory::_self("mayfly");

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: CompilerFactory.cpp,v $
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.7  2013/02/12 17:43:58  david
// Further code simplification (evaluators).
//
// Revision 1.6  2013/02/11 20:56:27  david
// Minor cleanup.
//
// Revision 1.5  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.4  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.3  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
