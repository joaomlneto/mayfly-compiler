%{
// $Id: PFParser.y,v 1.8 2013/02/12 18:56:15 david Exp $
#include <cstdlib>      // needed for getenv
#include <iostream>
#include <string>
#include "YYParser.h"
#include "nodes/all.h"  // automatically generated

#define LINE scanner()->lineno()

// very fragile, but works with byacc
#define yyparse pf2asm::YYParser::yyparse
%}

%union {
  int                    i;             /* integer number */
  double                 d;             /* real number */
  std::string           *s;             /* symbol name or string literal */
  cdk::node::Node       *node;          /* node pointer */
  cdk::node::Sequence   *sequence;      /* node pointer */
}

%token tNOP tINT tADD tSUB tMUL tDIV tMOD tNEG tINCR tDECR tGT tGE tLT tLE
%token tEQ tNE tAND tOR tXOR tNOT tROTL tROTR tSHTL tSHTRU tSHTRS tLOCAL
%token tADDR tLOCV tADDRV tLOCA tADDRA tLOAD tSTORE tLDCHR tSTCHR tLD16
%token tST16 tENTER tSTART tALLOC tLEAVE tTRASH tCALL tRET tRETN tBRANCH
%token tLEAP tJMP tJZ tJNZ tDUP tDDUP tSWAP tSP tPUSH tPOP tI2D tF2D tD2I tD2F
%token tDADD tDSUB tDMUL tDDIV tDCMP tDNEG tDLOAD tDSTORE tDPUSH tDPOP
%token tNIL tTEXT tRODATA tDATA tBSS tALIGN tEXTERN tCOMMON tGLOBAL tLABEL
%token tCONST tSTR tCHAR tID tBYTE tFLOAT tDOUBLE tULDCHR tULD16
%token tUDIV tUMOD tUGT tUGE tULT tULE tJEQ tJNE tJGT tJGE tJLT tJLE tJUGT
%token tJUGE tJULT tJULE

%token T_AND T_OR T_NE T_LE T_GE

%token<i> T_LIT_INT
%token<d> T_LIT_REAL
%token<s> T_LIT_STRING T_ID

%type<node> instruction data function addressing loadstore jumps
%type<node> bitwise logical arithmetic relational
%type<sequence> file instructions  
%type<s> label type
%type<i> integer bytes offset

%nonassoc '?'
%nonassoc ':'
%left T_OR
%left T_AND
%left T_NE T_EQ
%left '<' T_LE T_GE '>'
%left '+' '-'
%left '*' '/' '%'
%right T_UMINUS '!'

%%

file	         : /* empty */  { _compiler->ast($$ = new cdk::node::Sequence(LINE, new cdk::node::Nil(LINE))); }
               | instructions { _compiler->ast($$ = $1); }
               ;

instructions    : instruction                                { $$ = new cdk::node::Sequence(LINE, $1);     }
                | instructions instruction                   { $$ = new cdk::node::Sequence(LINE, $2, $1); }
                ;

instruction     : tNOP              { $$ = new pf2asm::node::NOP(LINE); }
                | tINCR integer     { $$ = new pf2asm::node::INCR(LINE, $2); }
                | tDECR integer     { $$ = new pf2asm::node::DECR(LINE, $2); }
                | tALLOC            { $$ = new pf2asm::node::ALLOC(LINE); }
                | tTRASH bytes      { $$ = new pf2asm::node::TRASH(LINE, $2); }
                | tDUP              { $$ = new pf2asm::node::DUP(LINE); }
                | tDDUP             { $$ = new pf2asm::node::DDUP(LINE); }
                | tSWAP             { $$ = new pf2asm::node::SWAP(LINE); }
                | tSP               { $$ = new pf2asm::node::SP(LINE); }
                | tI2D              { $$ = new pf2asm::node::I2D(LINE); }
                | tF2D              { $$ = new pf2asm::node::F2D(LINE); }
                | tD2I              { $$ = new pf2asm::node::D2I(LINE); }
                | tD2F              { $$ = new pf2asm::node::D2F(LINE); }
                | tNIL              { $$ = new pf2asm::node::NIL(LINE); }
                | data              { $$ = $1; }
                | function          { $$ = $1; }
                | addressing        { $$ = $1; }
                | loadstore         { $$ = $1; }
                | bitwise           { $$ = $1; }
                | logical           { $$ = $1; }
                | arithmetic        { $$ = $1; }
                | relational        { $$ = $1; }
                | jumps             { $$ = $1; }
                ;

