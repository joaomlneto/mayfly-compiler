%{
/* $Id: MFParser.y,v 1.18 2013/02/12 17:43:58 david Exp $ */
#include <cstdlib>  // needed for getenv
#include <iostream>
#include <string>
#include "YYParser.h"
#include "nodes/all.h"

#define LINE scanner()->lineno()

// The rules below will be included in the function yyparse, the main
// parsing function. The macro below will cause the function to become
// a method instead. This is very fragile, but works with byacc.
// The class is mayfly::YYParser, a cdk::Parser subclass using
// Flex and BYACC.
#define yyparse mayfly::YYParser::yyparse

%}

%union {
  int                                i;	/* integer value */
  double                             d;   /* double value */
  std::string                       *s;	/* symbol name or string literal */
  cdk::node::Node                   *node;	/* node pointer */
  cdk::node::Sequence               *sequence;
  cdk::node::expression::Expression *expression; /* expression nodes */
  ExpressionType                    *type;
  mayfly::node::FunctionDeclaration *fdecl;
};

/* LIST OF TOKENS */
%token tVOID tINTEGER tNUMBER tSTRING tPUBLIC tCONST tIF tTHEN tELSE tDO tWHILE tFOR
%token tIN tSTEP tUPTO tDOWNTO tCONTINUE tBREAK tRETURN tPRINTLN tINCREMENT tDECREMENT

/* LITERALS AND IDENTIFIER */
%token<i> tLINTEGER
%token<s> tLSTRING tIDENTIFIER
%token<d> tLNUMBER

/*******************************/
/* --- OPERATOR PRECEDENCE --- */

/* DANGLING IF-ELSE PROBLEM */
%nonassoc xIF
%nonassoc tELSE

/* not in language specification */
%nonassoc '#'

/* expression precedences - begin */
%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tEQ tNE
%left '<' '>' tLE tGE
%left '+' '-'
%left '*' '/' '%'
%nonassoc xPOINTED xADDR tUMINUS tINCREMENT tDECREMENT
%nonassoc '['
/* expression precedences - end */

%nonassoc xUMINUS xUPLUS /* not in language specification */

/* +++ OPERATOR PRECEDENCE +++ */
/* +++++++++++++++++++++++++++ */

/* non-terminal types */
%type<node> vardecl block cond iter
%type<fdecl> funcdecl

%type<sequence> decls blockdecls instrs args exprs fargs
%type<node>     decl  blockdecl  instr  arg

%type<expression> literal expr lval funcall
%type<type> type

%type<s> lstring

%%


file : decls { _compiler->ast($1); }
     |       { _compiler->ast(new cdk::node::Nil(LINE)); }
     ;

decls : decl       { $$ = new cdk::node::Sequence(LINE, $1); }
      | decls decl { $$ = new cdk::node::Sequence(LINE, $2, $1); }
      ;

decl : blockdecl      { $$ = $1; }
     | funcdecl       { $$ = $1; }
     | funcdecl block { $$ = new mayfly::node::FunctionDefinition(LINE, $1, $2); }
     ;

blockdecls : blockdecl            { $$ = new cdk::node::Sequence(LINE, $1); }
           | blockdecls blockdecl { $$ = new cdk::node::Sequence(LINE, $2, $1); }
			  ;

// Declarations only valid in blocks
blockdecl : vardecl ';'           { $$ = $1; }
			 ;

instrs : instr        { $$ = new cdk::node::Sequence(LINE, $1); }
       | instrs instr { $$ = new cdk::node::Sequence(LINE, $2, $1); }
		 ;

instr : expr ';'						{ $$ = new mayfly::node::ExpressionAsInstruction(LINE, $1); }
      | expr '!'						{ $$ = new mayfly::node::PrintNode(LINE, $1, false); }
		| expr tPRINTLN				{ $$ = new mayfly::node::PrintNode(LINE, $1, true); }
		| tBREAK ';'					{ $$ = new mayfly::node::BreakNode(LINE); }
		| tBREAK tLINTEGER ';'		{ $$ = new mayfly::node::BreakNode(LINE, $2); }
		| tCONTINUE ';'				{ $$ = new mayfly::node::ContinueNode(LINE); }
		| tCONTINUE tLINTEGER ';'	{ $$ = new mayfly::node::ContinueNode(LINE, $2); }
      | tRETURN						{ $$ = new mayfly::node::ReturnNode(LINE); }
		| cond							{ $$ = $1; }
		| iter							{ $$ = $1; }
		| block							{ $$ = $1; }
		;

