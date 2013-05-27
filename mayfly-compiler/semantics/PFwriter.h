// $Id: PFwriter.h,v 1.44 2013-05-20 19:31:32 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_PFWRITER_H__
#define __MF_SEMANTICS_PFWRITER_H__

#include <string>
#include <iostream>
#include <vector>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/generators/Postfix.h>
#include <cdk/nodes/expressions/Expression.h>
#include "nodes/FunctionDefinition.h"
#include "nodes/FunctionDeclaration.h"
#include "nodes/expression/FunctionCall.h"
#include "semantics/SemanticProcessor.h"
#include "semantics/Symbol.h"
#include "semantics/FunctionSymbol.h"
#include "semantics/VariableSymbol.h"
#include "semantics/LocalVariableSymbol.h"
#include "semantics/GlobalVariableSymbol.h"

namespace mayfly {
	namespace semantics {

		//!
		//! Traverse syntax tree and generate the corresponding assembly code.
		//!
		class PFwriter: public virtual SemanticProcessor {
			cdk::semantics::SymbolTable<Symbol> &_symtab;
			cdk::generator::Postfix &_pf;
			int _lbl;

			// Declare use of external functions
			bool _printi_declared = false;
			bool _printd_declared = false;
			bool _prints_declared = false;
			bool _println_declared = false;
			bool _readi_declared = false;
			bool _readd_declared = false;

			// Needed to process some nodes related to function definition
			bool _global_context = true; // false when inside functions
			FunctionSymbol *_current_function = NULL; // Current function
			int _local_declarations_offset; // for local variables
			int _local_arguments_offset;

			// For declaring global constant variables with type number or string
			// Ugly! :( @see processString processDouble processVariableDeclaration
			int _delayed_label;

			// Labels to jump on continue's and break's
			std::vector<std::string> _break_labels;
			std::vector<std::string> _continue_labels;

		public:
			PFwriter(std::ostream &os, bool debug, cdk::semantics::SymbolTable<Symbol> &symtab, cdk::generator::Postfix &pf) :
					SemanticProcessor(os, debug), _symtab(symtab), _pf(pf), _lbl(0) {
			}

		public:
			~PFwriter() {
				os().flush();
			}

		private:
			/** Method used to generate sequential labels. */
			inline std::string mklbl(int lbl) {
				std::ostringstream oss;
				if (lbl < 0)
					oss << ".L" << -lbl;
				else
					oss << "_L" << lbl;
				return oss.str();
			}

		// for debugging... 
		private:
		void debug(cdk::node::Node * const node, int lvl=0);
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

		// Section needed to process some of the simple values, which need
		// to go back to the "previous" segment...
		// This just eases the management of segments... I think
		private:
			enum PostfixSegment { BSS, DATA, RODATA, TEXT };
			PostfixSegment _previous_segment = PostfixSegment::TEXT;
			PostfixSegment _current_segment = PostfixSegment::TEXT;
			std::string segment2string(PostfixSegment seg) {
				switch(seg) {
					case BSS: return "BSS";
					case DATA: return "DATA";
					case RODATA: return "RODATA";
					case TEXT: return "TEXT";
				}
				return "ERROR";
			}
			void changeSegment(PostfixSegment seg) {
				// if no changes, dont change (avoid postfix spam... not good for debugging)
				if(_current_segment == seg) return;
				// Swap segments
				_previous_segment = _current_segment;
				switch(seg) {
					case BSS: _current_segment = BSS; _pf.BSS(); break;
					case DATA: _current_segment = DATA; _pf.DATA(); break;
					case RODATA: _current_segment = RODATA; _pf.RODATA(); break;
					case TEXT: _current_segment = TEXT; _pf.TEXT(); break;
				}
				// Debug prints
				//std::cout << "Was on segment " << segment2string(_previous_segment);
				//std::cout << " and now Im on segment " << segment2string(_current_segment) << std::endl;
			}
			void previousSegment() {
				changeSegment(_previous_segment);
			}

