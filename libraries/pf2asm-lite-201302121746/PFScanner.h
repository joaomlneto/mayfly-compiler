// $Id: PFScanner.h,v 1.3 2013/02/12 18:56:15 david Exp $
#ifndef __PF_PFSCANNER_H__
#define __PF_PFSCANNER_H__

#undef yyFlexLexer
#define yyFlexLexer PFScanner
#include <FlexLexer.h>

#endif

/*
 * $Log: PFScanner.h,v $
 * Revision 1.3  2013/02/12 18:56:15  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.2  2009/02/28 19:58:03  david
 * Introduced integer expressions with literals only (i.e., no variables).
 * It is now possible to write 16*1024+8.
 *
 * Revision 1.1  2009/02/25 07:31:56  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 * Revision 1.1  2009/02/23 20:53:38  david
 * First PF implementation. Does not work with PF syntax nor
 * does it do anything useful.
 *
 *
 */