bytes           : integer           { $$ = $1; };

data            : tCONST   integer      { $$ = new pf2asm::node::data::CONST  (LINE, $2); }
                | tSTR     T_LIT_STRING { $$ = new pf2asm::node::data::STR    (LINE, *$2); delete $2; }
                | tCHAR    T_LIT_STRING { $$ = new pf2asm::node::data::CHAR   (LINE, *$2); delete $2; }
                | tID      label        { $$ = new pf2asm::node::data::ID     (LINE, *$2); delete $2; }
                | tBYTE    integer      { $$ = new pf2asm::node::data::BYTE   (LINE, $2); }
                | tINT     integer      { $$ = new pf2asm::node::data::INT    (LINE, $2); }
                | tFLOAT   T_LIT_REAL   { $$ = new pf2asm::node::data::FLOAT  (LINE, $2); }
                | tDOUBLE  T_LIT_REAL   { $$ = new pf2asm::node::data::DOUBLE (LINE, $2); }
                ;

addressing      : tTEXT             { $$ = new pf2asm::node::addressing::TEXT   (LINE); }
                | tRODATA           { $$ = new pf2asm::node::addressing::RODATA (LINE); }
                | tDATA             { $$ = new pf2asm::node::addressing::DATA   (LINE); }
                | tBSS              { $$ = new pf2asm::node::addressing::BSS    (LINE); }
                | tALIGN            { $$ = new pf2asm::node::addressing::ALIGN  (LINE); }
                | tCOMMON integer   { $$ = new pf2asm::node::addressing::COMMON (LINE, $2); }
                | tLOCAL  offset    { $$ = new pf2asm::node::addressing::LOCAL  (LINE, $2); }
                | tLOCV   offset    { $$ = new pf2asm::node::addressing::LOCV   (LINE, $2); }
                | tLOCA   offset    { $$ = new pf2asm::node::addressing::LOCA   (LINE, $2); }
                | tGLOBAL label ',' type  { $$ = new pf2asm::node::addressing::GLOBAL(LINE, *$2, *$4); delete $2; delete $4; }
                | tEXTERN label     { $$ = new pf2asm::node::addressing::EXTERN (LINE, *$2); delete $2; }
                | tLABEL  label     { $$ = new pf2asm::node::addressing::LABEL  (LINE, *$2); delete $2; }
                | tADDR   label     { $$ = new pf2asm::node::addressing::ADDR   (LINE, *$2); delete $2; }
                | tADDRV  label     { $$ = new pf2asm::node::addressing::ADDRV  (LINE, *$2); delete $2; }
                | tADDRA  label     { $$ = new pf2asm::node::addressing::ADDRA  (LINE, *$2); delete $2; }
                ;

offset          : integer         { $$ = $1; };
label           : T_ID            { $$ = $1; };
type            : T_ID            { $$ = $1; };

function        : tENTER bytes   { $$ = new pf2asm::node::function::ENTER(LINE, $2); }
                | tSTART         { $$ = new pf2asm::node::function::START(LINE);   }
                | tLEAVE         { $$ = new pf2asm::node::function::LEAVE(LINE);   }
                | tCALL  label   { $$ = new pf2asm::node::function::CALL(LINE, *$2); delete $2; }
                | tRET           { $$ = new pf2asm::node::function::RET(LINE);     }
                | tRETN  bytes   { $$ = new pf2asm::node::function::RETN(LINE, $2);  }
                | tPUSH          { $$ = new pf2asm::node::function::PUSH(LINE);    }
                | tPOP           { $$ = new pf2asm::node::function::POP(LINE);     }
                | tDPUSH         { $$ = new pf2asm::node::function::DPUSH(LINE);   }
                | tDPOP          { $$ = new pf2asm::node::function::DPOP(LINE);    }
                ;

