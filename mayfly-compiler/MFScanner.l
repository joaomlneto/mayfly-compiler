%option c++ yyclass="MFScanner" outfile="MFScanner.cpp"
%option stack noyywrap yylineno 8bit
%option debug warn
%{ 
/* $Id: MFScanner.l,v 1.14 2013/02/11 20:56:27 david Exp $ */
#include <string>
#include <cdk/nodes/Node.h>
#include <cdk/nodes/Sequence.h>
#include <cdk/nodes/expressions/Expression.h>
#include "MFScanner.h"

// ensure that relevant includes are made before including the following
#include "MFParser.tab.h"

// this is terrible...
#define yyerror LexerError

%}

ALPHA			[a-zA-Z]
ALPHANUM		[0-9]|{ALPHA}
HEXNUM			[0-9a-fA-F]

WHITESPACE		[ \n\r\t]
IDENTIFIER		({ALPHA}|_)({ALPHANUM}|_)*

INTEGER_DEC		0|([1-9][0-9]*)
INTEGER_OCT		0[0-7]+
INTEGER_HEX		0x{HEXNUM}+

NUMBER_1		[0-9]+\.[0-9]*([eE][0-9]+)?
NUMBER_2		[0-9]*\.[0-9]+([eE][0-9]+)?
NUMBER			{NUMBER_1}|{NUMBER_2}

%x X_COMMENT X_STRING X_STR_SPECIAL X_ZERO X_OCTAL

%%

"void"					return tVOID;
"integer"				return tINTEGER;
"number"				return tNUMBER;
"string"				return tSTRING;
"public"				return tPUBLIC;
"const"					return tCONST;
"if"					return tIF;
"then"					return tTHEN;
"else"					return tELSE;
"do"					return tDO;
"while"					return tWHILE;
"for"					return tFOR;
"in"					return tIN;
"step"					return tSTEP;
"upto"					return tUPTO;
"downto"				return tDOWNTO;
"continue"				return tCONTINUE;
"break"					return tBREAK;
"return"				return tRETURN;
"!!"					return tPRINTLN;
"++"					return tINCREMENT;
"--"					return tDECREMENT;
"<="					return tLE;
">="					return tGE;
"=="					return tEQ;
"<>"					return tNE;
[,;:!(){}]				return *yytext;
[[\]*&+-/%<>~|=@#]			return *yytext;

">>".*$							;
<INITIAL,X_COMMENT>"=<"			yy_push_state(X_COMMENT);
<X_COMMENT>"=>"				yy_pop_state();
<X_COMMENT>.|\n				;

{IDENTIFIER}				{ yylval.s = new std::string(yytext); return tIDENTIFIER; }

\"					{yy_push_state(X_STRING); yylval.s = new std::string();}
<X_STRING>\"				{yy_pop_state(); return tLSTRING;}
<X_STRING>\\				{yy_push_state(X_STR_SPECIAL);}
<X_STRING>.				{*yylval.s += yytext;}

<X_STR_SPECIAL>n			{yy_pop_state(); *yylval.s += std::string(1,10); }
<X_STR_SPECIAL>r			{yy_pop_state(); *yylval.s += std::string(1,13); }
<X_STR_SPECIAL>t			{yy_pop_state(); *yylval.s += std::string(1,9); }
<X_STR_SPECIAL>[\"\\]			{yy_pop_state(); *yylval.s += std::string(1,(int)*yytext); }
<X_STR_SPECIAL>[0-9a-fA-F][0-9a-fA-F]?	{yy_pop_state(); *yylval.s += std::string(1,strtol(yytext, nullptr, 16)); }
<X_STR_SPECIAL>.|\n			yyerror("Invalid special character");

{INTEGER_HEX}		{ yylval.i = strtol(yytext, nullptr, 16); if(errno == ERANGE) yyerror("Invalid number range, overflow occurred"); return tLINTEGER; }
{INTEGER_DEC}		{ yylval.i = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("Invalid number range, overflow occurred"); return tLINTEGER; }
{INTEGER_OCT}		{ yylval.i = strtol(yytext, nullptr, 8); if(errno == ERANGE) yyerror("Invalid number range, overflow occurred"); return tLINTEGER; }
0[0-9]+		yyerror("Invalid number!");

{NUMBER}		{ yylval.d = strtod(yytext, nullptr); if(errno == ERANGE) yyerror("Invalid number range, overflow occurred"); return tLNUMBER; }

{WHITESPACE}*		; /* ignore whitespace */

.			{
			std::cout << "Found character '" << yytext << "' on line " << yylineno << std::endl;
			yyerror("Unknown character");
			}

%%

/**
 * Very, very dirty hack: flex is a mess generating C++.
 */
int MFScanner::yywrap() { return 1;}