// Variable declarations
vardecl : tPUBLIC tCONST type tIDENTIFIER				{ $$ = new mayfly::node::VariableDeclaration(LINE, $3, $4, true, true, NULL); }
		  | tPUBLIC type tIDENTIFIER						{ $$ = new mayfly::node::VariableDeclaration(LINE, $2, $3, true, false, NULL); }
		  | tCONST type tIDENTIFIER						{ $$ = new mayfly::node::VariableDeclaration(LINE, $2, $3, false, true, NULL); }
		  | type tIDENTIFIER									{ $$ = new mayfly::node::VariableDeclaration(LINE, $1, $2, false, false, NULL); }
		  | tPUBLIC tCONST type tIDENTIFIER '=' expr	{ $$ = new mayfly::node::VariableDeclaration(LINE, $3, $4, true, true, $6); }
		  | tPUBLIC type tIDENTIFIER '=' expr			{ $$ = new mayfly::node::VariableDeclaration(LINE, $2, $3, true, false, $5); }
		  | tCONST type tIDENTIFIER '=' expr			{ $$ = new mayfly::node::VariableDeclaration(LINE, $2, $3, false, true, $5); }
		  | type tIDENTIFIER '=' expr						{ $$ = new mayfly::node::VariableDeclaration(LINE, $1, $2, false, false, $4); }
        ;

// Function declarations (no definition)
funcdecl : tPUBLIC type tIDENTIFIER '(' fargs ')' '=' literal	{ $$ = new mayfly::node::FunctionDeclaration(LINE, $2, true, $3, $5, $8); }
			| tPUBLIC type tIDENTIFIER '(' fargs ')'					{ $$ = new mayfly::node::FunctionDeclaration(LINE, $2, true, $3, $5, NULL); }
         | tPUBLIC tVOID tIDENTIFIER '(' fargs ')'					{ $$ = new mayfly::node::FunctionDeclaration(LINE, new ExpressionType(0, ExpressionType::TYPE_VOID), true, $3, $5, NULL); }
			| type tIDENTIFIER '(' fargs ')' '=' literal				{ $$ = new mayfly::node::FunctionDeclaration(LINE, $1, false, $2, $4, $7); }
			| type tIDENTIFIER '(' fargs ')'								{ $$ = new mayfly::node::FunctionDeclaration(LINE, $1, false, $2, $4, NULL); }
			| tVOID tIDENTIFIER '(' fargs ')'							{ $$ = new mayfly::node::FunctionDeclaration(LINE, new ExpressionType(0, ExpressionType::TYPE_VOID), false, $2, $4, NULL); }
         ;

literal : tLINTEGER	{ $$ = new cdk::node::expression::Integer(LINE, $1); }
        | tLNUMBER	{ $$ = new cdk::node::expression::Double(LINE, $1); }
        | lstring		{ $$ = new cdk::node::expression::String(LINE, $1); }
		  ;

// String literals and concatenation
lstring : tLSTRING				{ $$ = $1; }
        | lstring tLSTRING		{ $$ = new std::string(*$1 + *$2); }
        ; 

// Function arguments (function declaration)
fargs : args			{ $$ = $1; }
      |					{ $$ = NULL;/*new cdk::node::Sequence(LINE, new cdk::node::Nil(LINE));*/ }
		;

args : arg					{ $$ = new cdk::node::Sequence(LINE, $1); }
     | args ',' arg		{ $$ = new cdk::node::Sequence(LINE, $3, $1); }
     ;

arg : type tIDENTIFIER	{ $$ = new mayfly::node::VariableDeclaration(LINE, $1, $2, false, false, NULL, true); }
    ;

// mayfly types
type : tINTEGER	{ $$ = new ExpressionType(4, ExpressionType::TYPE_INT); }
     | tNUMBER		{ $$ = new ExpressionType(8, ExpressionType::TYPE_DOUBLE); }
     | tSTRING		{ $$ = new ExpressionType(4, ExpressionType::TYPE_STRING); }
     | type '*'	{ $$ = new ExpressionType(4, ExpressionType::TYPE_POINTER); $$->_subtype = $1; }
     ;

block : '{' blockdecls instrs '}'	{ $$ = new mayfly::node::Block(LINE, $2, $3); }
      | '{' blockdecls '}'				{ $$ = new mayfly::node::Block(LINE, $2, NULL); }
      | '{' instrs '}'					{ $$ = new mayfly::node::Block(LINE, NULL, $2); }
      | '{' '}'							{ $$ = new mayfly::node::Block(LINE, NULL, NULL); }
      ;

cond : tIF expr tTHEN instr %prec xIF		{ $$ = new mayfly::node::IfNode(LINE, $2, $4); }
     | tIF expr tTHEN instr tELSE instr	{ $$ = new mayfly::node::IfElseNode(LINE, $2, $4, $6); }
     ;

