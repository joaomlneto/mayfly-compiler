// $Id: PFwriter.cpp,v 1.23 2013/02/12 18:56:17 david Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "semantics/PFwriter.h"
#include "nodes/all.h"

// must come after other #includes
#include "PFParser.tab.h"   /* token-based constants (from .y) */

//---------------------------------------------------------------------------
//          THIS IS THE POSTFIX CODE GENERATOR'S DEFINITION
//---------------------------------------------------------------------------

/**
 * A sequence in Postfix is simply a cycle through its items.
 * @param node the node representing the sequence.
 * @param lvl the syntax tree level
 */
void ps::PFwriter::processSequence(cdk::node::Sequence *const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) node->node(i)->accept(this, lvl);
}

//===========================================================================

void ps::PFwriter::processNOP(pn::NOP *node, int level) { _pf.NOP(); }
void ps::PFwriter::processINCR(pn::INCR *node, int level) { _pf.INCR(node->value()); }
void ps::PFwriter::processDECR(pn::DECR *node, int level) { _pf.DECR(node->value()); }
void ps::PFwriter::processALLOC(pn::ALLOC *node, int level) { _pf.ALLOC(); }
void ps::PFwriter::processTRASH(pn::TRASH *node, int level) { _pf.TRASH(node->value()); }
void ps::PFwriter::processDUP(pn::DUP *node, int level) { _pf.DUP(); }
void ps::PFwriter::processDDUP(pn::DDUP *node, int level) { _pf.DDUP(); }
void ps::PFwriter::processSWAP(pn::SWAP *node, int level) { _pf.SWAP(); }
void ps::PFwriter::processSP(pn::SP *node, int level) { _pf.SP(); }
void ps::PFwriter::processI2D(pn::I2D *node, int level) { _pf.I2D(); }
void ps::PFwriter::processF2D(pn::F2D *node, int level) { _pf.F2D(); }
void ps::PFwriter::processD2I(pn::D2I *node, int level) { _pf.D2I(); }
void ps::PFwriter::processD2F(pn::D2F *node, int level) { _pf.D2F(); }
void ps::PFwriter::processNIL(pn::NIL *node, int level) { _pf.NIL(); }

void ps::PFwriter::processCONST(pn::data::CONST *node, int level) { _pf.CONST(node->value()); }
void ps::PFwriter::processSTR(pn::data::STR *node, int level) { _pf.STR(node->value()); }
void ps::PFwriter::processCHAR(pn::data::CHAR *node, int level) { _pf.CHAR(node->value()[0]); }
void ps::PFwriter::processID(pn::data::ID *node, int level) { _pf.ID(node->value()); }
void ps::PFwriter::processBYTE(pn::data::BYTE *node, int level) { _pf.BYTE(node->value()); }
void ps::PFwriter::processINT(pn::data::INT *node, int level) { _pf.INT(node->value()); }
void ps::PFwriter::processFLOAT(pn::data::FLOAT *node, int level) { _pf.FLOAT(node->value()); }
void ps::PFwriter::processDOUBLE(pn::data::DOUBLE *node, int level) { _pf.DOUBLE(node->value()); }

void ps::PFwriter::processTEXT(pn::addressing::TEXT *node, int level) { _pf.TEXT(); }
void ps::PFwriter::processRODATA(pn::addressing::RODATA *node, int level) { _pf.RODATA(); }
void ps::PFwriter::processDATA(pn::addressing::DATA *node, int level) { _pf.DATA(); }
void ps::PFwriter::processBSS(pn::addressing::BSS *node, int level) { _pf.BSS(); }
void ps::PFwriter::processALIGN(pn::addressing::ALIGN *node, int level) { _pf.ALIGN(); }
void ps::PFwriter::processEXTERN(pn::addressing::EXTERN *node, int level) { _pf.EXTERN(node->label()); }
void ps::PFwriter::processCOMMON(pn::addressing::COMMON *node, int level) { _pf.COMMON(node->value()); }
void ps::PFwriter::processGLOBAL(pn::addressing::GLOBAL *node, int level) {
  _pf.GLOBAL(node->label(), (node->type() == "FUNC" ? _pf.FUNC() : _pf.OBJ()));
}
void ps::PFwriter::processLABEL(pn::addressing::LABEL *node, int level) { _pf.LABEL(node->label()); }
void ps::PFwriter::processLOCAL(pn::addressing::LOCAL *node, int level) { _pf.LOCAL(node->offset()); }
void ps::PFwriter::processADDR(pn::addressing::ADDR *node, int level) { _pf.ADDR(node->label()); }
void ps::PFwriter::processLOCV(pn::addressing::LOCV *node, int level) { _pf.LOCV(node->offset()); }
void ps::PFwriter::processADDRV(pn::addressing::ADDRV *node, int level) { _pf.ADDRV(node->label()); }
void ps::PFwriter::processLOCA(pn::addressing::LOCA *node, int level) { _pf.LOCA(node->offset()); }
void ps::PFwriter::processADDRA(pn::addressing::ADDRA *node, int level) { _pf.ADDRA(node->label()); }

