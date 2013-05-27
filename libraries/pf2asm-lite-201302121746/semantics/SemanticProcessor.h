// $Id: SemanticProcessor.h,v 1.12 2013/02/12 18:56:17 david Exp $ -*- c++ -*-
#ifndef __PF2ASM_SEMANTICS_SEMANTICPROCESSOR_H__
#define __PF2ASM_SEMANTICS_SEMANTICPROCESSOR_H__

#include <string>
#include <iostream>

/* include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "nodes/all.h"
#undef __NODE_DECLARATIONS_ONLY__

// shorthand notations:
namespace ps = pf2asm::semantics;
namespace pn = pf2asm::node;

#define visig(nsp, nodeType) void process##nodeType(nsp::nodeType *const node, int lvl)

/**
 * Base class of the hierarchy of visitor nodes.
 */
class SemanticProcessor {
  //! The output stream
  std::ostream &_os;

protected:
  bool _debug;

protected:
  SemanticProcessor(std::ostream &os = std::cout, bool debug = false) :
      _os(os), _debug(debug) {
  }
  inline std::ostream &os() {
    return _os;
  }

public:
  virtual ~SemanticProcessor() {
  }

public:
  virtual visig(cdk::node, Nil) = 0;
  virtual visig(cdk::node, Composite)= 0;
  virtual visig(cdk::node, Sequence)= 0;
  virtual visig(cdk::node, Data)= 0;

  virtual visig(cdk::node::expression, Double)= 0;
  virtual visig(cdk::node::expression, Integer)= 0;
  virtual visig(cdk::node::expression, String)= 0;
  virtual visig(cdk::node::expression, Identifier)= 0;

  virtual visig(cdk::node::expression, NEG) = 0;

  virtual visig(cdk::node::expression, ADD) = 0;
  virtual visig(cdk::node::expression, DIV) = 0;
  virtual visig(cdk::node::expression, MOD) = 0;
  virtual visig(cdk::node::expression, MUL) = 0;
  virtual visig(cdk::node::expression, SUB) = 0;
  virtual visig(cdk::node::expression, EQ) = 0;
  virtual visig(cdk::node::expression, GE) = 0;
  virtual visig(cdk::node::expression, GT) = 0;
  virtual visig(cdk::node::expression, LE) = 0;
  virtual visig(cdk::node::expression, LT) = 0;
  virtual visig(cdk::node::expression, NE) = 0;

public: // postfix keyword nodes

  virtual visig(pn, NOP) = 0;
  virtual visig(pn, INCR) = 0;
  virtual visig(pn, DECR) = 0;
  virtual visig(pn, ALLOC) = 0;
  virtual visig(pn, TRASH) = 0;
  virtual visig(pn, DUP) = 0;
  virtual visig(pn, DDUP) = 0;
  virtual visig(pn, SWAP) = 0;
  virtual visig(pn, SP) = 0;
  virtual visig(pn, I2D) = 0;
  virtual visig(pn, F2D) = 0;
  virtual visig(pn, D2I) = 0;
  virtual visig(pn, D2F) = 0;
  virtual visig(pn, NIL) = 0;

  virtual visig(pn::data, CONST) = 0;
  virtual visig(pn::data, STR) = 0;
  virtual visig(pn::data, CHAR) = 0;
  virtual visig(pn::data, ID) = 0;
  virtual visig(pn::data, BYTE) = 0;
  virtual visig(pn::data, INT) = 0;
  virtual visig(pn::data, FLOAT) = 0;
  virtual visig(pn::data, DOUBLE) = 0;

  virtual visig(pn::addressing, TEXT) = 0;
  virtual visig(pn::addressing, RODATA) = 0;
  virtual visig(pn::addressing, DATA) = 0;
  virtual visig(pn::addressing, BSS) = 0;
  virtual visig(pn::addressing, ALIGN) = 0;
  virtual visig(pn::addressing, EXTERN) = 0;
  virtual visig(pn::addressing, COMMON) = 0;
  virtual visig(pn::addressing, GLOBAL) = 0;
  virtual visig(pn::addressing, LABEL) = 0;
  virtual visig(pn::addressing, LOCAL) = 0;
  virtual visig(pn::addressing, ADDR) = 0;
  virtual visig(pn::addressing, LOCV) = 0;
  virtual visig(pn::addressing, ADDRV) = 0;
  virtual visig(pn::addressing, LOCA) = 0;
  virtual visig(pn::addressing, ADDRA) = 0;