loadstore       : tULDCHR        { $$ = new pf2asm::node::loadstore::ULDCHR(LINE); }
                | tULD16         { $$ = new pf2asm::node::loadstore::ULD16(LINE);  }
                | tLOAD          { $$ = new pf2asm::node::loadstore::LOAD(LINE);   }
                | tSTORE         { $$ = new pf2asm::node::loadstore::STORE(LINE);  }
                | tLDCHR         { $$ = new pf2asm::node::loadstore::LDCHR(LINE);  }
                | tSTCHR         { $$ = new pf2asm::node::loadstore::STCHR(LINE);  }
                | tLD16          { $$ = new pf2asm::node::loadstore::LD16(LINE);   }
                | tST16          { $$ = new pf2asm::node::loadstore::ST16(LINE);   }
                | tDLOAD         { $$ = new pf2asm::node::loadstore::DLOAD(LINE);  }
                | tDSTORE        { $$ = new pf2asm::node::loadstore::DSTORE(LINE); }
                ;

arithmetic      : tADD           { $$ = new pf2asm::node::arithmetic::ADD(LINE);  }
                | tSUB           { $$ = new pf2asm::node::arithmetic::SUB(LINE);  }
                | tMUL           { $$ = new pf2asm::node::arithmetic::MUL(LINE);  }
                | tDIV           { $$ = new pf2asm::node::arithmetic::DIV(LINE);  }
                | tMOD           { $$ = new pf2asm::node::arithmetic::MOD(LINE);  }
                | tNEG           { $$ = new pf2asm::node::arithmetic::NEG(LINE);  }
                | tUDIV          { $$ = new pf2asm::node::arithmetic::UDIV(LINE); }
                | tUMOD          { $$ = new pf2asm::node::arithmetic::UMOD(LINE); }
                | tDADD          { $$ = new pf2asm::node::arithmetic::DADD(LINE); }
                | tDSUB          { $$ = new pf2asm::node::arithmetic::DSUB(LINE); }
                | tDMUL          { $$ = new pf2asm::node::arithmetic::DMUL(LINE); }
                | tDDIV          { $$ = new pf2asm::node::arithmetic::DDIV(LINE); }
                | tDNEG          { $$ = new pf2asm::node::arithmetic::DNEG(LINE); }
                ;
                
bitwise         : tROTL          { $$ = new pf2asm::node::bitwise::ROTL(LINE);  }
                | tROTR          { $$ = new pf2asm::node::bitwise::ROTR(LINE);  }
                | tSHTL          { $$ = new pf2asm::node::bitwise::SHTL(LINE);  }
                | tSHTRU         { $$ = new pf2asm::node::bitwise::SHTRU(LINE); }
                | tSHTRS         { $$ = new pf2asm::node::bitwise::SHTRS(LINE); }
                ;
                
logical         : tAND           { $$ = new pf2asm::node::logical::AND(LINE); }
                | tOR            { $$ = new pf2asm::node::logical::OR(LINE);  }
                | tXOR           { $$ = new pf2asm::node::logical::XOR(LINE); }
                | tNOT           { $$ = new pf2asm::node::logical::NOT(LINE); }
                ;

relational      : tGT            { $$ = new pf2asm::node::relational::GT(LINE);   }
                | tGE            { $$ = new pf2asm::node::relational::GE(LINE);   }
                | tLT            { $$ = new pf2asm::node::relational::LT(LINE);   }
                | tLE            { $$ = new pf2asm::node::relational::LE(LINE);   }
                | tEQ            { $$ = new pf2asm::node::relational::EQ(LINE);   }
                | tNE            { $$ = new pf2asm::node::relational::NE(LINE);   }
                | tUGT           { $$ = new pf2asm::node::relational::UGT(LINE);  }
                | tUGE           { $$ = new pf2asm::node::relational::UGE(LINE);  }
                | tULT           { $$ = new pf2asm::node::relational::ULT(LINE);  }
                | tULE           { $$ = new pf2asm::node::relational::ULE(LINE);  }
                | tDCMP          { $$ = new pf2asm::node::relational::DCMP(LINE); }
                ;

