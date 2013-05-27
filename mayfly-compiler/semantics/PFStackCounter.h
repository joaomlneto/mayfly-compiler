// $Id: PFStackCounter.h,v 1.8 2013-05-17 16:18:53 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_PFSTACKCOUNTER_H__
#define __MF_SEMANTICS_PFSTACKCOUNTER_H__

#include <string>
#include <iostream>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/generators/Postfix.h>
#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"
#include "semantics/Symbol.h"

namespace mayfly {
  namespace semantics {

    //!
    //! Traverses part of the syntax tree and computes the necessary
	 //! stack space required for local variables in function definitions,
	 //! while also computing their offsets.
    //!
    class PFStackCounter: public virtual SemanticProcessor {
      // block declarations size (in bytes) is placed here after execution
      size_t _size;
    public:
      PFStackCounter(cdk::node::Node * const node) : SemanticProcessor(), _size(0) {
			node->accept(this, 0);
      }

    public:
      ~PFStackCounter() {
        os().flush();
      }
	
    public:
      unsigned long int size() {
        return _size;
      }
      void reset() {
        _size = 0;
      }

    public:
      void processNil(cdk::node::Nil * const node, int lvl) {}
      void processData(cdk::node::Data * const node, int lvl) {}
      void processComposite(cdk::node::Composite * const node, int lvl) {}
      void processSequence(cdk::node::Sequence * const node, int lvl);

    public:
      void processInteger(cdk::node::expression::Integer * const node, int lvl) {}
      void processDouble(cdk::node::expression::Double * const node, int lvl) {}
      void processString(cdk::node::expression::String * const node, int lvl) {}
      void processIdentifier(cdk::node::expression::Identifier * const node, int lvl) {} // NOT USED

    public:
      void processNEG(cdk::node::expression::NEG * const node, int lvl) {}

    public:
      void processADD(cdk::node::expression::ADD * const node, int lvl) {}
      void processSUB(cdk::node::expression::SUB * const node, int lvl) {}
      void processMUL(cdk::node::expression::MUL * const node, int lvl) {}
      void processDIV(cdk::node::expression::DIV * const node, int lvl) {}
      void processMOD(cdk::node::expression::MOD * const node, int lvl) {}
      void processLT(cdk::node::expression::LT * const node, int lvl) {}
      void processLE(cdk::node::expression::LE * const node, int lvl) {}
      void processGE(cdk::node::expression::GE * const node, int lvl) {}
      void processGT(cdk::node::expression::GT * const node, int lvl) {}
      void processNE(cdk::node::expression::NE * const node, int lvl) {}
      void processEQ(cdk::node::expression::EQ * const node, int lvl) {}

    public:
      void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl) {}
      void processAddressing(mayfly::node::expression::Addressing * const node, int lvl) {}
      void processAND(mayfly::node::expression::AND * const node, int lvl) {}
      void processAssignment(mayfly::node::expression::Assignment * const node, int lvl) {}
      void processDecrement(mayfly::node::expression::Decrement * const node, int lvl) {}
      void processIncrement(mayfly::node::expression::Increment * const node, int lvl) {}
      void processIndexing(mayfly::node::expression::Indexing * const node, int lvl) {}
      void processMemoryReservation(mayfly::node::expression::MemoryReservation * const node, int lvl) {}
      void processNOT(mayfly::node::expression::NOT * const node, int lvl) {}
      void processOR(mayfly::node::expression::OR * const node, int lvl) {}
      void processRead(mayfly::node::expression::Read * const node, int lvl) {}
      void processFunctionCall(mayfly::node::expression::FunctionCall * const node, int lvl);
      void processIdentity(mayfly::node::expression::Identity * const node, int lvl) {}
      void processExpressionAsInstruction(mayfly::node::ExpressionAsInstruction * const node, int lvl) {}

    public:
      void processPrintNode(mayfly::node::PrintNode * const node, int lvl) {}
      void processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl);
      void processIfNode(mayfly::node::IfNode * const node, int lvl);
      void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl);
      void processBreakNode(mayfly::node::BreakNode * const node, int lvl) {}
      void processContinueNode(mayfly::node::ContinueNode * const node, int lvl) {}
      void processReturnNode(mayfly::node::ReturnNode * const node, int lvl) {}
      void processForUpToNode(mayfly::node::ForUpToNode * const node, int lvl);
      void processForDownToNode(mayfly::node::ForDownToNode * const node, int lvl);
      void processBlock(mayfly::node::Block * const node, int lvl);
      void processVariableDeclaration(mayfly::node::VariableDeclaration * const node, int lvl);
      void processFunctionDeclaration(mayfly::node::FunctionDeclaration * const node, int lvl) {}
      void processFunctionDefinition(mayfly::node::FunctionDefinition * const node, int lvl);

    };

  }    // namespace semantics
} // namespace mayfly

#endif

// $Log: PFStackCounter.h,v $
// Revision 1.8  2013-05-17 16:18:53  ist164787
// Added missing methods in StackCounter - you can also declare variables in blocks that are in Whiles/Fors/Ifs...
//
// Revision 1.7  2013-05-16 21:03:41  ist164787
// Fixed when assigning integers to numbers
//
// Revision 1.6  2013-05-13 21:01:17  ist164787
// TypeValidator almost finished, Function Calls are full of awesome, printnode prints everything... other minor changes i dont remember
//
// Revision 1.5  2013-05-13 19:10:05  ist164787
// ExpressionAsInstruction node added
//
// Revision 1.4  2013-05-13 18:34:03  ist164787
// Fixed identifier and leftvalue confusion... added identity node for type validation... refactored typevalidator code
//
// Revision 1.3  2013-05-13 15:52:44  ist164787
// Added some more methods to TypeValidator
//
// Revision 1.2  2013-05-09 15:51:23  ist164787
// Small changes on FunctionDefinition and StackCounter
//
// Revision 1.1  2013-05-08 22:49:05  ist164787
// - Added StackCounter - a visitor to compute the necessary space for local
// variables (works for both functiondefinition and block nodes)
// - Removed unused dumb function in grammar file.y
//
//
