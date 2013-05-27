// $Id: PFTypeValidator.cpp,v 1.16 2013-05-20 19:31:31 ist164787 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "semantics/PFTypeValidator.h"
#include "nodes/all.h"  // all.h is automatically generated

// just to get a shorter name
namespace cpt = mayfly;

// Uncomment next line for debug prints
#define __PFTYPEVALIDATOR_DEBUG__

std::string cpt::semantics::PFTypeValidator::fixFunctionName(std::string identifier) {
	// POSTFIX RESTRICTION: main function must be named '_main'
	// But in MAYFLY, the main function must be 'mayfly so... (lol h4x!)
	if(identifier == "mayfly") return "_main";
	if(identifier == "_main") return "mayfly";
	return identifier;
}

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::visitChildren(cdk::node::expression::BinaryExpression * const node, int lvl) {

	// if node already has a type specified, it means it is already validated
	// poor guy has been through much, so we'll spare him this time
	if(node->type() != NULL) {
		return;
	}

#ifdef __PFTYPEVALIDATOR_DEBUG__
	std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] HELLO" << std::endl;
	std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] Going to visit my left child" << std::endl;
#endif
	node->left()->accept(this, lvl+3);
#ifdef __PFTYPEVALIDATOR_DEBUG__
	//std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] My left child has type " << type2str(node->left()->type()) << std::endl;
	std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] Going to visit my right child" << std::endl;
#endif
	node->right()->accept(this, lvl+3);
#ifdef __PFTYPEVALIDATOR_DEBUG__
	//std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] My right child has type " << type2str(node->right()->type()) << std::endl;
#endif
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::visitChildren(cdk::node::expression::UnaryExpression * const node, int lvl) {

	// if node already has a type specified, it means it is already validated
	// poor guy has been through much, so we'll spare him this time
	if(node->type() != NULL) {
		return;
	}

#ifdef __PFTYPEVALIDATOR_DEBUG__
	std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] HELLO" << std::endl;
	std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] Going to visit my child" << std::endl;
#endif
	node->argument()->accept(this, lvl+3);
#ifdef __PFTYPEVALIDATOR_DEBUG__
	//std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] My child has type " << type2str(node->argument()->type()) << std::endl;