jumps           : tBRANCH           { $$ = new pf2asm::node::jumps::BRANCH (LINE); }
                | tLEAP             { $$ = new pf2asm::node::jumps::LEAP   (LINE); }
                | tJMP  label       { $$ = new pf2asm::node::jumps::JMP    (LINE, *$2); delete $2; }
                | tJZ   label       { $$ = new pf2asm::node::jumps::JZ     (LINE, *$2); delete $2; }
                | tJNZ  label       { $$ = new pf2asm::node::jumps::JNZ    (LINE, *$2); delete $2; }
                | tJEQ  label       { $$ = new pf2asm::node::jumps::JEQ    (LINE, *$2); delete $2; }
                | tJNE  label       { $$ = new pf2asm::node::jumps::JNE    (LINE, *$2); delete $2; }
                | tJGT  label       { $$ = new pf2asm::node::jumps::JGT    (LINE, *$2); delete $2; }
                | tJGE  label       { $$ = new pf2asm::node::jumps::JGE    (LINE, *$2); delete $2; }
                | tJLT  label       { $$ = new pf2asm::node::jumps::JLT    (LINE, *$2); delete $2; }
                | tJLE  label       { $$ = new pf2asm::node::jumps::JLE    (LINE, *$2); delete $2; }
                | tJUGT label       { $$ = new pf2asm::node::jumps::JUGT   (LINE, *$2); delete $2; }
                | tJUGE label       { $$ = new pf2asm::node::jumps::JUGE   (LINE, *$2); delete $2; }
                | tJULT label       { $$ = new pf2asm::node::jumps::JULT   (LINE, *$2); delete $2; }
                | tJULE label       { $$ = new pf2asm::node::jumps::JULE   (LINE, *$2); delete $2; }
                ;

integer         : T_LIT_INT                       { $$ = $1; }
                | integer  '+'  integer           { $$ = $1 +  $3; }
                | integer  '-'  integer           { $$ = $1 -  $3; }
                | integer  '*'  integer           { $$ = $1 *  $3; }
                | integer  '/'  integer           { $$ = $1 /  $3; }
                | integer  '%'  integer           { $$ = $1 %  $3; }
                | integer  '<'  integer           { $$ = $1 <  $3; }
                | integer T_LE  integer           { $$ = $1 <= $3; }
                | integer T_EQ  integer           { $$ = $1 == $3; }
                | integer T_GE  integer           { $$ = $1 >= $3; }
                | integer  '>'  integer           { $$ = $1 >  $3; }
                | integer T_NE  integer           { $$ = $1 != $3; }
                | '!' integer                     { $$ = !$2; }
                | '-' integer %prec T_UMINUS      { $$ = -$2; }
                | '+' integer %prec T_UMINUS      { $$ =  $2; }
                | '(' integer ')'                 { $$ =  $2; }
                | integer '?' integer ':' integer { $$ = $1 ? $3 : $5; }
                ;

%%
/*
 * $Log: PFParser.y,v $
 * Revision 1.8  2013/02/12 18:56:15  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.7  2012/02/19 20:30:16  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 * Revision 1.6  2009/05/09 17:36:56  david
 * Major node cleanup. Parser simplification.
 *
 * Revision 1.5  2009/05/09 16:29:34  david
 * Simplified some elements (integers and strings).
 *
 * Revision 1.4  2009/02/28 21:01:06  david
 * Minor cleanup.
 *
 * Revision 1.3  2009/02/28 19:58:03  david
 * Introduced integer expressions with literals only (i.e., no variables).
 * It is now possible to write 16*1024+8.
 *
 */
 