void ps::PFwriter::processENTER(pn::function::ENTER *node, int level) { _pf.ENTER(node->value()); }
void ps::PFwriter::processSTART(pn::function::START *node, int level) { _pf.START(); }
void ps::PFwriter::processLEAVE(pn::function::LEAVE *node, int level) { _pf.LEAVE(); }
void ps::PFwriter::processCALL(pn::function::CALL *node, int level) { _pf.CALL(node->label()); }
void ps::PFwriter::processRET(pn::function::RET *node, int level) { _pf.RET(); }
void ps::PFwriter::processRETN(pn::function::RETN *node, int level) { _pf.RETN(node->value()); }
void ps::PFwriter::processPUSH(pn::function::PUSH *node, int level) { _pf.PUSH(); }
void ps::PFwriter::processPOP(pn::function::POP *node, int level) { _pf.POP(); }
void ps::PFwriter::processDPUSH(pn::function::DPUSH *node, int level) { _pf.DPUSH(); }
void ps::PFwriter::processDPOP(pn::function::DPOP *node, int level) { _pf.DPOP(); }

void ps::PFwriter::processULDCHR(pn::loadstore::ULDCHR *node, int level) { _pf.ULDCHR(); }
void ps::PFwriter::processULD16(pn::loadstore::ULD16 *node, int level) { _pf.ULD16(); }
void ps::PFwriter::processLOAD(pn::loadstore::LOAD *node, int level) { _pf.LOAD(); }
void ps::PFwriter::processSTORE(pn::loadstore::STORE *node, int level) { _pf.STORE(); }
void ps::PFwriter::processLDCHR(pn::loadstore::LDCHR *node, int level) { _pf.LDCHR(); }
void ps::PFwriter::processSTCHR(pn::loadstore::STCHR *node, int level) { _pf.STCHR(); }
void ps::PFwriter::processLD16(pn::loadstore::LD16 *node, int level) { _pf.LD16(); }
void ps::PFwriter::processST16(pn::loadstore::ST16 *node, int level) { _pf.ST16(); }
void ps::PFwriter::processDLOAD(pn::loadstore::DLOAD *node, int level) { _pf.DLOAD(); }
void ps::PFwriter::processDSTORE(pn::loadstore::DSTORE *node, int level) { _pf.DSTORE(); }

void ps::PFwriter::processADD(pn::arithmetic::ADD *node, int level) { _pf.ADD(); }
void ps::PFwriter::processSUB(pn::arithmetic::SUB *node, int level) { _pf.SUB(); }
void ps::PFwriter::processMUL(pn::arithmetic::MUL *node, int level) { _pf.MUL(); }
void ps::PFwriter::processDIV(pn::arithmetic::DIV *node, int level) { _pf.DIV(); }
void ps::PFwriter::processMOD(pn::arithmetic::MOD *node, int level) { _pf.MOD(); }
void ps::PFwriter::processNEG(pn::arithmetic::NEG *node, int level) { _pf.NEG(); }
void ps::PFwriter::processUDIV(pn::arithmetic::UDIV *node, int level) { _pf.UDIV(); }
void ps::PFwriter::processUMOD(pn::arithmetic::UMOD *node, int level) { _pf.UMOD(); }
void ps::PFwriter::processDADD(pn::arithmetic::DADD *node, int level) { _pf.DADD(); }
void ps::PFwriter::processDSUB(pn::arithmetic::DSUB *node, int level) { _pf.DSUB(); }
void ps::PFwriter::processDMUL(pn::arithmetic::DMUL *node, int level) { _pf.DMUL(); }
void ps::PFwriter::processDDIV(pn::arithmetic::DDIV *node, int level) { _pf.DDIV(); }
void ps::PFwriter::processDNEG(pn::arithmetic::DNEG *node, int level) { _pf.DNEG(); }

