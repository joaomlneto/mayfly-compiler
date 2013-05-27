%option stack noyywrap yylineno 8bit c++ debug yymore
%option yyclass="PFScanner" outfile="PFScanner.cpp"
%{
// $Id: PFScanner.l,v 1.10 2013/02/12 18:56:15 david Exp $
#include <string>
#include <stack>
#include <sstream>
#include <iostream>
#include "nodes/all.h"   // needed by PFParser.tab.h
#include "PFScanner.h"
#include "PFParser.tab.h"

// output stream for building string literals
static std::ostringstream strlit;

// more horrible stuff
#define yyerror LexerError

//---------------------------------------------------------------------------
//using namespace std;
%}

SPACE     ([ \t\r]|\n)
INT       [[:digit:]]+

%x X_COMMENT X_STRING X_BACKSLASH X_HEXADECIMAL X_HEX_INT

%%

  /* ====================================================================== */
  /* ====[                         COMMENTS                           ]==== */
  /* ====================================================================== */

";".*$                /* match the whole line (it is ignored) */

"/*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"*/"        yy_pop_state();
<X_COMMENT>.|"\n"      ;  /* ignore inside comments */

  /* ====================================================================== */
  /* ====[                  MNEMONICS / INTRUCTIONS                   ]==== */
  /* ====================================================================== */
  
NOP    return tNOP;
INT    return tINT;
ADD    return tADD;
SUB    return tSUB;
MUL    return tMUL;
DIV    return tDIV;
MOD    return tMOD;
NEG    return tNEG;
INCR   return tINCR;
DECR   return tDECR;
GT     return tGT;
GE     return tGE;
LT     return tLT;
LE     return tLE;
EQ     return tEQ;
NE     return tNE;
AND    return tAND;
OR     return tOR;
XOR    return tXOR;
NOT    return tNOT;
ROTL   return tROTL;
ROTR   return tROTR;
SHTL   return tSHTL;
SHTRU  return tSHTRU;
SHTRS  return tSHTRS;
LOCAL  return tLOCAL;
ADDR   return tADDR;
LOCV   return tLOCV;
ADDRV  return tADDRV;
LOCA   return tLOCA;
ADDRA  return tADDRA;
LOAD   return tLOAD;
STORE  return tSTORE;
LDCHR  return tLDCHR;
STCHR  return tSTCHR;
LD16   return tLD16;
ST16   return tST16;
ENTER  return tENTER;
START  return tSTART;
ALLOC  return tALLOC;
LEAVE  return tLEAVE;
TRASH  return tTRASH;
CALL   return tCALL;
RET    return tRET;
RETN   return tRETN;
BRANCH return tBRANCH;
LEAP   return tLEAP;
JMP    return tJMP;
JZ     return tJZ;
JNZ    return tJNZ;
DUP    return tDUP;
DDUP   return tDDUP;
SWAP   return tSWAP;
SP     return tSP;
PUSH   return tPUSH;
POP    return tPOP;
I2D    return tI2D;
F2D    return tF2D;
D2I    return tD2I;
D2F    return tD2F;
DADD   return tDADD;
DSUB   return tDSUB;
DMUL   return tDMUL;
DDIV   return tDDIV;
DCMP   return tDCMP;
DNEG   return tDNEG;
DLOAD  return tDLOAD;
DSTORE return tDSTORE;
DPUSH  return tDPUSH;
DPOP   return tDPOP;
NIL    return tNIL;
TEXT   return tTEXT;
RODATA return tRODATA;
DATA   return tDATA;
BSS    return tBSS;
ALIGN  return tALIGN;
EXTERN return tEXTERN;
COMMON return tCOMMON;
GLOBAL return tGLOBAL;
LABEL  return tLABEL;
CONST  return tCONST;
STR    return tSTR;
CHAR   return tCHAR;
ID     return tID;
BYTE   return tBYTE;
FLOAT  return tFLOAT;
DOUBLE return tDOUBLE;
ULDCHR return tULDCHR;
ULD16  return tULD16;
UDIV   return tUDIV;
UMOD   return tUMOD;
UGT    return tUGT;
UGE    return tUGE;
ULT    return tULT;
ULE    return tULE;
JEQ    return tJEQ;
JNE    return tJNE;
JGT    return tJGT;
JGE    return tJGE;
JLT    return tJLT;
JLE    return tJLE;
JUGT   return tJUGT;
JUGE   return tJUGE;
JULT   return tJULT;
JULE   return tJULE;

  /* ====================================================================== */
  /* ====[               EXPRESSION OPERATORS (LITERALS)              ]==== */
  /* ====================================================================== */