iter : tFOR lval tIN expr tUPTO expr tSTEP expr tDO instr		{ $$ = new mayfly::node::ForUpToNode(LINE, $2, $4, $6, $8, $10); }
     | tFOR lval tIN expr tUPTO expr tDO instr						{ $$ = new mayfly::node::ForUpToNode(LINE, $2, $4, $6, NULL, $8); }
     | tFOR lval tIN expr tDOWNTO expr tSTEP expr tDO instr 	{ $$ = new mayfly::node::ForDownToNode(LINE, $2, $4, $6, $8, $10); }
     | tFOR lval tIN expr tDOWNTO expr tDO instr					{ $$ = new mayfly::node::ForDownToNode(LINE, $2, $4, $6, NULL, $8); }
     | tDO instr tWHILE expr ';'											{ $$ = new mayfly::node::DoWhileNode(LINE, $2, $4); }
     ;

expr : lval									{ $$ = $1; }
	  | literal								{ $$ = $1; }
	  | funcall								{ $$ = $1; }
	  | expr '+' expr						{ $$ = new cdk::node::expression::ADD(LINE, $1, $3); }
	  | expr '-' expr						{ $$ = new cdk::node::expression::SUB(LINE, $1, $3); }
	  | expr '*' expr						{ $$ = new cdk::node::expression::MUL(LINE, $1, $3); }
	  | expr '/' expr						{ $$ = new cdk::node::expression::DIV(LINE, $1, $3); }
	  | expr '%' expr						{ $$ = new cdk::node::expression::MOD(LINE, $1, $3); }
	  | expr '>' expr						{ $$ = new cdk::node::expression::GT(LINE, $1, $3); }
	  | expr '<' expr						{ $$ = new cdk::node::expression::LT(LINE, $1, $3); }
	  | expr tGE expr						{ $$ = new cdk::node::expression::GE(LINE, $1, $3); }
	  | expr tLE expr						{ $$ = new cdk::node::expression::LE(LINE, $1, $3); }
	  | expr tEQ expr						{ $$ = new cdk::node::expression::EQ(LINE, $1, $3); }
	  | expr tNE expr						{ $$ = new cdk::node::expression::NE(LINE, $1, $3); }
	  | expr '|' expr						{ $$ = new mayfly::node::expression::OR(LINE, $1, $3); }
	  | expr '&' expr						{ $$ = new mayfly::node::expression::AND(LINE, $1, $3); }
	  | tINCREMENT lval					{ $$ = new mayfly::node::expression::Increment(LINE, $2, true); }
	  | tDECREMENT lval					{ $$ = new mayfly::node::expression::Decrement(LINE, $2, true); }
	  | lval tINCREMENT					{ $$ = new mayfly::node::expression::Increment(LINE, $1, false); }
	  | lval tDECREMENT					{ $$ = new mayfly::node::expression::Decrement(LINE, $1, false); }
	  | '&' lval							{ $$ = new mayfly::node::expression::Addressing(LINE, $2); }
	  | '~' expr							{ $$ = new mayfly::node::expression::NOT(LINE, $2); }
	  | '@'									{ $$ = new mayfly::node::expression::Read(LINE); }
	  | '-' expr %prec xUMINUS			{ $$ = new cdk::node::expression::NEG(LINE, $2); }
	  | '+' expr %prec xUPLUS			{ $$ = new mayfly::node::expression::Identity(LINE, $2); }
	  | '#' expr                     { $$ = new mayfly::node::expression::MemoryReservation(LINE, $2); }
     | lval '=' expr						{ $$ = new mayfly::node::expression::Assignment(LINE, $1, $3); }
	  | '(' expr ')'						{ $$ = $2; }
     ;

lval : tIDENTIFIER								{ $$ = new mayfly::node::expression::LeftValue(LINE, $1); }
     | lval '[' expr ']'						{ $$ = new mayfly::node::expression::Indexing(LINE, $1, $3); }
	  | funcall '[' expr ']'					{ $$ = new mayfly::node::expression::Indexing(LINE, $1, $3); }
	  | '(' expr ')' '[' expr ']'				{ $$ = new mayfly::node::expression::Indexing(LINE, $2, $5); }
	  | '*' lval %prec xPOINTED				{ $$ = new mayfly::node::expression::Indexing(LINE, $2); }
	  | '*' '(' expr ')'	%prec xPOINTED		{ $$ = new mayfly::node::expression::Indexing(LINE, $3); }
	  | '*' funcall %prec xPOINTED			{ $$ = new mayfly::node::expression::Indexing(LINE, $2); }
	  ;

funcall : tIDENTIFIER '(' exprs ')'		{ $$ = new mayfly::node::expression::FunctionCall(LINE, $1, $3); }
        | tIDENTIFIER '(' ')'				{ $$ = new mayfly::node::expression::FunctionCall(LINE, $1, NULL); }
        ;

// Function arguments (function call)
exprs : expr ',' exprs	{ $$ = new cdk::node::Sequence(LINE, $1, $3); }
      | expr				{ $$ = new cdk::node::Sequence(LINE, $1); }
		;

%%
