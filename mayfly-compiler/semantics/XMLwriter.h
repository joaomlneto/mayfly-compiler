// $Id: XMLwriter.h,v 1.19 2013-05-13 19:10:06 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_XMLWRITER_H__
#define __MF_SEMANTICS_XMLWRITER_H__

#include <string>
#include <iostream>
#include <cdk/nodes/Node.h>
#include <cdk/semantics/ExpressionType.h>
#include "semantics/SemanticProcessor.h"

namespace mayfly {
  namespace semantics {

    /**
     * Print nodes as XML elements to the output stream.
     */
    class XMLwriter: public virtual SemanticProcessor {

    public:
      XMLwriter(std::ostream &os = std::cout, bool debug = false) :
          SemanticProcessor(os, debug) {
      }

    public:
      ~XMLwriter() {
        os().flush();
      }

    private:
      inline void openTag(const std::string &tag, int lvl) {
        os() << std::string(lvl, ' ') + "<" + tag + ">" << std::endl;
      }
      inline void openTag(const cdk::node::Node *node, int lvl) {
        openTag(node->name(), lvl);
      }
      inline void closeTag(const std::string &tag, int lvl) {
        os() << std::string(lvl, ' ') + "</" + tag + ">" << std::endl;
      }
      inline void closeTag(const cdk::node::Node *node, int lvl) {
        closeTag(node->name(), lvl);
      }
		
		inline std::string type2str(ExpressionType *type) {
			switch(type->name()) {
				case ExpressionType::TYPE_INT: return "INTEGER"; break;
				case ExpressionType::TYPE_DOUBLE: return "NUMBER"; break;
				case ExpressionType::TYPE_BOOLEAN: return "BOOLEAN"; break; /* not in mayfly */
				case ExpressionType::TYPE_STRING: return "STRING"; break;
				case ExpressionType::TYPE_STRUCT: return "STRUCT"; break; /* not in mayfly */
				case ExpressionType::TYPE_VOID: return "VOID"; break;
				case ExpressionType::TYPE_ERROR: return "ERROR"; break;
				case ExpressionType::TYPE_POINTER:
					return ("*" + type2str(type->subtype()));
			}
			return "UNSPECIFIED";
		}
		inline void printType(ExpressionType *type) {
			os() << type2str(type);
		}

    public:
      void processNil(cdk::node::Nil * const node, int lvl) {
      }
      void processData(cdk::node::Data * const node, int lvl);
      void processComposite(cdk::node::Composite * const node, int lvl);
      void processSequence(cdk::node::Sequence * const node, int lvl);

    protected:
      template<typename T>
      void processSimple(cdk::node::expression::Simple<T> * const node, int lvl) {
        os() << std::string(lvl, ' ') << "<" << node->name() << ">" << node->value() << "</" << node->name() << ">" << std::endl;
      }

    public:
      void processInteger(cdk::node::expression::Integer * const node, int lvl);
      void processDouble(cdk::node::expression::Double * const node, int lvl);
      void processString(cdk::node::expression::String * const node, int lvl);
      void processIdentifier(cdk::node::expression::Identifier * const node, int lvl);

    protected:
      void processUnaryExpression(cdk::node::expression::UnaryExpression * const node, int lvl);

    public:
      void processNEG(cdk::node::expression::NEG * const node, int lvl);

    protected:
      void processBinaryExpression(cdk::node::expression::BinaryExpression * const node, int lvl);

    public:
      void processADD(cdk::node::expression::ADD * const node, int lvl);
      void processSUB(cdk::node::expression::SUB * const node, int lvl);
      void processMUL(cdk::node::expression::MUL * const node, int lvl);
      void processDIV(cdk::node::expression::DIV * const node, int lvl);
      void processMOD(cdk::node::expression::MOD * const node, int lvl);
      void processLT(cdk::node::expression::LT * const node, int lvl);
      void processLE(cdk::node::expression::LE * const node, int lvl);
      void processGE(cdk::node::expression::GE * const node, int lvl);
      void processGT(cdk::node::expression::GT * const node, int lvl);
      void processNE(cdk::node::expression::NE * const node, int lvl);
      void processEQ(cdk::node::expression::EQ * const node, int lvl);

    public:
      void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl);
      void processAddressing(mayfly::node::expression::Addressing * const node, int lvl);
      void processAND(mayfly::node::expression::AND * const node, int lvl);
      void processAssignment(mayfly::node::expression::Assignment * const node, int lvl);
      void processDecrement(mayfly::node::expression::Decrement * const node, int lvl);
      void processIncrement(mayfly::node::expression::Increment * const node, int lvl);
      void processIndexing(mayfly::node::expression::Indexing * const node, int lvl);
      void processMemoryReservation(mayfly::node::expression::MemoryReservation * const node, int lvl);
      void processNOT(mayfly::node::expression::NOT * const node, int lvl);
      void processOR(mayfly::node::expression::OR * const node, int lvl);
      void processRead(mayfly::node::expression::Read * const node, int lvl);
      void processFunctionCall(mayfly::node::expression::FunctionCall * const node, int lvl);
      void processIdentity(mayfly::node::expression::Identity * const node, int lvl);
      void processExpressionAsInstruction(mayfly::node::ExpressionAsInstruction * const node, int lvl);

    public:
      void processPrintNode(mayfly::node::PrintNode * const node, int lvl);
      void processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl);
      void processIfNode(mayfly::node::IfNode * const node, int lvl);
      void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl);
      void processBreakNode(mayfly::node::BreakNode * const node, int lvl);
      void processContinueNode(mayfly::node::ContinueNode * const node, int lvl);
      void processReturnNode(mayfly::node::ReturnNode * const node, int lvl);
      void processForUpToNode(mayfly::node::ForUpToNode * const node, int lvl);
      void processForDownToNode(mayfly::node::ForDownToNode * const node, int lvl);
      void processBlock(mayfly::node::Block * const node, int lvl);
      void processVariableDeclaration(mayfly::node::VariableDeclaration * const node, int lvl);
      void processFunctionDeclaration(mayfly::node::FunctionDeclaration * const node, int lvl);
      void processFunctionDefinition(mayfly::node::FunctionDefinition * const node, int lvl);

    };

  } // namespace semantics
} // namespace mayfly

#endif

// $Log: XMLwriter.h,v $
// Revision 1.19  2013-05-13 19:10:06  ist164787
// ExpressionAsInstruction node added
//
// Revision 1.18  2013-05-13 15:52:44  ist164787
// Added some more methods to TypeValidator
//
// Revision 1.17  2013-04-24 10:48:10  ist164787
// Removed Function Argument, misc minor changes
//
// Revision 1.16  2013-04-18 19:05:13  ist164787
// Added VariableDeclaration function content at XMLwriter; Added a method to print ExpressionTypes
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
// Revision 1.11  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.10  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.9  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.8  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