		// To swap _main with mayfly -- a bit of an overkill...
		private:
			inline std::string fixFunctionName(std::string identifier) {
				// POSTFIX RESTRICTION: main function must be named '_main'
				// But in MAYFLY, the main function must be 'mayfly so... (lol h4x!)
				if(identifier == "mayfly") return "_main";
				if(identifier == "_main") return "mayfly";
				return identifier;
			}
			inline std::string fixFunctionName(mayfly::node::FunctionDefinition * const node) {
				return fixFunctionName(node->identifier());
			}
			inline std::string fixFunctionName(mayfly::node::FunctionDeclaration * const node) {
				return fixFunctionName(node->identifier());
			}
			inline std::string fixFunctionName(mayfly::node::expression::FunctionCall * const node) {
				return fixFunctionName(node->identifier());
			}

		// These are to ease the burden of generating code
		// dependent on expression types and stuff...
		private:
			inline bool isLeftValue(cdk::node::expression::Expression * const node) {
				std::string name(node->name());
				return ((name == "LeftValue") || (name == "Indexing")); // ARGH!
			}
			inline void loadNodeValue(cdk::node::expression::Expression * const node) {
				if(node->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.DLOAD(); }
				else { _pf.LOAD(); }
			}
			inline void storeNodeValue(cdk::node::expression::Expression * const node) {
				if(node->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.DSTORE(); }
				else { _pf.STORE(); }
			}
			inline void duplicateNodeValue(cdk::node::expression::Expression * const node) {
				if(node->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.DDUP(); }
				else { _pf.DUP(); }
			}
			inline void doAddition(cdk::node::expression::Expression * const node) {
				if(node->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.DADD(); }
				else { _pf.ADD(); }
			}
			inline void doSubtraction(cdk::node::expression::Expression * const node) {
				if(node->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.DSUB(); }
				else { _pf.SUB(); }
			}
			inline void convertIfDouble(cdk::node::expression::Expression * const node) {
				if(node->type()->name() == ExpressionType::TYPE_DOUBLE) { _pf.I2D(); }
			}

		public:
			void processNil(cdk::node::Nil * const node, int lvl) {}
			void processData(cdk::node::Data * const node, int lvl) {}
			void processComposite(cdk::node::Composite * const node, int lvl) {}
			void processSequence(cdk::node::Sequence * const node, int lvl);