#endif
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::finalizeNodeValidation(cdk::node::expression::Expression * const node, int lvl) {
#ifdef __PFTYPEVALIDATOR_DEBUG__
	std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << "] I have type " << type2str(node->type()) << std::endl;
#endif
	if(node->type()->name() == ExpressionType::TYPE_ERROR) {
		std::cout << std::string(lvl, ' ') << "[TYPEVALIDATOR] [" << node->name() << " @ line " << node->lineno() << "] Invalid types!! " << type2str(node->type()) << std::endl;
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processBinaryArithmeticExpression(cdk::node::expression::BinaryExpression * const node, int lvl) {
	visitChildren(node, lvl);

	// Check for invalid types in expression
	// FIXME: this is too long, better negate this...
	if((node->left()->type()->name() == ExpressionType::TYPE_STRING)
	|| (node->right()->type()->name() == ExpressionType::TYPE_STRING)
	|| (node->left()->type()->name() == ExpressionType::TYPE_VOID)
	|| (node->right()->type()->name() == ExpressionType::TYPE_VOID)
	|| (node->left()->type()->name() == ExpressionType::TYPE_POINTER)
	|| (node->right()->type()->name() == ExpressionType::TYPE_POINTER)
	|| (node->left()->type()->name() == ExpressionType::TYPE_ERROR)
	|| (node->right()->type()->name() == ExpressionType::TYPE_ERROR)) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
	}

	// If an operand is of type double, the binary expression is of type double
	if((node->left()->type()->name() == ExpressionType::TYPE_DOUBLE)
	|| (node->right()->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE));
	}
	// Otherwise, they are both integers, and the binary expression has type integer as well
	else {
		node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processBinaryLogicalExpression(cdk::node::expression::BinaryExpression * const node, int lvl) {
	visitChildren(node, lvl);

	// Check if operands have compatible types (i.e. integer)
	if((node->left()->type()->name() != ExpressionType::TYPE_INT)
	|| (node->right()->type()->name() != ExpressionType::TYPE_INT)) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
		return;
	}

	// It is always of type boolean (booleans are integers in mayfly)
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processBinaryEqualityExpression(cdk::node::expression::BinaryExpression * const node, int lvl) {
	visitChildren(node, lvl);

	// Check for invalid types in expression
	if((node->left()->type()->name() == ExpressionType::TYPE_STRING)
	|| (node->right()->type()->name() == ExpressionType::TYPE_STRING)
	|| (node->left()->type()->name() == ExpressionType::TYPE_VOID)
	|| (node->right()->type()->name() == ExpressionType::TYPE_VOID)
	|| (node->left()->type()->name() == ExpressionType::TYPE_ERROR)
	|| (node->right()->type()->name() == ExpressionType::TYPE_ERROR)) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
	}

	// It is always of type boolean
	// On Mayfly, its just an integer but... its more cute this way
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processUnaryArithmeticExpression(cdk::node::expression::UnaryExpression * const node, int lvl) {
	visitChildren(node, lvl);

	// Check if argument has a compatible type - integer or double
	if((node->argument()->type()->name() != ExpressionType::TYPE_INT)
	&& (node->argument()->type()->name() != ExpressionType::TYPE_DOUBLE)) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
		return;
	}

	// It has the same type as its child
	node->type(node->argument()->type());
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processUnaryIncrementExpression(cdk::node::expression::UnaryExpression * const node, int lvl) {
	visitChildren(node, lvl);

	// Check if argument has a compatible type - integer or pointer
	if((node->argument()->type()->name() != ExpressionType::TYPE_INT)
	&& (node->argument()->type()->name() != ExpressionType::TYPE_POINTER)) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
	}

	// It has the same type as its child
	node->type(node->argument()->type());
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processInteger(cdk::node::expression::Integer * const node, int lvl) {
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processDouble(cdk::node::expression::Double * const node, int lvl) {
	node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE));
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processString(cdk::node::expression::String * const node, int lvl) {
	node->type(new ExpressionType(4, ExpressionType::TYPE_STRING));
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl) {
	// Check if a symbol is registered with that identifier
	Symbol *s = _symtab.find(node->value());
	if(s == nullptr) {
		// No such identifier on symbol table!
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
	}
	else {
		// Found it!
		node->type(s->type());
	}
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processNEG(cdk::node::expression::NEG * const node, int lvl) {
	processUnaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processIdentity(cpt::node::expression::Identity * const node, int lvl) {
	processUnaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processADD(cdk::node::expression::ADD * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);

	// Exception: on ADD and SUB you can have one integer and one pointer
	if((node->left()->type()->name() == ExpressionType::TYPE_POINTER)
	&& (node->right()->type()->name() == ExpressionType::TYPE_INT)) {
		node->type(node->left()->type());
	}
	if ((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->right()->type()->name() == ExpressionType::TYPE_POINTER)) {
		node->type(node->right()->type());
	}

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processSUB(cdk::node::expression::SUB * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);

	// Exception: on ADD and SUB you can have one integer and one pointer
	if((node->left()->type()->name() == ExpressionType::TYPE_POINTER)
	&& (node->right()->type()->name() == ExpressionType::TYPE_INT)) {
		node->type(node->left()->type());
	}
	if ((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->right()->type()->name() == ExpressionType::TYPE_POINTER)) {
		node->type(node->right()->type());
	}


	// Exception: on SUB you can have two pointers
	if((node->left()->type()->name() == ExpressionType::TYPE_POINTER)
	&& (node->right()->type()->name() == ExpressionType::TYPE_POINTER)) {
		node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processMUL(cdk::node::expression::MUL * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processDIV(cdk::node::expression::DIV * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processMOD(cdk::node::expression::MOD * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);

	// MOD does not allow Doubles
	// If one of the operands is of type double,
	// processBinaryArithmeticExpression should have assigned type Double
	// to the MOD node itself
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
	}

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processLT(cdk::node::expression::LT * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processLE(cdk::node::expression::LE * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processGE(cdk::node::expression::GE * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processGT(cdk::node::expression::GT * const node, int lvl) {
	processBinaryArithmeticExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processNE(cdk::node::expression::NE * const node, int lvl) {
	processBinaryEqualityExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processEQ(cdk::node::expression::EQ * const node, int lvl) {
	processBinaryEqualityExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processNOT(cpt::node::expression::NOT * const node, int lvl) {
	visitChildren(node, lvl);

	// Check if argument has a compatible type (i.e. integer)
	if(node->argument()->type()->name() != ExpressionType::TYPE_INT) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
		return;
	}

	// It is always of type boolean (booleans are integers in mayfly)
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processAND(cpt::node::expression::AND * const node, int lvl) {
	processBinaryLogicalExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processOR(cpt::node::expression::OR * const node, int lvl) {
	processBinaryLogicalExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}
	
//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processAssignment(mayfly::node::expression::Assignment * const node, int lvl) {

	_assignments.push(node);
	visitChildren(node, lvl);
	_assignments.pop();
	std::string right_child_name(node->right()->name());

	// Check for invalid types in assignment
	if((node->left()->type()->name() == ExpressionType::TYPE_VOID)
	|| (node->right()->type()->name() == ExpressionType::TYPE_VOID)
	|| (node->left()->type()->name() == ExpressionType::TYPE_ERROR)
	|| (node->right()->type()->name() == ExpressionType::TYPE_ERROR)
	|| (node->left()->type()->name() == ExpressionType::TYPE_UNSPEC)) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
		finalizeNodeValidation(node, lvl);
		return;
	}

	// We can assign an integer to a double
	else if((node->left()->type()->name() == ExpressionType::TYPE_DOUBLE)
	&& (node->right()->type()->name() == ExpressionType::TYPE_INT)) {
		node->type(node->left()->type()); // not necessary but...
	}

	// We can assign the integer literal zero to a pointer
	else if((node->left()->type()->name() == ExpressionType::TYPE_POINTER)
	&& (right_child_name == "Integer")
	&& (((cdk::node::expression::Simple<int>*)node->right())->value() == 0)) {
		node->type(node->left()->type()); // not necessary but...
	}

	// Right values can be left unspecified - memoryreservation and read nodes
	else if(node->right()->type()->name() == ExpressionType::TYPE_UNSPEC) {
		node->type(node->left()->type());
	}

	// Otherwise, if operand types do not match, its an error
	else if(node->left()->type()->name() != node->right()->type()->name()) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
		finalizeNodeValidation(node, lvl);
		return;
	}

	// Otherwise, both operands have the same type
	// The assignment type has the same type of both
	node->type(node->left()->type());

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processAddressing(mayfly::node::expression::Addressing * const node, int lvl) {
	visitChildren(node, lvl);

	// Check if argument has a compatible type (i.e. integer)
	if(node->argument()->type()->name() != ExpressionType::TYPE_POINTER) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
		return;
	}

	// It is always of type boolean (booleans are integers in mayfly)
	node->type(new ExpressionType(4, ExpressionType::TYPE_INT));

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processDecrement(mayfly::node::expression::Decrement * const node, int lvl) {
	processUnaryIncrementExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processIncrement(mayfly::node::expression::Increment * const node, int lvl) {
	processUnaryIncrementExpression(node, lvl);
	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processMemoryReservation(mayfly::node::expression::MemoryReservation * const node, int lvl) {

	if((node->type() != NULL) 
	&& (node->type()->name() != ExpressionType::TYPE_UNSPEC)) {
		// Nothing to do here
		// Been there, done that
		return;
	}

	// It returns a pointer to ... somewhere - see below
	node->type(new ExpressionType(4, ExpressionType::TYPE_POINTER));

	// We dont have a parent yet! Get one :(
	if(_assignments.size() == 0) {
		// Orphan MemoryReservation - it has default type (integer)
		node->type()->_subtype = new ExpressionType(4, ExpressionType::TYPE_INT);

	}
	else {
		// If it is in an assignment, it should have the same type as the assignment
		node->parent_assignment(_assignments.top());
		node->type()->_subtype = new ExpressionType(0, ExpressionType::TYPE_UNSPEC);
	}

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processIndexing(mayfly::node::expression::Indexing * const node, int lvl) {
	visitChildren(node, lvl);

	// Check if child nodes have compatible types
	// Left must be a pointer and right must be an integer
	if((node->left()->type()->name() != ExpressionType::TYPE_POINTER)
	|| (node->right()->type()->name() != ExpressionType::TYPE_INT)) {
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
		return;
	}

	// It is of the type pointed by its left child (which is a pointer)
	node->type(node->left()->type()->subtype());

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processRead(mayfly::node::expression::Read * const node, int lvl) {

	if((node->type() != NULL) 
	&& (node->type()->name() != ExpressionType::TYPE_UNSPEC)) {
		// Nothing to do here
		// Been there, done that
		return;
	}

	// We dont have a parent yet! Get one :(
	if(_assignments.size() == 0) {
		// Orphan MemoryReservation - it has default type (integer)
		node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
	}
	else {
		// If it is in an assignment, it should have the same type as the assignment
		node->parent_assignment(_assignments.top());
		node->type(new ExpressionType(0, ExpressionType::TYPE_UNSPEC));
	}

	finalizeNodeValidation(node, lvl);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFTypeValidator::processFunctionCall(mayfly::node::expression::FunctionCall * const node, int lvl) {
	//FIXME: Check if fixFunctionName is required (it is!)
	// Check if a symbol is registered with that identifier
	Symbol *s = _symtab.find(fixFunctionName(fixFunctionName(node->identifier())));
	if(s == nullptr) {
		// No such identifier on symbol table!
		node->type(new ExpressionType(0, ExpressionType::TYPE_ERROR));
	}
	else {
		// Found it!
		node->type(s->type());
	}
	finalizeNodeValidation(node, lvl);
}

void cpt::semantics::PFTypeValidator::processVariableDeclaration(mayfly::node::VariableDeclaration * const node, int lvl) {
	if(node->initial_value() != NULL) {
		node->initial_value()->accept(this, lvl+1);
	}
}

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: PFTypeValidator.cpp,v $
// Revision 1.16  2013-05-20 19:31:31  ist164787
// misc fixes
//
// Revision 1.15  2013-05-19 10:46:59  ist164787
// Memory reservation seems to be working... partially well
//
// Revision 1.14  2013-05-16 21:03:41  ist164787
// Fixed when assigning integers to numbers
//
// Revision 1.13  2013-05-16 19:31:28  ist164787
// Refactoring and fixes
//
// Revision 1.12  2013-05-15 19:51:27  ist164787
// Return node works... I hope
//
// Revision 1.11  2013-05-15 12:51:54  ist164787
// Nested block declarations in functions working, fixed block attribute name from definitions to instructions... seems legit now
//
// Revision 1.10  2013-05-14 21:52:53  ist164787
// minor bugfixes
//
// Revision 1.9  2013-05-14 14:41:24  ist164787
// bugfixes in many expressions when dealing with leftvalues, bugfix in print nodes; fixed a bug for increment node on typevalidator
//
// Revision 1.8  2013-05-14 00:17:45  ist164787
// Lots of PFwriter wrote. Lots of TypeValidator validated. See what I did there?
//
// Revision 1.7  2013-05-13 21:01:17  ist164787
// TypeValidator almost finished, Function Calls are full of awesome, printnode prints everything... other minor changes i dont remember
//
// Revision 1.6  2013-05-13 19:10:06  ist164787
// ExpressionAsInstruction node added
//
// Revision 1.5  2013-05-13 18:34:03  ist164787
// Fixed identifier and leftvalue confusion... added identity node for type validation... refactored typevalidator code
//
// Revision 1.4  2013-05-13 15:52:44  ist164787
// Added some more methods to TypeValidator
//
// Revision 1.3  2013-05-13 09:52:23  ist164787
// Did a bit more of typevalidator - from 7.3 to 7.11
//
// Revision 1.2  2013-05-12 22:29:55  ist164787
// Fixed a lex error on doubles - was using yylval.i instead of yylval.dvim Makefile  Awfulvim Makefile  Did a bit of TypeValidator (simple nodes, and ADD and SUB binary expressions)... theres also a template for binary expressions - the common stuff. Also did the ADD on PFwriter - not sure if everything is finished, though!
//
// Revision 1.1  2013-05-12 14:17:19  ist164787
// Added TypeValidator, does nothing yet
//
