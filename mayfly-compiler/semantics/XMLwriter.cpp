// $Id: XMLwriter.cpp,v 1.26 2013-05-17 23:15:52 ist164787 Exp $ -*- c++ -*-
#include <string>
#include "semantics/XMLwriter.h"
#include "nodes/all.h"  // automatically generated

// just to get a shorter name
namespace cpt = mayfly;

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processData(cdk::node::Data * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<data size='" << node->size() << "'>";
  for (size_t i = 0; i < node->size(); i++)
    os() << ((unsigned char*)node->data())[i];
  closeTag(node, lvl);
}

void cpt::semantics::XMLwriter::processComposite(cdk::node::Composite * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<composite size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->at(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processSequence(cdk::node::Sequence * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<Sequence size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processInteger(cdk::node::expression::Integer * const node, int lvl) {
  processSimple(node, lvl);
}

void cpt::semantics::XMLwriter::processDouble(cdk::node::expression::Double * const node, int lvl) {
  processSimple(node, lvl);
}

void cpt::semantics::XMLwriter::processString(cdk::node::expression::String * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processIdentifier(cdk::node::expression::Identifier * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

inline void cpt::semantics::XMLwriter::processUnaryExpression(cdk::node::expression::UnaryExpression * const node, int lvl) {
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void cpt::semantics::XMLwriter::processNEG(cdk::node::expression::NEG * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void cpt::semantics::XMLwriter::processBinaryExpression(cdk::node::expression::BinaryExpression * const node, int lvl) {
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void cpt::semantics::XMLwriter::processADD(cdk::node::expression::ADD * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processSUB(cdk::node::expression::SUB * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processMUL(cdk::node::expression::MUL * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processDIV(cdk::node::expression::DIV * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processMOD(cdk::node::expression::MOD * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processLT(cdk::node::expression::LT * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processLE(cdk::node::expression::LE * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processGE(cdk::node::expression::GE * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processGT(cdk::node::expression::GT * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processNE(cdk::node::expression::NE * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void cpt::semantics::XMLwriter::processEQ(cdk::node::expression::EQ * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processLeftValue(cpt::node::expression::LeftValue * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processAddressing(cpt::node::expression::Addressing * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processAND(cpt::node::expression::AND * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processAssignment(cpt::node::expression::Assignment * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processDecrement(cpt::node::expression::Decrement * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " is_prefix='" << node->is_prefix() << "'" \
	     << ">" << std::endl;
	node->argument()->accept(this, lvl+2);
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processIncrement(cpt::node::expression::Increment * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " is_prefix='" << node->is_prefix() << "'" \
	     << ">" << std::endl;
	node->argument()->accept(this, lvl+2);
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processIndexing(cpt::node::expression::Indexing * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processMemoryReservation(cpt::node::expression::MemoryReservation * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processNOT(cpt::node::expression::NOT * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processOR(cpt::node::expression::OR * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processRead(cpt::node::expression::Read * const node, int lvl) {
	openTag(node, lvl);
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processFunctionCall(cpt::node::expression::FunctionCall * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " identifier='" << node->identifier() << "'" \
	     << ">" << std::endl;
	openTag("arguments", lvl+2);
	node->arguments()->accept(this, lvl+4);
	closeTag("arguments", lvl+2);
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processIdentity(cpt::node::expression::Identity * const node, int lvl) {
	node->argument()->accept(this, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processExpressionAsInstruction(cpt::node::ExpressionAsInstruction * const node, int lvl) {
	node->expression()->accept(this, lvl);
}

//---------------------------------------------------------------------------
/*
void cpt::semantics::XMLwriter::processProgramNode(cpt::node::ProgramNode * const node, int lvl) {
  openTag(node, lvl);
  node->statements()->accept(this, lvl + 4);
  closeTag(node, lvl);
}
*/
//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processPrintNode(cpt::node::PrintNode * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<" << node->name() \
       << " print_newline='" << node->print_newline() << "'" \
       << ">" << std::endl;
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------
/*
void cpt::semantics::XMLwriter::processAssignmentNode(cpt::node::AssignmentNode * const node, int lvl) {
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 2);
  openTag("rvalue", lvl + 2);
  node->rvalue()->accept(this, lvl + 4);
  closeTag("rvalue", lvl + 2);
  closeTag(node, lvl);
}
*/
//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processDoWhileNode(cpt::node::DoWhileNode * const node, int lvl) {
  openTag(node, lvl);
  openTag("instruction", lvl + 2);
  node->instruction()->accept(this, lvl + 4);
  closeTag("instruction", lvl + 2);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::XMLwriter::processIfNode(cpt::node::IfNode * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void cpt::semantics::XMLwriter::processIfElseNode(cpt::node::IfElseNode * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processBreakNode(cpt::node::BreakNode * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " level='" << node->level() << "'" \
	     << ">" << std::endl;
	closeTag(node, lvl);
}
//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processContinueNode(cpt::node::ContinueNode * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " level='" << node->level() << "'" \
	     << ">" << std::endl;
	closeTag(node, lvl);
}
//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processReturnNode(cpt::node::ReturnNode * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}
//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processForUpToNode(cpt::node::ForUpToNode * const node, int lvl) {
	openTag(node, lvl);
	openTag("LeftValue", lvl+2);
	node->leftvalue()->accept(this, lvl+4);
	closeTag("LeftValue", lvl+2);
	openTag("Start", lvl+2);
	node->start()->accept(this, lvl+4);
	closeTag("Start", lvl+2);
	openTag("End", lvl+2);
	node->end()->accept(this, lvl+4);
	closeTag("End", lvl+2);
	openTag("Step", lvl+2);
	node->step()->accept(this, lvl+4);
	closeTag("Step", lvl+2);
	node->block()->accept(this, lvl+4);
	closeTag(node, lvl);
}
//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processForDownToNode(cpt::node::ForDownToNode * const node, int lvl) {
	openTag(node, lvl);
	openTag("LeftValue", lvl+2);
	node->leftvalue()->accept(this, lvl+4);
	closeTag("LeftValue", lvl+2);
	openTag("Start", lvl+2);
	node->start()->accept(this, lvl+4);
	closeTag("Start", lvl+2);
	openTag("End", lvl+2);
	node->end()->accept(this, lvl+4);
	closeTag("End", lvl+2);
	openTag("Step", lvl+2);
	node->step()->accept(this, lvl+4);
	closeTag("Step", lvl+2);
	node->block()->accept(this, lvl+4);
	closeTag(node, lvl);
}
//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processBlock(cpt::node::Block * const node, int lvl) {
	openTag(node, lvl);
	if(node->declarations() != NULL) {
		openTag("declarations", lvl+2);
		node->declarations()->accept(this, lvl+4);
		closeTag("declarations", lvl+2);
	}
	if(node->instructions() != NULL) {
		openTag("instructions", lvl+2);
		node->instructions()->accept(this, lvl+4);
		closeTag("instructions", lvl+2);
	}
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processVariableDeclaration(cpt::node::VariableDeclaration * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " identifier='" << node->identifier() << "'" \
	     << " type='" << type2str(node->type()) << "'" \
	     << " is_public='" << node->is_public() << "'" \
	     << " is_const='" << node->is_const() << "'" \
	     << ">" << std::endl;
	if(node->initial_value() != NULL) {
		openTag("initial_value", lvl+2);
		node->initial_value()->accept(this, lvl+4);
		closeTag("initial_value", lvl+2);
	}
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processFunctionDeclaration(cpt::node::FunctionDeclaration * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " identifier='" << node->identifier() << "'" \
	     << " type='" << type2str(node->type()) << "'" \
	     << " is_public='" << node->is_public() << "'";
	os() << ">" << std::endl;
	if(node->arguments() != NULL) {
		openTag("Arguments", lvl+2);
		node->arguments()->accept(this, lvl+4);
		closeTag("Arguments", lvl+2);
	}
	if(node->literal() != NULL) {
		openTag("Literal", lvl+2);
		node->literal()->accept(this, lvl+4);
		closeTag("Literal", lvl+2);
	}
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------
void cpt::semantics::XMLwriter::processFunctionDefinition(cpt::node::FunctionDefinition * const node, int lvl) {
	os() << std::string(lvl, ' ') << "<" << node->name() \
	     << " identifier='" << node->identifier() << "'" \
	     << " type='" << type2str(node->type()) << "'" \
	     << " is_public='" << node->is_public() << "'" \
	     << ">" << std::endl;
	if(node->arguments() != NULL) {
		openTag("Arguments", lvl+2);
		node->arguments()->accept(this, lvl+4);
		closeTag("Arguments", lvl+2);
	}
	openTag("Literal", lvl+2);
	node->literal()->accept(this, lvl+4);
	closeTag("Literal", lvl+2);
	openTag("Block", lvl+2);
	node->block()->accept(this, lvl+4);
	closeTag("Block", lvl+2);
	closeTag(node, lvl);	
}

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: XMLwriter.cpp,v $
// Revision 1.26  2013-05-17 23:15:52  ist164787
// bugfix in xmlwriter, fixme note...
//
// Revision 1.25  2013-05-15 12:51:54  ist164787
// Nested block declarations in functions working, fixed block attribute name from definitions to instructions... seems legit now
//
// Revision 1.24  2013-05-13 19:10:06  ist164787
// ExpressionAsInstruction node added
//
// Revision 1.23  2013-05-13 15:52:44  ist164787
// Added some more methods to TypeValidator
//
// Revision 1.22  2013-05-09 21:20:16  ist164787
// minor changes
//
// Revision 1.21  2013-04-24 10:48:10  ist164787
// Removed Function Argument, misc minor changes
//
// Revision 1.20  2013-04-19 00:02:19  ist164787
// minor bugfixes in grammar - missing modulus operator - and in xmlwriter - wasnt displaying all of increment/decrement nodes
//
// Revision 1.19  2013-04-18 22:41:20  ist164787
// XMLwriter methods, small changes in BreakNode and ContinueNode and FunctionCall
//
// Revision 1.18  2013-04-18 19:05:13  ist164787
// Added VariableDeclaration function content at XMLwriter; Added a method to print ExpressionTypes
//
// Revision 1.17  2013-04-16 19:58:29  ist164787
// fixed syntax tree building - it was segfaulting
//
// Revision 1.16  2013-04-16 18:54:09  ist164787
// Added a new node: FunctionArgument. This represents an argument in a function declaration/definition
// Syntax tree is now being built (not tested)
//
// Revision 1.15  2013-04-14 20:59:23  ist164787
// MAJOR CHANGES in .y and .l and some XMLwriter.cpp; The return of LeftValue expression node
//
// Revision 1.14  2013-03-26 11:16:22  ist164787
// Reused some of compact semantics
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
// Revision 1.10  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.9  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.8  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