void ps::PFwriter::processROTL(pn::bitwise::ROTL *node, int level) { _pf.ROTL(); }
void ps::PFwriter::processROTR(pn::bitwise::ROTR *node, int level) { _pf.ROTR(); }
void ps::PFwriter::processSHTL(pn::bitwise::SHTL *node, int level) { _pf.SHTL(); }
void ps::PFwriter::processSHTRU(pn::bitwise::SHTRU *node, int level) { _pf.SHTRU(); }
void ps::PFwriter::processSHTRS(pn::bitwise::SHTRS *node, int level) { _pf.SHTRS(); }

void ps::PFwriter::processAND(pn::logical::AND *node, int level) { _pf.AND(); }
void ps::PFwriter::processOR(pn::logical::OR *node, int level) { _pf.OR(); }
void ps::PFwriter::processXOR(pn::logical::XOR *node, int level) { _pf.XOR(); }
void ps::PFwriter::processNOT(pn::logical::NOT *node, int level) { _pf.NOT(); }

void ps::PFwriter::processGT(pn::relational::GT *node, int level) { _pf.GT(); }
void ps::PFwriter::processGE(pn::relational::GE *node, int level) { _pf.GE(); }
void ps::PFwriter::processLT(pn::relational::LT *node, int level) { _pf.LT(); }
void ps::PFwriter::processLE(pn::relational::LE *node, int level) { _pf.LE(); }
void ps::PFwriter::processEQ(pn::relational::EQ *node, int level) { _pf.EQ(); }
void ps::PFwriter::processNE(pn::relational::NE *node, int level) { _pf.NE(); }
void ps::PFwriter::processUGT(pn::relational::UGT *node, int level) { _pf.UGT(); }
void ps::PFwriter::processUGE(pn::relational::UGE *node, int level) { _pf.UGE(); }
void ps::PFwriter::processULT(pn::relational::ULT *node, int level) { _pf.ULT(); }
void ps::PFwriter::processULE(pn::relational::ULE *node, int level) { _pf.ULE(); }
void ps::PFwriter::processDCMP(pn::relational::DCMP *node, int level) { _pf.DCMP(); }

void ps::PFwriter::processBRANCH(pn::jumps::BRANCH *node, int level) { _pf.BRANCH(); }
void ps::PFwriter::processLEAP  (pn::jumps::LEAP   *node, int level) { _pf.LEAP(); }
void ps::PFwriter::processJMP   (pn::jumps::JMP    *node, int level) { _pf.JMP(node->label()); }
void ps::PFwriter::processJZ    (pn::jumps::JZ     *node, int level) { _pf.JZ(node->label()); }
void ps::PFwriter::processJNZ   (pn::jumps::JNZ    *node, int level) { _pf.JNZ(node->label()); }
void ps::PFwriter::processJEQ   (pn::jumps::JEQ    *node, int level) { _pf.JEQ(node->label()); }
void ps::PFwriter::processJNE   (pn::jumps::JNE    *node, int level) { _pf.JNE(node->label()); }
void ps::PFwriter::processJGT   (pn::jumps::JGT    *node, int level) { _pf.JGT(node->label()); }
void ps::PFwriter::processJGE   (pn::jumps::JGE    *node, int level) { _pf.JGE(node->label()); }
void ps::PFwriter::processJLT   (pn::jumps::JLT    *node, int level) { _pf.JLT(node->label()); }
void ps::PFwriter::processJLE   (pn::jumps::JLE    *node, int level) { _pf.JLE(node->label()); }
void ps::PFwriter::processJUGT  (pn::jumps::JUGT   *node, int level) { _pf.JUGT(node->label()); }
void ps::PFwriter::processJUGE  (pn::jumps::JUGE   *node, int level) { _pf.JUGE(node->label()); }
void ps::PFwriter::processJULT  (pn::jumps::JULT   *node, int level) { _pf.JULT(node->label()); }
void ps::PFwriter::processJULE  (pn::jumps::JULE   *node, int level) { _pf.JULE(node->label()); }

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
/*
 * $Log: PFwriter.cpp,v $
 * Revision 1.23  2013/02/12 18:56:17  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.22  2012/02/19 20:30:16  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 * Revision 1.21  2009/05/09 16:23:46  david
 * Misc cleanup.
 *
 * Revision 1.20  2009/03/02 13:26:51  david
 * Code cleanup. Removed a few minor warnings.
 *
 * Revision 1.19  2009/02/28 21:01:06  david
 * Minor cleanup.
 *
 * Revision 1.18  2009/02/25 07:31:57  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 *
 */
