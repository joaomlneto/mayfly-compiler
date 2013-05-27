// $Id: PFwriter.h,v 1.16 2012/02/19 20:30:16 david Exp $ -*- c++ -*-
/*
 * $Log: PFwriter.h,v $
 * Revision 1.16  2012/02/19 20:30:16  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 * Revision 1.15  2011/03/06 14:53:19  david
 * Ported to CDK6.
 *
 * Revision 1.14  2009/05/09 16:23:46  david
 * Misc cleanup.
 *
 * Revision 1.13  2009/03/02 13:26:51  david
 * Code cleanup. Removed a few minor warnings.
 *
 * Revision 1.12  2009/03/01 20:45:10  david
 * The symbol table now needs a symbol type. In this case, and
 * given the simplicity of this compiler, symbols are just strings.
 * This may change in future revisions.
 *
 * Revision 1.11  2009/02/28 21:01:07  david
 * Minor cleanup.
 *
 * Revision 1.10  2009/02/27 01:39:54  david
 * First test with structures and C compatibility.
 *
 * Revision 1.9  2009/02/25 07:31:57  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 * Revision 1.8  2009/02/23 20:53:38  david
 * First PF implementation. Does not work with PF syntax nor
 * does it do anything useful.
 *
 */

#ifndef __NX6_SEMANTICS_PFWRITER_H__
#define __NX6_SEMANTICS_PFWRITER_H__

#include "semantics/SemanticProcessor.h"

#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/generators/Postfix.h>

/**
 * Traverse syntax tree and generate the corresponding PF code.
 * Note that no attempt is made to validate symbols (the assembly
 * parser -- nasm, yasm, etc. -- will do that).
 */

namespace pf2asm {
  namespace semantics {

    class PFwriter: public virtual SemanticProcessor {
      cdk::semantics::SymbolTable<std::string> &_symtab; // not used

      // code generation
      cdk::generator::Postfix &_pf;

      // counter for automatic labels
      int _lbl;

      // current framepointer offset (0 means no vars defined)
      int _offset;

      // semantic analysis errors
      bool _errors;

    public:
      PFwriter(std::ostream &os, bool debug, cdk::semantics::SymbolTable<std::string> &symtab,
               cdk::generator::Postfix &pf) :
        SemanticProcessor(os, debug), _symtab(symtab), _pf(pf), _lbl(0), _offset(0), _errors(false) {
      }

    public:
      inline ~PFwriter() {
        os().flush();
      }

    private:
      std::string mklbl(int lbl) {
        std::ostringstream oss;
        if (lbl < 0)
          oss << ".L" << -lbl;
        else
          oss << "_L" << lbl;
        return oss.str();
      }

      void error(int lineno, std::string s) {
        std::cerr << "error: " << lineno << ": " << s << std::endl;
      }

    public:
      visig(cdk::node, Node) {
      }
      visig(cdk::node, Nil) {
      }
      visig(cdk::node, Composite) {
        throw 42;
      }
      visig(cdk::node, Sequence);visig(cdk::node, Data) {
        throw 42;
      }

      template<typename T> void processSimple(cdk::node::expression::Simple<T> * const node,
                                              int lvl) {
        throw 42;
      }
      visig(cdk::node::expression, Double) {
        throw 42;
      }
      visig(cdk::node::expression, Integer) {
        throw 42;
      }
      visig(cdk::node::expression, String) {
        throw 42;
      }
      visig(cdk::node::expression, Identifier) {
        throw 42;
      }

      visig(cdk::node::expression, UnaryExpression) {
        throw 42;
      }
      visig(cdk::node::expression, NEG) {
        throw 42;
      }

      visig(cdk::node::expression, BinaryExpression) {
        throw 42;
      }
      visig(cdk::node::expression, ADD) {
        throw 42;
      }
      visig(cdk::node::expression, DIV) {
        throw 42;
      }
      visig(cdk::node::expression, MOD) {
        throw 42;
      }
      visig(cdk::node::expression, MUL) {
        throw 42;
      }
      visig(cdk::node::expression, SUB) {
        throw 42;
      }
      visig(cdk::node::expression, EQ) {
        throw 42;
      }
      visig(cdk::node::expression, GE) {
        throw 42;
      }
      visig(cdk::node::expression, GT) {
        throw 42;
      }
      visig(cdk::node::expression, LE) {
        throw 42;
      }
      visig(cdk::node::expression, LT) {
        throw 42;
      }
      visig(cdk::node::expression, NE) {
        throw 42;
      }

