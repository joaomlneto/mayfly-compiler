// $Id: SemanticProcessor.h,v 1.18 2013-05-13 19:10:06 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_SEMANTICPROCESSOR_H__
#define __MF_SEMANTICS_SEMANTICPROCESSOR_H__

#include <string>
#include <iostream>

/* include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "nodes/all.h"  // automatically generated
#undef __NODE_DECLARATIONS_ONLY__

//!
//! Print nodes as XML elements to the output stream.
//!
class SemanticProcessor {
  //! The output stream
  std::ostream &_os;

protected:
  //! Debug flag
  bool _debug;

protected:
  SemanticProcessor(std::ostream &o = std::cout, bool debug = false) :
      _os(o), _debug(debug) {
  }
  inline std::ostream &os() {
    return _os;
  }

public:
  virtual ~SemanticProcessor() {
  }

public:
  // CDK nodes (general)
  virtual void processNil(cdk::node::Nil * const node, int lvl) = 0;
  virtual void processData(cdk::node::Data * const node, int lvl) = 0;
  virtual void processComposite(cdk::node::Composite * const node, int lvl) = 0;
  virtual void processSequence(cdk::node::Sequence * const node, int lvl) = 0;

public:
  virtual void processInteger(cdk::node::expression::Integer * const node, int lvl) = 0;
  virtual void processDouble(cdk::node::expression::Double * const node, int lvl) = 0;
  virtual void processString(cdk::node::expression::String * const node, int lvl) = 0;
  virtual void processIdentifier(cdk::node::expression::Identifier * const node, int lvl) = 0;

public:
  virtual void processNEG(cdk::node::expression::NEG * const node, int lvl) = 0;

public:
  virtual void processADD(cdk::node::expression::ADD * const node, int lvl) = 0;
  virtual void processSUB(cdk::node::expression::SUB * const node, int lvl) = 0;
  virtual void processMUL(cdk::node::expression::MUL * const node, int lvl) = 0;
  virtual void processDIV(cdk::node::expression::DIV * const node, int lvl) = 0;
  virtual void processMOD(cdk::node::expression::MOD * const node, int lvl) = 0;
  virtual void processLT(cdk::node::expression::LT * const node, int lvl) = 0;
  virtual void processLE(cdk::node::expression::LE * const node, int lvl) = 0;
  virtual void processGE(cdk::node::expression::GE * const node, int lvl) = 0;
  virtual void processGT(cdk::node::expression::GT * const node, int lvl) = 0;
  virtual void processNE(cdk::node::expression::NE * const node, int lvl) = 0;
  virtual void processEQ(cdk::node::expression::EQ * const node, int lvl) = 0;

public:
  // Mayfly-specific expressions and left-values
  virtual void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl) = 0;
  virtual void processAddressing(mayfly::node::expression::Addressing * const node, int lvl) = 0;
  virtual void processAND(mayfly::node::expression::AND * const node, int lvl) = 0;
  virtual void processAssignment(mayfly::node::expression::Assignment * const node, int lvl) = 0;
  virtual void processDecrement(mayfly::node::expression::Decrement * const node, int lvl) = 0;
  virtual void processIncrement(mayfly::node::expression::Increment * const node, int lvl) = 0;
  virtual void processIndexing(mayfly::node::expression::Indexing * const node, int lvl) = 0;
  virtual void processMemoryReservation(mayfly::node::expression::MemoryReservation * const node, int lvl) = 0;
  virtual void processNOT(mayfly::node::expression::NOT * const node, int lvl) = 0;
  virtual void processOR(mayfly::node::expression::OR * const node, int lvl) = 0;
  virtual void processRead(mayfly::node::expression::Read * const node, int lvl) = 0;
  virtual void processFunctionCall(mayfly::node::expression::FunctionCall * const node, int lvl) = 0;
  virtual void processIdentity(mayfly::node::expression::Identity * const node, int lvl) = 0;
  virtual void processExpressionAsInstruction(mayfly::node::ExpressionAsInstruction * const node, int lvl) = 0;

public:
  // Other Mayfly-specific nodes
  virtual void processPrintNode(mayfly::node::PrintNode * const node, int lvl) = 0;
  virtual void processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl) = 0;
  virtual void processIfNode(mayfly::node::IfNode * const node, int lvl) = 0;
  virtual void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl) = 0;
  virtual void processBreakNode(mayfly::node::BreakNode * const node, int lvl) = 0;
  virtual void processContinueNode(mayfly::node::ContinueNode * const node, int lvl) = 0;
  virtual void processReturnNode(mayfly::node::ReturnNode * const node, int lvl) = 0;
  virtual void processForUpToNode(mayfly::node::ForUpToNode * const node, int lvl) = 0;
  virtual void processForDownToNode(mayfly::node::ForDownToNode * const node, int lvl) = 0;
  virtual void processBlock(mayfly::node::Block * const node, int lvl) = 0;
  virtual void processVariableDeclaration(mayfly::node::VariableDeclaration * const node, int lvl) = 0;
  virtual void processFunctionDeclaration(mayfly::node::FunctionDeclaration * const node, int lvl) = 0;
  virtual void processFunctionDefinition(mayfly::node::FunctionDefinition * const node, int lvl) = 0;

};

#endif

// $Log: SemanticProcessor.h,v $
// Revision 1.18  2013-05-13 19:10:06  ist164787
// ExpressionAsInstruction node added
//
// Revision 1.17  2013-05-13 15:52:44  ist164787
// Added some more methods to TypeValidator
//
// Revision 1.16  2013-04-24 10:48:10  ist164787
// Removed Function Argument, misc minor changes
//
// Revision 1.15  2013-04-16 18:54:09  ist164787
// Added a new node: FunctionArgument. This represents an argument in a function declaration/definition
// Syntax tree is now being built (not tested)
//
// Revision 1.14  2013-04-14 20:59:23  ist164787
// MAJOR CHANGES in .y and .l and some XMLwriter.cpp; The return of LeftValue expression node
//
// Revision 1.13  2013-03-26 11:12:33  ist164787
// Removed unused Compact nodes
//
// Revision 1.12  2013-03-26 10:46:29  ist164787
// Removed Pointer expression node
//
// Revision 1.11  2013-03-25 19:13:20  ist164787
// Added FunctionDefinition node
//
// Revision 1.10  2013-03-25 19:07:17  ist164787
// Added FunctionDeclaration node
//
// Revision 1.9  2013-03-25 18:55:44  ist164787
// Added VariableDeclaration node
//
// Revision 1.8  2013-03-25 18:48:08  ist164787
// Added Block node
//
// Revision 1.7  2013-03-25 18:31:52  ist164787
// Removed ReadNode
//
// Revision 1.6  2013-03-25 18:03:26  ist164787
// added Break, Continue, Return, Node, ForUpTo, ForDownTo;\nRemoved ReadNode (instruction), WhileNode (is now DoWhileNode)
//
// Revision 1.5  2013-03-25 17:28:00  ist164787
// FunctionCall expression node added
//
// Revision 1.4  2013-03-25 17:17:15  ist164787
// Removed NOT expression node - theres already a NEG in CDK
//
// Revision 1.3  2013-03-25 12:16:19  ist164787
// Added the NOT unary operator node
//
// Revision 1.2  2013-03-25 12:08:59  ist164787
// Fixed semantics - it now compiles correctly again
//
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.12  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.11  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.10  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.9  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