  virtual visig(pn::function, ENTER) = 0;
  virtual visig(pn::function, START) = 0;
  virtual visig(pn::function, LEAVE) = 0;
  virtual visig(pn::function, CALL) = 0;
  virtual visig(pn::function, RET) = 0;
  virtual visig(pn::function, RETN) = 0;
  virtual visig(pn::function, PUSH) = 0;
  virtual visig(pn::function, POP) = 0;
  virtual visig(pn::function, DPUSH) = 0;
  virtual visig(pn::function, DPOP) = 0;

  virtual visig(pn::loadstore, ULDCHR) = 0;
  virtual visig(pn::loadstore, ULD16) = 0;
  virtual visig(pn::loadstore, LOAD) = 0;
  virtual visig(pn::loadstore, STORE) = 0;
  virtual visig(pn::loadstore, LDCHR) = 0;
  virtual visig(pn::loadstore, STCHR) = 0;
  virtual visig(pn::loadstore, LD16) = 0;
  virtual visig(pn::loadstore, ST16) = 0;
  virtual visig(pn::loadstore, DLOAD) = 0;
  virtual visig(pn::loadstore, DSTORE) = 0;

  virtual visig(pn::arithmetic, ADD) = 0;
  virtual visig(pn::arithmetic, SUB) = 0;
  virtual visig(pn::arithmetic, MUL) = 0;
  virtual visig(pn::arithmetic, DIV) = 0;
  virtual visig(pn::arithmetic, MOD) = 0;
  virtual visig(pn::arithmetic, NEG) = 0;
  virtual visig(pn::arithmetic, UDIV) = 0;
  virtual visig(pn::arithmetic, UMOD) = 0;
  virtual visig(pn::arithmetic, DADD) = 0;
  virtual visig(pn::arithmetic, DSUB) = 0;
  virtual visig(pn::arithmetic, DMUL) = 0;
  virtual visig(pn::arithmetic, DDIV) = 0;
  virtual visig(pn::arithmetic, DNEG) = 0;

  virtual visig(pn::bitwise, ROTL) = 0;
  virtual visig(pn::bitwise, ROTR) = 0;
  virtual visig(pn::bitwise, SHTL) = 0;
  virtual visig(pn::bitwise, SHTRU) = 0;
  virtual visig(pn::bitwise, SHTRS) = 0;

  virtual visig(pn::logical, AND) = 0;
  virtual visig(pn::logical, OR) = 0;
  virtual visig(pn::logical, XOR) = 0;
  virtual visig(pn::logical, NOT) = 0;

  virtual visig(pn::relational, GT) = 0;
  virtual visig(pn::relational, GE) = 0;
  virtual visig(pn::relational, LT) = 0;
  virtual visig(pn::relational, LE) = 0;
  virtual visig(pn::relational, EQ) = 0;
  virtual visig(pn::relational, NE) = 0;
  virtual visig(pn::relational, UGT) = 0;
  virtual visig(pn::relational, UGE) = 0;
  virtual visig(pn::relational, ULT) = 0;
  virtual visig(pn::relational, ULE) = 0;
  virtual visig(pn::relational, DCMP) = 0;

  virtual visig(pn::jumps, BRANCH) = 0;
  virtual visig(pn::jumps, LEAP) = 0;
  virtual visig(pn::jumps, JMP) = 0;
  virtual visig(pn::jumps, JZ) = 0;
  virtual visig(pn::jumps, JNZ) = 0;
  virtual visig(pn::jumps, JEQ) = 0;
  virtual visig(pn::jumps, JNE) = 0;
  virtual visig(pn::jumps, JGT) = 0;
  virtual visig(pn::jumps, JGE) = 0;
  virtual visig(pn::jumps, JLT) = 0;
  virtual visig(pn::jumps, JLE) = 0;
  virtual visig(pn::jumps, JUGT) = 0;
  virtual visig(pn::jumps, JUGE) = 0;
  virtual visig(pn::jumps, JULT) = 0;
  virtual visig(pn::jumps, JULE) = 0;

};

#endif

/*
 * $Log: SemanticProcessor.h,v $
 * Revision 1.12  2013/02/12 18:56:17  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.11  2012/02/19 20:30:16  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 * Revision 1.10  2009/02/28 21:01:07  david
 * Minor cleanup.
 *
 * Revision 1.9  2009/02/25 07:31:57  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 *
 */
