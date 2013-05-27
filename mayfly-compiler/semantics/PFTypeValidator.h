// $Id: PFTypeValidator.h,v 1.11 2013-05-20 19:31:31 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_PFTYPEVALIDATOR_H__
#define __MF_SEMANTICS_PFTYPEVALIDATOR_H__

#include <string>
#include <iostream>
#include <stack>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/generators/Postfix.h>
#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include "nodes/expression/Assignment.h"
#include "semantics/SemanticProcessor.h"
#include "semantics/Symbol.h"

namespace mayfly {
	namespace semantics {

		//!
		//! Traverses part of the syntax tree and computes node types
		//! while also checking for incompatible type usage
		//!
		class PFTypeValidator: public virtual SemanticProcessor {
	 	private:
			cdk::semantics::SymbolTable<Symbol> &_symtab;
			
			// To detect the types of read and memory reservation nodes
			std::stack<mayfly::node::expression::Assignment*> _assignments;

		public:
			PFTypeValidator(cdk::semantics::SymbolTable<Symbol> &symtab, cdk::node::expression::Expression * const node) :
				SemanticProcessor(), _symtab(symtab) {
				if(node->type() == NULL) {
					node->accept(this, 0);
				}
			}
			// FIXME Terrible overloading... but it works so >_>...
			PFTypeValidator(cdk::semantics::SymbolTable<Symbol> &symtab, cdk::node::Node * const node) :
				SemanticProcessor(), _symtab(symtab) {
				node->accept(this, 0);
			}

			PFTypeValidator(cdk::semantics::SymbolTable<Symbol> &symtab) :
				SemanticProcessor(), _symtab(symtab) {}

		// For cute debugging purposes
		private:
			inline std::string type2str(ExpressionType *type) {
				switch(type->name()) {
					case ExpressionType::TYPE_INT: return "Integer";
					case ExpressionType::TYPE_DOUBLE: return "Number";
					case ExpressionType::TYPE_STRING: return "String";
					case ExpressionType::TYPE_VOID: return "Void";
					case ExpressionType::TYPE_ERROR: return "ERROR";
					case ExpressionType::TYPE_POINTER: return ("*" + type2str(type->subtype()));
				}
				return "UNSPECIFIED";
			}

		public:
			~PFTypeValidator() {
				os().flush();
			}
	
		private:
			inline std::string fixFunctionName(std::string identifier);

		private:
			void visitChildren(cdk::node::expression::BinaryExpression * const node, int lvl);
			void visitChildren(cdk::node::expression::UnaryExpression * const node, int lvl);
			void finalizeNodeValidation(cdk::node::expression::Expression * const node, int lvl);

		// Common typechecking between nodes
		private:
			// ADD SUB MUL DIV MOD GT GE LT LE
			void processBinaryArithmeticExpression(cdk::node::expression::BinaryExpression * const node, int lvl);
			// EQ NE
			void processBinaryEqualityExpression(cdk::node::expression::BinaryExpression * const node, int lvl);
			// AND OR
			void processBinaryLogicalExpression(cdk::node::expression::BinaryExpression * const node, int lvl);
			// NEG Identity
			void processUnaryArithmeticExpression(cdk::node::expression::UnaryExpression * const node, int lvl);
			// INC DEC
			void processUnaryIncrementExpression(cdk::node::expression::UnaryExpression * const node, int lvl);

		public:
			void processNil(cdk::node::Nil * const node, int lvl) {}
			void processData(cdk::node::Data * const node, int lvl) {}
			void processComposite(cdk::node::Composite * const node, int lvl) {}
			void processSequence(cdk::node::Sequence * const node, int lvl) {}

		public:
			void processInteger(cdk::node::expression::Integer * const node, int lvl);
			void processDouble(cdk::node::expression::Double * const node, int lvl);
			void processString(cdk::node::expression::String * const node, int lvl);
			void processIdentifier(cdk::node::expression::Identifier * const node, int lvl) {} // NOT USED

		public:
			void processNEG(cdk::node::expression::NEG * const node, int lvl);

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
			void processExpressionAsInstruction(mayfly::node::ExpressionAsInstruction * const node, int lvl) {}

		public:
			void processPrintNode(mayfly::node::PrintNode * const node, int lvl) {}
			void processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl) {}
			void processIfNode(mayfly::node::IfNode * const node, int lvl) {}
			void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl) {}
			void processBreakNode(mayfly::node::BreakNode * const node, int lvl) {}
			void processContinueNode(mayfly::node::ContinueNode * const node, int lvl) {}
			void processReturnNode(mayfly::node::ReturnNode * const node, int lvl) {}
			void processForUpToNode(mayfly::node::ForUpToNode * const node, int lvl) {}
			void processForDownToNode(mayfly::node::ForDownToNode * const node, int lvl) {}
			void processBlock(mayfly::node::Block * const node, int lvl) {}
			void processVariableDeclaration(mayfly::node::VariableDeclaration * const node, int lvl);
			void processFunctionDeclaration(mayfly::node::FunctionDeclaration * const node, int lvl) {}
			void processFunctionDefinition(mayfly::node::FunctionDefinition * const node, int lvl) {}

		};

	}		// namespace semantics
} // namespace mayfly

#endif

// $Log: PFTypeValidator.h,v $
// Revision 1.11  2013-05-20 19:31:31  ist164787
// misc fixes
//
// Revision 1.10  2013-05-19 10:46:59  ist164787
// Memory reservation seems to be working... partially well
//
// Revision 1.9  2013-05-16 21:55:35  ist164787
// Changed the way variables are initialized; Fixed a problem when using integer left values that would be converted to doubles *sigh* that was really lol!
//
// Revision 1.8  2013-05-16 21:03:41  ist164787
// Fixed when assigning integers to numbers
//
// Revision 1.7  2013-05-13 21:01:17  ist164787
// TypeValidator almost finished, Function Calls are full of awesome, printnode prints everything... other minor changes i dont remember
//
// Revision 1.6	2013-05-13 19:10:06	ist164787
// ExpressionAsInstruction node added
//
// Revision 1.5	2013-05-13 18:34:03	ist164787
// Fixed identifier and leftvalue confusion... added identity node for type validation... refactored typevalidator code
//
// Revision 1.4	2013-05-13 15:52:44	ist164787
// Added some more methods to TypeValidator
//
// Revision 1.3	2013-05-13 09:52:23	ist164787
// Did a bit more of typevalidator - from 7.3 to 7.11
//
// Revision 1.2	2013-05-12 22:29:55	ist164787
// Fixed a lex error on doubles - was using yylval.i instead of yylval.dvim Makefile	Awfulvim Makefile	Did a bit of TypeValidator (simple nodes, and ADD and SUB binary expressions)... theres also a template for binary expressions - the common stuff. Also did the ADD on PFwriter - not sure if everything is finished, though!
//
// Revision 1.1	2013-05-12 14:17:19	ist164787
// Added TypeValidator, does nothing yet
//
//
