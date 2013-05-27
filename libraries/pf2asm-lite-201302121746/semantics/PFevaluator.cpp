// $Id: PFevaluator.cpp,v 1.10 2013/02/12 18:56:17 david Exp $
#include "semantics/PFevaluator.h"

/**
 * Postfix for ix86.
 * @var create and register an evaluator for ASM targets.
 */
pf2asm::semantics::PFevaluator pf2asm::semantics::PFevaluator::_self("asm");

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
/*
 * $Log: PFevaluator.cpp,v $
 * Revision 1.10  2013/02/12 18:56:17  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.9  2012/02/19 20:30:16  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 * Revision 1.8  2011/03/06 14:53:19  david
 * Ported to CDK6.
 *
 * Revision 1.7  2009/03/02 13:26:51  david
 * Code cleanup. Removed a few minor warnings.
 *
 * Revision 1.6  2009/03/01 20:45:10  david
 * The symbol table now needs a symbol type. In this case, and
 * given the simplicity of this compiler, symbols are just strings.
 * This may change in future revisions.
 *
 * Revision 1.5  2009/02/28 21:01:07  david
 * Minor cleanup.
 *
 * Revision 1.4  2009/02/25 07:31:57  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 */