    public:
      // postfix keyword nodes

      visig(pn, NOP);
      visig(pn, INCR);
      visig(pn, DECR);
      visig(pn, ALLOC);
      visig(pn, TRASH);
      visig(pn, DUP);
      visig(pn, DDUP);
      visig(pn, SWAP);
      visig(pn, SP);
      visig(pn, I2D);
      visig(pn, F2D);
      visig(pn, D2I);
      visig(pn, D2F);
      visig(pn, NIL);

      visig(pn::data, CONST);
      visig(pn::data, STR);
      visig(pn::data, CHAR);
      visig(pn::data, ID);
      visig(pn::data, BYTE);
      visig(pn::data, INT);
      visig(pn::data, FLOAT);
      visig(pn::data, DOUBLE);

      visig(pn::addressing, TEXT);
      visig(pn::addressing, RODATA);
      visig(pn::addressing, DATA);
      visig(pn::addressing, BSS);
      visig(pn::addressing, ALIGN);
      visig(pn::addressing, EXTERN);
      visig(pn::addressing, COMMON);
      visig(pn::addressing, GLOBAL);
      visig(pn::addressing, LABEL);
      visig(pn::addressing, LOCAL);
      visig(pn::addressing, ADDR);
      visig(pn::addressing, LOCV);
      visig(pn::addressing, ADDRV);
      visig(pn::addressing, LOCA);
      visig(pn::addressing, ADDRA);

      visig(pn::function, ENTER);
      visig(pn::function, START);
      visig(pn::function, LEAVE);
      visig(pn::function, CALL);
      visig(pn::function, RET);
      visig(pn::function, RETN);
      visig(pn::function, PUSH);
      visig(pn::function, POP);
      visig(pn::function, DPUSH);
      visig(pn::function, DPOP);

      visig(pn::loadstore, ULDCHR);
      visig(pn::loadstore, ULD16);
      visig(pn::loadstore, LOAD);
      visig(pn::loadstore, STORE);
      visig(pn::loadstore, LDCHR);
      visig(pn::loadstore, STCHR);
      visig(pn::loadstore, LD16);
      visig(pn::loadstore, ST16);
      visig(pn::loadstore, DLOAD);
      visig(pn::loadstore, DSTORE);

      visig(pn::arithmetic, ADD);
      visig(pn::arithmetic, SUB);
      visig(pn::arithmetic, MUL);
      visig(pn::arithmetic, DIV);
      visig(pn::arithmetic, MOD);
      visig(pn::arithmetic, NEG);
      visig(pn::arithmetic, UDIV);
      visig(pn::arithmetic, UMOD);
      visig(pn::arithmetic, DADD);
      visig(pn::arithmetic, DSUB);
      visig(pn::arithmetic, DMUL);
      visig(pn::arithmetic, DDIV);
      visig(pn::arithmetic, DNEG);

      visig(pn::bitwise, ROTL);
      visig(pn::bitwise, ROTR);
      visig(pn::bitwise, SHTL);
      visig(pn::bitwise, SHTRU);
      visig(pn::bitwise, SHTRS);

      visig(pn::logical, AND);
      visig(pn::logical, OR);
      visig(pn::logical, XOR);
      visig(pn::logical, NOT);

      visig(pn::relational, GT);
      visig(pn::relational, GE);
      visig(pn::relational, LT);
      visig(pn::relational, LE);
      visig(pn::relational, EQ);
      visig(pn::relational, NE);
      visig(pn::relational, UGT);
      visig(pn::relational, UGE);
      visig(pn::relational, ULT);
      visig(pn::relational, ULE);
      visig(pn::relational, DCMP);

      visig(pn::jumps, BRANCH);
      visig(pn::jumps, LEAP);
      visig(pn::jumps, JMP);
      visig(pn::jumps, JZ);
      visig(pn::jumps, JNZ);
      visig(pn::jumps, JEQ);
      visig(pn::jumps, JNE);
      visig(pn::jumps, JGT);
      visig(pn::jumps, JGE);
      visig(pn::jumps, JLT);
      visig(pn::jumps, JLE);
      visig(pn::jumps, JUGT);
      visig(pn::jumps, JUGE);
      visig(pn::jumps, JULT);
      visig(pn::jumps, JULE);

    }; // class PFwriter

  } // namespace semantics
} // namespace pf2asm

#endif