[-+*/%!<>?:@]          return *yytext;
"=="                   return T_EQ;
"!="                   return T_NE;
"<="                   return T_LE;
">="                   return T_GE;
"&&"                   return T_AND;
"||"                   return T_OR;

  /* ====================================================================== */
  /* ====[                DELIMITERS AND SEPARATORS                   ]==== */
  /* ====================================================================== */

[(),]                return *yytext;

  /* ====================================================================== */
  /* ====[                     INTEGER NUMBERS                        ]==== */
  /* ====================================================================== */

"0x"[[:xdigit:]]+    yylval.i = strtoul(yytext+2, NULL, 16); return T_LIT_INT;
{INT}                yylval.i = strtoul(yytext,   NULL, 10); return T_LIT_INT;

  /* ====================================================================== */
  /* ====[                       REAL NUMBERS                         ]==== */
  /* ====================================================================== */

([0-9]*\.[0-9]+|[0-9]+\.[0-9])([Ee]([-+])?[0-9]+)? { yylval.d = strtod(yytext, NULL); return T_LIT_REAL; }

  /* ====================================================================== */
  /* ====[                        IDENTIFIERS                         ]==== */
  /* ====================================================================== */

([[:alpha:]]|[_.:])([[:alnum:]]|[_.:])*  yylval.s = new std::string(yytext); return T_ID;

  /* ====================================================================== */
  /* ====[                          STRINGS                           ]==== */
  /* ====================================================================== */

"\""                           yy_push_state(X_STRING);
<X_STRING>\\                   yy_push_state(X_BACKSLASH);
<X_STRING>"\""                 {
                                 yylval.s = new std::string(strlit.str());
                                 strlit.str("");
                                 yy_pop_state();
                                 return T_LIT_STRING;
                               }
<X_STRING>.                    strlit << *yytext;

<X_BACKSLASH>n                 strlit << '\n'; yy_pop_state();
<X_BACKSLASH>r                 strlit << '\r'; yy_pop_state();
<X_BACKSLASH>t                 strlit << '\t'; yy_pop_state();
<X_BACKSLASH>"\""              strlit << '\"'; yy_pop_state();
<X_BACKSLASH>\\                strlit << '\\'; yy_pop_state();
<X_BACKSLASH>.                 strlit << *yytext; yy_pop_state();

  /* ====================================================================== */
  /* ====[                         AFTER THE END                      ]==== */
  /* ====================================================================== */

[[:space:]]|\n         /* ignore remaining white space inside the program */
.                      yyerror(yytext);    /* all other chars: error! */

  /* ====================================================================== */
  /* ====[                           THE END                          ]==== */
  /* ====================================================================== */

%%
// Very, very dirty hack, but Flex is a mess generating C++.
int PFScanner::yywrap() { return 1;}

/*
 * $Log: PFScanner.l,v $
 * Revision 1.10  2013/02/12 18:56:15  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.9  2012/02/19 20:30:16  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 * Revision 1.8  2009/05/09 16:50:59  david
 * First pf2asm-lite ready to roll.
 *
 * Revision 1.7  2009/05/09 16:29:34  david
 * Simplified some elements (integers and strings).
 *
 * Revision 1.6  2009/03/02 13:26:51  david
 * Code cleanup. Removed a few minor warnings.
 *
 * Revision 1.5  2009/02/28 21:01:06  david
 * Minor cleanup.
 *
 */