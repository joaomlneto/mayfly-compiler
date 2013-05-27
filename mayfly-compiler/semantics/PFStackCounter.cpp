// $Id: PFStackCounter.cpp,v 1.10 2013-05-17 16:18:53 ist164787 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "semantics/PFStackCounter.h"
#include "nodes/all.h"  // all.h is automatically generated

// just to get a shorter name
namespace cpt = mayfly;

// Uncomment next line for debug prints
//#define __PFSTACKCOUNTER_DEBUG__

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processSequence(cdk::node::Sequence * const node, int lvl) {
	for (size_t i = 0; i < node->size(); i++) {
		node->node(i)->accept(this, lvl);
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processBlock(cpt::node::Block * const node, int lvl) {
	if(node->declarations() != NULL) {
		node->declarations()->accept(this, lvl+2);
	}
	if(node->instructions() != NULL) {
		// We could have nested blocks with declarations
		// We must account for all of them
		node->instructions()->accept(this, lvl+2);
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processVariableDeclaration(cpt::node::VariableDeclaration * const node, int lvl) {
	_size += node->type()->size();
}

//---------------------------------------------------------------------------

/**
 * This function computes the necessary stack space for local variables
 */
void cpt::semantics::PFStackCounter::processFunctionDefinition(cpt::node::FunctionDefinition * const node, int lvl) {
	// space required for the return variable
	if(node->type()->name() != ExpressionType::TYPE_VOID) {
		_size += node->type()->size();
	}
	node->block()->accept(this, lvl+2);
#ifdef __PFSTACKCOUNTER_DEBUG__
	std::cerr << "[StackCounter] FunctionDefinition ["
	          << node->identifier() << "] "
				 << _size << " bytes"
				 << std::endl;
#endif
}

//---------------------------------------------------------------------------

/**
 * This function computes the size occupied on stack for the arguments
 */
void cpt::semantics::PFStackCounter::processFunctionCall(mayfly::node::expression::FunctionCall * const node, int lvl) {
	// If function call has arguments
	if(node->arguments() != NULL) {
		node->arguments()->accept(this, lvl+2);
	}
#ifdef __PFSTACKCOUNTER_DEBUG__
	std::cerr << "[StackCounter] FunctionCall ["
	          << node->identifier() << "] "
	          << _size << " bytes"
	          << std::endl;
#endif
}

//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processDoWhileNode(mayfly::node::DoWhileNode * const node, int lvl) {
	// If While has a block (it must!... but better safe than sorry)
	if(node->instruction() != NULL) {
		node->instruction()->accept(this, lvl+2);
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processIfNode(mayfly::node::IfNode * const node, int lvl) {
	if(node->block() != NULL) {
		node->block()->accept(this, lvl+2);
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processIfElseNode(mayfly::node::IfElseNode * const node, int lvl) {
	if(node->thenblock() != NULL) {
		node->thenblock()->accept(this, lvl+2);
	}
	if(node->elseblock() != NULL) {
		node->elseblock()->accept(this, lvl+2);
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processForUpToNode(mayfly::node::ForUpToNode * const node, int lvl) {
	if(node->block() != NULL) {
		node->block()->accept(this, lvl+2);
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFStackCounter::processForDownToNode(mayfly::node::ForDownToNode * const node, int lvl) {
	if(node->block() != NULL) {
		node->block()->accept(this, lvl+2);
	}
}


//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: PFStackCounter.cpp,v $
// Revision 1.10  2013-05-17 16:18:53  ist164787
// Added missing methods in StackCounter - you can also declare variables in blocks that are in Whiles/Fors/Ifs...
//
// Revision 1.9  2013-05-15 19:51:27  ist164787
// Return node works... I hope
//
// Revision 1.8  2013-05-15 12:51:54  ist164787
// Nested block declarations in functions working, fixed block attribute name from definitions to instructions... seems legit now
//
// Revision 1.7  2013-05-14 00:17:44  ist164787
// Lots of PFwriter wrote. Lots of TypeValidator validated. See what I did there?
//
// Revision 1.6  2013-05-13 21:01:17  ist164787
// TypeValidator almost finished, Function Calls are full of awesome, printnode prints everything... other minor changes i dont remember
//
// Revision 1.5  2013-05-11 22:15:30  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.4  2013-05-11 15:35:35  ist164787
// vardecls in pfwriter - began changes
//
// Revision 1.3  2013-05-09 21:20:16  ist164787
// minor changes
//
// Revision 1.2  2013-05-09 15:51:23  ist164787
// Small changes on FunctionDefinition and StackCounter
//
// Revision 1.1  2013-05-08 22:49:04  ist164787
// - Added StackCounter - a visitor to compute the necessary space for local
// variables (works for both functiondefinition and block nodes)
// - Removed unused dumb function in grammar file.y
//
//