		public:
			void processInteger(cdk::node::expression::Integer * const node, int lvl);
			void processDouble(cdk::node::expression::Double * const node, int lvl);
			void processString(cdk::node::expression::String * const node, int lvl);
			void processIdentifier(cdk::node::expression::Identifier * const node, int lvl) {}

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

	}		// namespace semantics
} // namespace mayfly

#endif

// $Log: PFwriter.h,v $
// Revision 1.44  2013-05-20 19:31:32  ist164787
// misc fixes
//
// Revision 1.43  2013-05-19 11:05:59  ist164787
// Read working
//
// Revision 1.42  2013-05-19 10:46:59  ist164787
// Memory reservation seems to be working... partially well
//
// Revision 1.41  2013-05-17 22:20:27  ist164787
// Continue working, fixed While node in exchange for a DoWhile node
//
// Revision 1.40  2013-05-17 21:29:20  ist164787
// changed function name so it is a lot clearer now
//
// Revision 1.39  2013-05-16 21:03:41  ist164787
// Fixed when assigning integers to numbers
//
// Revision 1.38  2013-05-16 19:31:28  ist164787
// Refactoring and fixes
//
// Revision 1.37  2013-05-16 16:49:05  ist164787
// MOAR REFACTORING!
//
// Revision 1.36  2013-05-16 16:30:34  ist164787
// Refactoring
//
// Revision 1.35  2013-05-15 19:51:27  ist164787
// Return node works... I hope
//
// Revision 1.34  2013-05-15 19:28:34  ist164787
// Global constants; Print node fixed for doubles; Global doubles initialized with integers fixed
//
// Revision 1.33  2013-05-15 16:00:47  ist164787
// fixed bug in flex and byacc - doubles with capital E were not recognized (only with undercase e), expressions within parenthesis can be indexed - its also a left value. this case was not covered previously
//
// Revision 1.32  2013-05-15 11:05:04  ist164787
// Segment management functions
//
// Revision 1.31	2013-05-14 14:41:24	ist164787
// bugfixes in many expressions when dealing with leftvalues, bugfix in print nodes; fixed a bug for increment node on typevalidator
//
// Revision 1.30	2013-05-14 12:08:17	ist164787
// Fixed most binary expressions when dealing with left values, as they only push their addresses when visited, not their values... some nodes still need to be modified to reflect these changes
//
// Revision 1.29	2013-05-13 21:01:17	ist164787
// TypeValidator almost finished, Function Calls are full of awesome, printnode prints everything... other minor changes i dont remember
//
// Revision 1.28	2013-05-13 19:10:06	ist164787
// ExpressionAsInstruction node added
//
// Revision 1.27	2013-05-13 18:34:03	ist164787
// Fixed identifier and leftvalue confusion... added identity node for type validation... refactored typevalidator code
//
// Revision 1.26	2013-05-13 15:52:44	ist164787
// Added some more methods to TypeValidator
//
// Revision 1.25	2013-05-11 22:15:30	ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.24	2013-05-11 18:18:41	ist164787
// function declarations working, part of vardecls working
//
// Revision 1.23	2013-05-11 15:35:35	ist164787
// vardecls in pfwriter - began changes
//
// Revision 1.22	2013-05-10 13:03:36	ist164787
// Fixed FunctionSymbol arguments. FunctionSymbol is now being added to the Symbol Table on FunctionDefinition node processing
//
// Revision 1.21	2013-05-09 15:51:23	ist164787
// Small changes on FunctionDefinition and StackCounter
//
// Revision 1.20	2013-05-08 18:16:17	ist164787
// removed symbol subclasses - variablesymbol and functionsymbol
//
// Revision 1.19	2013-05-08 11:53:49	ist164787
// print functions and main function working -- function declarations, function arguments and function local variables DO NOT WORK
//
// Revision 1.18	2013-05-07 19:03:05	ist164787
// added missing files... oops
//
// Revision 1.17	2013-04-29 16:27:08	ist164787
// Compiler already produces a ASM file (doesnt do anything, though)
//
// Revision 1.16	2013-04-24 10:48:10	ist164787
// Removed Function Argument, misc minor changes
//
// Revision 1.15	2013-04-16 18:54:09	ist164787
// Added a new node: FunctionArgument. This represents an argument in a function declaration/definition
// Syntax tree is now being built (not tested)
//
// Revision 1.14	2013-04-14 20:59:23	ist164787
// MAJOR CHANGES in .y and .l and some XMLwriter.cpp; The return of LeftValue expression node
//
// Revision 1.13	2013-03-26 11:12:32	ist164787
// Removed unused Compact nodes
//
// Revision 1.12	2013-03-26 10:46:29	ist164787
// Removed Pointer expression node
//
// Revision 1.11	2013-03-25 19:13:20	ist164787
// Added FunctionDefinition node
//
// Revision 1.10	2013-03-25 19:07:17	ist164787
// Added FunctionDeclaration node
//
// Revision 1.9	2013-03-25 18:55:44	ist164787
// Added VariableDeclaration node
//
// Revision 1.8	2013-03-25 18:48:08	ist164787
// Added Block node
//
// Revision 1.7	2013-03-25 18:31:52	ist164787
// Removed ReadNode
//
// Revision 1.6	2013-03-25 18:03:26	ist164787
// added Break, Continue, Return, Node, ForUpTo, ForDownTo;\nRemoved ReadNode (instruction), WhileNode (is now DoWhileNode)
//
// Revision 1.5	2013-03-25 17:28:00	ist164787
// FunctionCall expression node added
//
// Revision 1.4	2013-03-25 17:17:15	ist164787
// Removed NOT expression node - theres already a NEG in CDK
//
// Revision 1.3	2013-03-25 12:16:19	ist164787
// Added the NOT unary operator node
//
// Revision 1.2	2013-03-25 12:08:59	ist164787
// Fixed semantics - it now compiles correctly again
//
// Revision 1.1	2013-02-16 16:10:14	ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.14	2013/02/10 19:20:04	david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.13	2013/02/09 18:57:47	david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.12	2012/04/10 19:09:47	david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.11	2012/02/18 19:37:58	david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
