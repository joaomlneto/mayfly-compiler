// $Id: PFwriter.cpp,v 1.69 2013-05-20 19:31:31 ist164787 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "semantics/PFwriter.h"
#include "semantics/PFStackCounter.h"
#include "semantics/PFTypeValidator.h"
#include "nodes/all.h"	// all.h is automatically generated

// just to get a shorter name
namespace cpt = mayfly;

// Uncomment for extra spam
#define __PFWRITER_DEBUG__

void cpt::semantics::PFwriter::debug(cdk::node::Node * const node, int lvl) {
#ifdef __PFWRITER_DEBUG__
	os() << ";" << std::string(10, '~');
	for(int i=0; i<lvl; i++) {
		os() << "  |";
	}
	os() << "--" << node->name() << std::endl;
#endif
}

//---------------------------------------------------------------------------
//		 THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processSequence(cdk::node::Sequence * const node, int lvl) {
	for (size_t i = 0; i < node->size(); i++) {
		node->node(i)->accept(this, lvl+1);
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processInteger(cdk::node::expression::Integer * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Write Integer value... where?
	if(_global_context) {
		// If in a global context, write value in memory
		_pf.CONST(node->value());
	}
	else {
		// If in a local context, push value into the stack
		_pf.INT(node->value());
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processDouble(cdk::node::expression::Double * const node, int lvl) {

	debug(node, lvl);

	int lbl1 = ++_lbl;

	// For the RODATAception sh**storm special horrible messy case
	bool global_constant = _global_context && (_current_segment == RODATA);
	bool global_nonconstant = _global_context && !global_constant;

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Global non-constant - just load the double!
	if(global_nonconstant) {
		_pf.DOUBLE(node->value());
		return;
	}

	// Generate the Double
	changeSegment(RODATA);
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl1));
	_pf.DOUBLE(node->value());

	// Check where to load the double address to
	if(global_constant) {
		// Its a global constant - dont load address
		// Mark label for future use (delay)...
		_delayed_label = lbl1;
	}
	else {
		// Load it to memory
		previousSegment();
		_pf.ADDR(mklbl(lbl1));
		_pf.DLOAD();
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processString(cdk::node::expression::String * const node, int lvl) {

	debug(node, lvl);

	int lbl1 = ++_lbl;

	// For the RODATAception sh**storm special horrible messy case
	bool global_constant = _global_context && (_current_segment == RODATA);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// generate the string
	changeSegment(RODATA);
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl1));
	_pf.STR(node->value());

	// Check where to load the string address to
	if(_global_context) {
		if(global_constant) {
			// Its a global constant - dont load address
			// Mark label for future use (delay)...
			_delayed_label = lbl1;
		}
		else {
			// Load it to memory
			previousSegment();
			_pf.ID(mklbl(lbl1));
		}
	}
	else {
		// Load it (the address of the first string character) into stack
		previousSegment();
		_pf.ADDR(mklbl(lbl1));
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processNEG(cdk::node::expression::NEG * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	node->argument()->accept(this, lvl+1); // determine the value

	// If the argument is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->argument())) {
		loadNodeValue(node->argument());
	}

	// Check which type is the argument of
	if(node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// If it is a Double, DNEG
		_pf.DNEG();
	}
	else {
		// Otherwise, its a NEG
		_pf.NEG();
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processADD(cdk::node::expression::ADD * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);
	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the ADD has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the ADD has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! use DADD
		_pf.DADD();
	}
	else {
		// No. Its a regular integer ADD
		_pf.ADD();
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processSUB(cdk::node::expression::SUB * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the SUB has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the SUB has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}


	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! use DSUB
		_pf.DSUB();
	}
	else {
		// No. Its a regular integer SUB
		// (works for pointers as well!)
		_pf.SUB();
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processMUL(cdk::node::expression::MUL * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the MUL has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the MUL has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! use DMUL
		_pf.DMUL();
	}
	else {
		// No. Its a regular integer MUL
		_pf.MUL();
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processDIV(cdk::node::expression::DIV * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the DIV has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the DIV has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! use DDIV
		_pf.DDIV();
	}
	else {
		// No. Its a regular integer DIV
		_pf.DIV();
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processMOD(cdk::node::expression::MOD * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// Do it!
	_pf.MOD();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processLT(cdk::node::expression::LT * const node, int lvl) {
	
	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the LT has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the LT has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! Do ninja stuff!
		_pf.DCMP();
		_pf.INT(0);
	}

	_pf.LT();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processLE(cdk::node::expression::LE * const node, int lvl) {
	
	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the LE has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the LE has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! Do ninja stuff!
		_pf.DCMP();
		_pf.INT(0);
	}

	_pf.LE();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processGE(cdk::node::expression::GE * const node, int lvl) {
	
	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the GE has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the GE has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! Do ninja stuff!
		_pf.DCMP();
		_pf.INT(0);
	}

	_pf.GE();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processGT(cdk::node::expression::GT * const node, int lvl) {
	
	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the GT has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the GT has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! Do ninja stuff!
		_pf.DCMP();
		_pf.INT(0);
	}

	_pf.GT();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processNE(cdk::node::expression::NE * const node, int lvl) {
	
	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the NE has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the NE has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! Do ninja stuff!
		_pf.DCMP();
		_pf.INT(0);
	}

	_pf.NE();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processEQ(cdk::node::expression::EQ * const node, int lvl) {
	
	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// If the EQ has type double but left child is of type INT, we must convert
	if((node->left()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// If the EQ has type double but right child is of type INT, we must convert
	if((node->right()->type()->name() == ExpressionType::TYPE_INT)
	&& (node->type()->name() == ExpressionType::TYPE_DOUBLE)) {
		_pf.I2D();
	}

	// Is the result supposed to be a double? (operands are already in double representation)
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// Yes! Do ninja stuff!
		_pf.DCMP();
		_pf.INT(0);
	}

	_pf.EQ();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processLeftValue(cpt::node::expression::LeftValue * const node, int lvl) {

	debug(node, lvl);

	//FIXME: When inside a functioncall, must load the value! :(

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Search for an existing symbol with the same identifier
	std::string identifier = node->value();
	Symbol *s = _symtab.find(identifier);

	// Symbol not found! That is an error.
	if(!s) {
		std::cout << identifier << " never existed..." << std::endl;
		//TODO: FATAL ERROR
		return;
	}

	// Check if it is a local variable (or function argument, its the same)
	if(s->symbolType() == "LOCAL VARIABLE") { // THIS IS AWFUL!
		LocalVariableSymbol *lvs = (LocalVariableSymbol*) s;
		_pf.LOCAL(lvs->local_offset());
	}

	// Check if it is a global variable
	if(s->symbolType() == "GLOBAL VARIABLE") { // THIS IS STILL AWFUL!
		GlobalVariableSymbol *gvs = (GlobalVariableSymbol*) s;
		_pf.ADDR(gvs->label());
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processAddressing(cpt::node::expression::Addressing * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Load the leftvalue argument
	node->argument()->accept(this, lvl+1);

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processAND(cpt::node::expression::AND * const node, int lvl) {

	debug(node, lvl);

	int lbl_end = ++_lbl;

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If left child evaluates to false, dont evaluate right child
	// The result is already false on stack (left child)
	duplicateNodeValue(node->left());
	_pf.JZ(mklbl(lbl_end));

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left()); // this is the same as _pf.LOAD();
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right()); // this is the same as _pf.LOAD()
	}

	// Do it!
	_pf.AND();

	// Label to skip right child evaluation
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_end));

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processAssignment(cpt::node::expression::Assignment * const node, int lvl) {

	debug(node, lvl);

	// TODO: Check if going to assign to a constant variable

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Visit the right child
	node->right()->accept(this, lvl+1);

	// If the right value is a left value, it only places
	// its address on top of the stack
	if(isLeftValue(node->right())) {
		// We must load that address contents
		loadNodeValue(node->right());
	}

	// If assigning an integer to a double... we must convert!
	if(node->right()->type()->name() == ExpressionType::TYPE_INT) {
		// convert top of stack to double if node has type double
		convertIfDouble(node);
	}

	// Duplicate right child value (based on size of left value)
	// Only if not used to initialize a variable!
	if(!node->is_initialization()) {
		duplicateNodeValue(node->left());
	}

	// Visit the left child
	node->left()->accept(this, lvl+1);

	// Store the value!
	storeNodeValue(node);

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processDecrement(cpt::node::expression::Decrement * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Visit child
	node->argument()->accept(this, lvl+1);

	// Load the value from the left-value address
	loadNodeValue(node->argument());

	// Should we decrement before using the value?
	if(node->is_prefix()) {
		// Yes! Decrement and then "use" the value
		_pf.INT(1);
		convertIfDouble(node);
		doSubtraction(node); // add 1
		duplicateNodeValue(node);
	}
	else {
		// No! Use the "undecremented" value - decrement later
		duplicateNodeValue(node);
		_pf.INT(1);
		convertIfDouble(node);
		doSubtraction(node); // add 1
	}

	// Visit the left-value again - we need its address to store
	node->argument()->accept(this, lvl+1);

	storeNodeValue(node);

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIncrement(cpt::node::expression::Increment * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Visit child
	node->argument()->accept(this, lvl+1);

	// Load the value from the left-value address
	loadNodeValue(node->argument());

	// Should we increment before using the value?
	if(node->is_prefix()) {
		// Yes! Increment and then "use" the value
		_pf.INT(1);
		convertIfDouble(node);
		doAddition(node); // add 1
		duplicateNodeValue(node); // DUP
	}
	else {
		// No! Use the "unincremented" value - increment later
		duplicateNodeValue(node); // DUP
		_pf.INT(1);
		convertIfDouble(node);
		doAddition(node); // add 1
	}

	// Visit the left-value again - we need its address to store
	node->argument()->accept(this, lvl+1);

	storeNodeValue(node);

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIndexing(cpt::node::expression::Indexing * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Visit pointer child
	node->left()->accept(this, lvl+1);

	if(isLeftValue(node->left())) {
		_pf.LOAD();
	}

	// Visit integer child
	node->right()->accept(this, lvl+1);

	if(isLeftValue(node->right())) {
		_pf.LOAD();
	}

	// Multiply integer by pointer's pointed type size and sum
	_pf.INT(node->left()->type()->subtype()->size());
	_pf.MUL();
	_pf.ADD();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processMemoryReservation(cpt::node::expression::MemoryReservation * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Check if has type unspecified
	if(node->type()->subtype()->name() == ExpressionType::TYPE_UNSPEC) {
		// Fetch correct type from parent assignment
		node->type()->_subtype = node->parent_assignment()->type()->subtype();
	}

	// Place the size of the elements to alloc space for
	_pf.INT(node->type()->subtype()->size());

	// Visit argument to get number of elements
	node->argument()->accept(this, lvl+1);

	// If the argument is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->argument())) {
		// We must load its contents
		loadNodeValue(node->argument());
	}

	// Multiply to get requested allocation space in bytes
	_pf.MUL();

	// Do the allocation (reserves space at the top of the stack!)
	_pf.ALLOC();

	// Push the address of the allocated space to the top of the stack
	_pf.SP(); // Which is the stack pointer

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processNOT(cpt::node::expression::NOT * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Visit argument
	node->argument()->accept(this, lvl+1);

	// If the argument is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->argument())) {
		loadNodeValue(node->argument());
	}

	// One's complement (logical negation)
	_pf.NOT();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processOR(cpt::node::expression::OR * const node, int lvl) {

	debug(node, lvl);

	int lbl1 = ++_lbl;

	// Validate expression type
	PFTypeValidator v(_symtab, node);

	// Visit left child
	node->left()->accept(this, lvl+1);

	// If left child evaluates to true, dont evaluate right child
	// The result is already true on stack (left child)
	duplicateNodeValue(node->left());
	_pf.JNZ(mklbl(lbl1));

	// If the left child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->left())) {
		loadNodeValue(node->left());
	}

	// Visit right child
	node->right()->accept(this, lvl+1);

	// If the right child is a left value, it only places its address
	// onto the top of the stack
	if(isLeftValue(node->right())) {
		loadNodeValue(node->right());
	}

	// Do it!
	_pf.OR();

	// Label to skip right child evaluation
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl1));

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processRead(cpt::node::expression::Read * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// Check if has type unspecified
	if(node->type()->name() == ExpressionType::TYPE_UNSPEC) {
		// Fetch correct type from parent assignment
		node->type(node->parent_assignment()->type());
	}

	// Should we read an integer?
	if(node->type()->name() == ExpressionType::TYPE_INT) {
		if(!_readi_declared) {
			_pf.EXTERN("readi");
			_readi_declared = true;
		}
		_pf.CALL("readi");
		_pf.PUSH();
	}

	// Should we read a double?
	if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
		if(!_readd_declared) {
			_pf.EXTERN("readd");
			_readi_declared = true;
		}
		_pf.CALL("readd");
		_pf.DPUSH();
	}

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processFunctionCall(cpt::node::expression::FunctionCall * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// How much space do we need to trash afterwards?
	PFStackCounter sc(node);

	std::cout << "FUNCTIONCALL: " << node->identifier() << std::endl;
	std::cout << "going to process arguments" << std::endl;
	os() << "; startarguments" << std::endl;
	// Put arguments in the stack (Cdecl covered by grammar)
	if(node->arguments() != NULL) {
		node->arguments()->accept(this, lvl+1);
	}
	std::cout << "Done..." << std::endl;
	os() << ";done" << std::endl;

	// Call the function
	_pf.CALL(node->identifier());

	// Trash arguments (they are no longer needed)
	_pf.TRASH(sc.size());

	// Push function return value to the top of the stack
	Symbol *s = _symtab.find(fixFunctionName(node));
	if((s->type()->name() == ExpressionType::TYPE_INT)
	|| (s->type()->name() == ExpressionType::TYPE_POINTER)
	|| (s->type()->name() == ExpressionType::TYPE_STRING)) {
		// If function returns an integer/pointer/string (4 bytes)
		_pf.PUSH();
	}
	if(s->type()->name() == ExpressionType::TYPE_DOUBLE) {
		// If function returns a double (8 bytes)
		_pf.DPUSH();
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIdentity(cpt::node::expression::Identity * const node, int lvl) {

	debug(node, lvl);

	// Just do type validation
	PFTypeValidator tv(_symtab, node);

	// Visit child
	node->argument()->accept(this, lvl+1);

	// Dont generate any postfix - node used only for type validation

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processExpressionAsInstruction(cpt::node::ExpressionAsInstruction * const node, int lvl) {

	debug(node, lvl);

	// Validate expression type
	node->expression()->accept(this, lvl+1);

	// Trash the unused result from outermost expression
	_pf.TRASH(node->expression()->type()->size());

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processPrintNode(cpt::node::PrintNode * const node, int lvl) {

	debug(node, lvl);

	// push the value to print to the top of the stack
	node->argument()->accept(this, lvl+1);

	// If the argument is a left value, it only places
	// its address on top of the stack
	if(isLeftValue(node->argument())) {
		// We must load that address contents
		loadNodeValue(node->argument());
	}

	// is it an integer?
	if(node->argument()->type()->name() == ExpressionType::TYPE_INT) {
		if(!_printi_declared) {
			_pf.EXTERN("printi");
			_printi_declared = true;
		}
		_pf.CALL("printi"); // call to the print function
		_pf.TRASH(4); // delete the printed value
	}

	// is it a double?
	if(node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE) {
		if(!_printd_declared) {
			_pf.EXTERN("printd");
			_printd_declared = true;
		}
		_pf.CALL("printd"); // call to the print function
		_pf.TRASH(8); // delete the printed value
	}

	// is it a string?
	if(node->argument()->type()->name() == ExpressionType::TYPE_STRING) {
		if(!_prints_declared) {
			_pf.EXTERN("prints");
			_prints_declared = true;
		}
		_pf.CALL("prints"); // call to the print function
		_pf.TRASH(4); // delete the printed value
	}
	
	// do we need to print a newline in the end?
	if(node->print_newline()) {
		if(!_println_declared) {
			_pf.EXTERN("println");
			_println_declared = true;
		}
		_pf.CALL("println"); // print a newline
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processDoWhileNode(cpt::node::DoWhileNode * const node, int lvl) {

	debug(node, lvl);

	int lbl_start = ++_lbl;
	int lbl_end = ++_lbl;
	int lbl_cond = ++_lbl;

	std::string lbl_break = mklbl(lbl_end);
	std::string lbl_continue = mklbl(lbl_cond);

	_break_labels.push_back(lbl_break);
	_continue_labels.push_back(lbl_continue);

	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_start));
	
	// Instruction is done first - it is evaluated at least once
	node->instruction()->accept(this, lvl+1);
	
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_cond)); // for 'continue'

	node->condition()->accept(this, lvl+1);
	_pf.JZ(mklbl(lbl_end)); // end while if condition is false
	_pf.JMP(mklbl(lbl_start)); // otherwise, another lap

	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_end)); // not only but also for 'break'

	_break_labels.pop_back();
	_continue_labels.pop_back();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIfNode(cpt::node::IfNode * const node, int lvl) {
	debug(node, lvl);

	int lbl1;
	node->condition()->accept(this, lvl+1);
	_pf.JZ(mklbl(lbl1 = ++_lbl));
	node->block()->accept(this, lvl+1);
	_pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIfElseNode(cpt::node::IfElseNode * const node, int lvl) {
	debug(node, lvl);

	int lbl1, lbl2;
	node->condition()->accept(this, lvl+1);
	_pf.JZ(mklbl(lbl1 = ++_lbl));
	node->thenblock()->accept(this, lvl+1);
	_pf.JMP(mklbl(lbl2 = ++_lbl));
	_pf.LABEL(mklbl(lbl1));
	node->elseblock()->accept(this, lvl+1);
	_pf.LABEL(mklbl(lbl1 = lbl2));
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processBreakNode(cpt::node::BreakNode * const node, int lvl) {

	debug(node, lvl);

	// Check if programmer is asking the impossible
	if(node->level() > _break_labels.size()) {
		std::cout << node->lineno() << ": Too many levels on that BREAK of yours. That is an error." << std::endl;
		return;
	}

	//std::cout << "LABEL: " << _break_labels[_continue_labels.size() - node->level()] << std::endl;
	_pf.JMP(_break_labels[_continue_labels.size() - node->level()]);

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processContinueNode(cpt::node::ContinueNode * const node, int lvl) {

	debug(node, lvl);

	// Check if programmer is asking the impossible
	if(node->level() > _continue_labels.size()) {
		std::cout << node->lineno() << ": Too many levels on that CONTINUE of yours. That is an error." << std::endl;
		return;
	}

	//std::cout << "LABEL: " << _continue_labels[_continue_labels.size() - node->level()] << std::endl;
	_pf.JMP(_continue_labels[_continue_labels.size() - node->level()]);

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processReturnNode(cpt::node::ReturnNode * const node, int lvl) {

	debug(node, lvl);

	// An alternative to current node implementation would be to jump
	// to the end of the function body ... all we needed was a label

	// Check if used in global context
	if(_current_function == NULL) {
		// FIXME: EXTERMINATE
		std::cout << "WRONG! Cannot return if outside a function! *sigh*" << std::endl;
		return;
	}

	// Place return value on EAX (POP!)
	if(_current_function->type()->name() != ExpressionType::TYPE_VOID) {
		// this is stupid, but gcc was acting strange and i was lazy to find out why
		int return_offset = 0 - _current_function->type()->size();
		_pf.LOCV(return_offset); // push return variable value to stack
		_pf.POP(); // return value goes *POP*
	}
	// End function and return to previous context
	_pf.LEAVE();
	_pf.RET();
	
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processForUpToNode(cpt::node::ForUpToNode * const node, int lvl) {
	
	debug(node, lvl);
	
	int lbl_cond = ++_lbl;
	int lbl_step = ++_lbl;
	int lbl_end = ++_lbl;

	// Break jumps to the end (after for)
	std::string lbl_break = mklbl(lbl_end);
	// Continue jumps to the increment
	std::string lbl_continue = mklbl(lbl_step);

	// Push loop label context
	_break_labels.push_back(lbl_break);
	_continue_labels.push_back(lbl_continue);
	
	// Make initial assignment
	node->make_init_assignment()->accept(this, lvl+1);

	// Evaluate condition
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_cond));
	
	// Make condition expression
	node->make_cond_expression()->accept(this, lvl+1);
	
	// Exit loop if condition is false
	_pf.JZ(mklbl(lbl_end));
	
	// Evaluate block - block is only ran if passes cond
	node->block()->accept(this, lvl+1);
		
	// Evaluate step
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_step)); // Continue jumps here
	node->make_incr_assignment()->accept(this, lvl+1);
	
	// Restart loop
	_pf.JMP(mklbl(lbl_cond));
  
  	// Insert label after loop
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_end)); // Break jumps here
	
	// Remove loop label context
	_break_labels.pop_back();
	_continue_labels.pop_back();

}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processForDownToNode(cpt::node::ForDownToNode * const node, int lvl) {
		
	debug(node, lvl);
	
	int lbl_cond = ++_lbl;
	int lbl_step = ++_lbl;
	int lbl_end = ++_lbl;

	// Break jumps to the end (after for)
	std::string lbl_break = mklbl(lbl_end);
	// Continue jumps to the increment
	std::string lbl_continue = mklbl(lbl_step);

	// Push loop label context
	_break_labels.push_back(lbl_break);
	_continue_labels.push_back(lbl_continue);
	
	// Make initial assignment
	node->make_init_assignment()->accept(this, lvl+1);

	// Evaluate condition
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_cond));
	
	// Make condition expression
	node->make_cond_expression()->accept(this, lvl+1);
	
	// Exit loop if condition is false
	_pf.JZ(mklbl(lbl_end));
	
	// Evaluate block - block is only ran if passes cond
	node->block()->accept(this, lvl+1);
		
	// Evaluate step
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_step)); // Continue jumps here
	node->make_decr_assignment()->accept(this, lvl+1);
	
	// Restart loop
	_pf.JMP(mklbl(lbl_cond));
  
  	// Insert label after loop
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl_end)); // Break jumps here
	
	// Remove loop label context
	_break_labels.pop_back();
	_continue_labels.pop_back();

}

//---------------------------------------------------------------------------
void cpt::semantics::PFwriter::processBlock(cpt::node::Block * const node, int lvl) {

	debug(node, lvl);

	// Push a context
	_symtab.push();

	// Process declarations
	if(node->declarations() != NULL) {
		node->declarations()->accept(this, lvl+1);
	}

	// Process instructions
	if(node->instructions() != NULL) {
		node->instructions()->accept(this, lvl+1);
	}

	// Destroy current block context
	_symtab.pop();
}

//---------------------------------------------------------------------------
void cpt::semantics::PFwriter::processVariableDeclaration(cpt::node::VariableDeclaration * const node, int lvl) {

	debug(node, lvl);

	// FIXME: Should TypeValidate a VariableDeclaration as well
	//        It is currently possible to do integer i = 3.14;

	std::string identifier = node->identifier();

	// Validate expression type
	PFTypeValidator tv(_symtab, node);

	// This declaration is the argument of a function (in function definition)
	if(node->is_function_argument()) {
		// just declare it on symbol table as a local variable with positive offset
		// they are non-static, non-constant local variables
		LocalVariableSymbol *lvs = new LocalVariableSymbol(node->type(), identifier, false, false, _local_arguments_offset);
		_symtab.insert(identifier, lvs);
		_local_arguments_offset += node->type()->size();
		return;
	}

	// This declaration is a LOCAL variable (declared in a block)
	if(!_global_context) {
		// Compute local offset where to store the variable
		_local_declarations_offset -= node->type()->size();
		// Register variable in symbol table
		LocalVariableSymbol *lvs = new LocalVariableSymbol(node->type(), identifier, false, false, _local_declarations_offset);
		_symtab.insert(identifier, lvs);
		// Initialize (if value specified)
		// TODO: Cleanup commented code after checking "makeAssignment" works (it should!)
/*		if(node->initial_value() != NULL) {
			node->initial_value()->accept(this, lvl+1);
			// Is the node a double?
			if(node->type()->name() == ExpressionType::TYPE_DOUBLE) {
				// Is the initial value an integer?
				if(node->initial_value()->type()->name() == ExpressionType::TYPE_INT) {
					// Yes, we must convert to double
					_pf.I2D();
				}
				// Doubles are 'harder' to store...
				_pf.LOCAL(_local_declarations_offset);
				_pf.DSTORE();
			}
			else {
				// Load an integer
				_pf.LOCA(_local_declarations_offset);
			}
		}*/
		if(node->initial_value() != NULL) {
			node->makeAssignment()->accept(this, lvl+1);
		}
	}

	// This declaration is a GLOBAL variable
	else {
		std::string label;
		if(node->is_public()) {
			label = node->identifier();
		}
		else {
			label = mklbl(++_lbl);
		}

		// NOTE: Uninitialized constants are stupid
		// If that happens, throw a rock at the programmer

		// Is the variable uninitialized?
		if(node->initial_value() == NULL) {
			// Just reserve space for it in BSS
			changeSegment(BSS);
			_pf.ALIGN();
			_pf.LABEL(label);
			_pf.BYTE(node->type()->size());
		}

		// Is the variable NOT constant
		else if (!node->is_const()) {
			// Place it in DATA
			changeSegment(DATA);
			_pf.ALIGN();
			_pf.LABEL(label);
			// Special case - assigning an integer to a global double variable
			if((node->type()->name() == ExpressionType::TYPE_DOUBLE)
			&& (node->initial_value()->type()->name() == ExpressionType::TYPE_INT)) {
				_pf.DOUBLE(((cdk::node::expression::Simple<int>*)node->initial_value())->value());
			}
			else {
				node->initial_value()->accept(this, lvl+1);
			}
		}

		// Its a constant!! Oh boy...
		else {
			changeSegment(RODATA);
			if(node->type()->name() == ExpressionType::TYPE_INT) {
				// If it is an int, we can treat it like a non-const variable... phew!
				_pf.ALIGN();
				_pf.LABEL(label);
			}

			node->initial_value()->accept(this, lvl+1);

			if(node->type()->name() != ExpressionType::TYPE_INT) {
				// It is not an int (its a double or a string)!
				// Brace yourselves... a mess is coming
				// We must visit the value first (already did, 5 lines earlier)
				// The node did not load its address (hopefully!)
				changeSegment(RODATA); // just to be sure...
				_pf.ALIGN();
				_pf.LABEL(label);
				_pf.ID(mklbl(_delayed_label)); // plz plz plz ...
			}
		}

		// Do not forget to register variable in symbol table (I know I did!)
		GlobalVariableSymbol *gvs = new GlobalVariableSymbol(node->type(), identifier, node->is_public(), node->is_const(), label);
		_symtab.insert(identifier, gvs);
	}
}

//---------------------------------------------------------------------------
void cpt::semantics::PFwriter::processFunctionDeclaration(cpt::node::FunctionDeclaration * const node, int lvl) {
	debug(node, lvl);

	std::string identifier = fixFunctionName(node);
	FunctionSymbol *fs = (FunctionSymbol*)_symtab.find(identifier);

	// Check if there is a previous declaration with this ID
	if(fs == nullptr) {
		// Previous declaration not found - declare it now
		fs = new FunctionSymbol(node->type(), identifier, node->is_public(), false);
		_symtab.insert(identifier, fs);
	}
	else {
		// Previous declaration could be here - dont insert another symbol
		//TODO: Check if return value and arguments match
		//      If they dont... FATAL ERROR!!! and kill the programmer
	}
}

//---------------------------------------------------------------------------
void cpt::semantics::PFwriter::processFunctionDefinition(cpt::node::FunctionDefinition * const node, int lvl) {

	debug(node, lvl);

	std::string identifier = fixFunctionName(node);
	PFStackCounter sc(node);

	// Repeat stuff that is done for a declaration as well
	node->makeDeclaration()->accept(this, lvl+1);
	FunctionSymbol *fs = (FunctionSymbol*)_symtab.find(identifier);

	// Push function context
	_symtab.push();
	_global_context = false;
	_current_function = fs;
	_local_arguments_offset = +8; // where are my arguments?
	_local_declarations_offset = 0; // where are my local variables?

	if(fs->is_defined()) {
		// Function has been defined already! Bad, bad programmer!!
		std::cerr << "[" << node->lineno() << "] FATAL: Previous definition of function " << identifier << " found." << std::endl;
		return;
	}
	else {
		// Function has been declared but not defined - define it now
		// Define it now
		fs->is_defined(true);
	}

	// Switch to TEXT segment
	changeSegment(TEXT);

	if(node->is_public()) {
		// Register name globally as a function
		_pf.GLOBAL(identifier, _pf.FUNC());
	}

	// Actual Postfix code starts here
	// Create a label at top of function code
	_pf.ALIGN();
	_pf.LABEL(identifier);

	// Reserve stack space for local variables
	_pf.ENTER(sc.size());

	// Process function arguments - just declare them on the symbol table
	if(node->arguments() != NULL)
		node->arguments()->accept(this, lvl+1);

	// Create variable with the same name as the function to store the return value
	node->makeReturnVariableDeclaration()->accept(this, lvl+1);

	// Generate postfix for function body
	node->block()->accept(this, lvl+1);

	// Place return value on EAX (POP!)
	if(node->type()->name() != ExpressionType::TYPE_VOID) {
		// this is stupid, but gcc was acting strange and i was lazy to find out why
		int return_offset = 0 - node->type()->size();
		_pf.LOCV(return_offset); // push return variable value to stack
		_pf.POP(); // return value goes *POP*
	}
	// End function and return to previous context
	_pf.LEAVE();
	_pf.RET();

	// Destroy function context
	_symtab.pop();
	_global_context = true;
	_current_function = NULL;

}

//---------------------------------------------------------------------------
//		 T H E		E N D
//---------------------------------------------------------------------------
// $Log: PFwriter.cpp,v $
// Revision 1.69  2013-05-20 19:31:31  ist164787
// misc fixes
//
// Revision 1.68  2013-05-20 13:19:56  ist164787
// fixed fornode visitors... code cleanup
//
// Revision 1.67  2013-05-20 05:18:13  ist164788
// ForUpToNode
//
// Revision 1.66  2013-05-19 14:46:12  ist164787
// tried to fix public global variables
//
// Revision 1.65  2013-05-19 14:39:26  ist164787
// fixed problem with indexing node - was using type size instead of subtype size...
//
// Revision 1.64  2013-05-19 11:05:59  ist164787
// Read working
//
// Revision 1.63  2013-05-19 10:46:59  ist164787
// Memory reservation seems to be working... partially well
//
// Revision 1.62  2013-05-17 23:15:52  ist164787
// bugfix in xmlwriter, fixme note...
//
// Revision 1.61  2013-05-17 22:26:16  ist164787
// Fixed warning; removed unnecessary chattery; did BREAK node - copy pasted from CONTINUE... easy!
//
// Revision 1.60  2013-05-17 22:20:27  ist164787
// Continue working, fixed While node in exchange for a DoWhile node
//
// Revision 1.59  2013-05-17 21:29:20  ist164787
// changed function name so it is a lot clearer now
//
// Revision 1.58  2013-05-17 19:39:48  ist164787
// fixed jumps in OR and AND expressions
//
// Revision 1.57  2013-05-17 19:12:17  ist164787
// Fixed local variable declaration without initialization... sigh
//
// Revision 1.56  2013-05-16 21:55:35  ist164787
// Changed the way variables are initialized; Fixed a problem when using integer left values that would be converted to doubles *sigh* that was really lol!
//
// Revision 1.55  2013-05-16 21:03:41  ist164787
// Fixed when assigning integers to numbers
//
// Revision 1.54  2013-05-16 19:31:28  ist164787
// Refactoring and fixes
//
// Revision 1.53  2013-05-16 16:49:05  ist164787
// MOAR REFACTORING!
//
// Revision 1.52  2013-05-16 16:30:34  ist164787
// Refactoring
//
// Revision 1.51  2013-05-16 16:17:35  ist164787
// Fixed global doubles and operations with doubles... messy code... needs refactoringcvs diff
//
// Revision 1.50  2013-05-16 14:25:24  ist164787
// Fixed double variable declarations
//
// Revision 1.49  2013-05-15 19:51:27  ist164787
// Return node works... I hope
//
// Revision 1.48  2013-05-15 19:28:34  ist164787
// Global constants; Print node fixed for doubles; Global doubles initialized with integers fixed
//
// Revision 1.47  2013-05-15 12:51:54  ist164787
// Nested block declarations in functions working, fixed block attribute name from definitions to instructions... seems legit now
//
// Revision 1.46  2013-05-15 11:05:04  ist164787
// Segment management functions
//
// Revision 1.45  2013-05-14 22:23:08  ist164787
// Forgot to remove FIXME comment on OR node - already fixed in previous commit
//
// Revision 1.44  2013-05-14 22:22:03  ist164787
// ADD/OR nodes: do not evaluate right child if left child is false/true, respectivelly
//
// Revision 1.43  2013-05-14 22:01:01  ist164787
// Fixed string when used in global context (only works if used in DATA though)
//
// Revision 1.42  2013-05-14 21:52:53  ist164787
// minor bugfixes
//
// Revision 1.41  2013-05-14 14:41:24  ist164787
// bugfixes in many expressions when dealing with leftvalues, bugfix in print nodes; fixed a bug for increment node on typevalidator
//
// Revision 1.40  2013-05-14 12:08:17  ist164787
// Fixed most binary expressions when dealing with left values, as they only push their addresses when visited, not their values... some nodes still need to be modified to reflect these changes
//
// Revision 1.39  2013-05-14 00:17:45  ist164787
// Lots of PFwriter wrote. Lots of TypeValidator validated. See what I did there?
//
// Revision 1.38  2013-05-13 21:01:17  ist164787
// TypeValidator almost finished, Function Calls are full of awesome, printnode prints everything... other minor changes i dont remember
//
// Revision 1.37  2013-05-13 19:10:06  ist164787
// ExpressionAsInstruction node added
//
// Revision 1.36  2013-05-13 18:34:03  ist164787
// Fixed identifier and leftvalue confusion... added identity node for type validation... refactored typevalidator code
//
// Revision 1.35  2013-05-13 15:52:44  ist164787
// Added some more methods to TypeValidator
//
// Revision 1.34  2013-05-12 22:29:55  ist164787
// Fixed a lex error on doubles - was using yylval.i instead of yylval.dvim Makefile  Awfulvim Makefile  Did a bit of TypeValidator (simple nodes, and ADD and SUB binary expressions)... theres also a template for binary expressions - the common stuff. Also did the ADD on PFwriter - not sure if everything is finished, though!
//
// Revision 1.33  2013-05-12 14:17:19  ist164787
// Added TypeValidator, does nothing yet
//
// Revision 1.32  2013-05-12 13:16:51  ist164787
// Function arguments and return values working, I believe.. Function call doesnt work, though
//
// Revision 1.31  2013-05-11 23:36:57  ist164787
// Function arguments working in proper order AFAIK. Left values only work as Right Values (and if identifier is local variable)... other stuff less important...
//
// Revision 1.30	2013-05-11 22:15:30	ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.29	2013-05-11 18:18:41	ist164787
// function declarations working, part of vardecls working
//
// Revision 1.28	2013-05-11 15:35:35	ist164787
// vardecls in pfwriter - began changes
//
// Revision 1.27	2013-05-10 22:22:10	ist164787
// forgot to add FunctionSymbol file; fixed return value POP
//
// Revision 1.26	2013-05-10 13:03:36	ist164787
// Fixed FunctionSymbol arguments. FunctionSymbol is now being added to the Symbol Table on FunctionDefinition node processing
//
// Revision 1.25	2013-05-09 21:20:16	ist164787
// minor changes
//
// Revision 1.24	2013-05-09 15:51:23	ist164787
// Small changes on FunctionDefinition and StackCounter
//
// Revision 1.23	2013-05-08 22:49:05	ist164787
// - Added StackCounter - a visitor to compute the necessary space for local
// variables (works for both functiondefinition and block nodes)
// - Removed unused dumb function in grammar file.y
//
// Revision 1.22	2013-05-08 18:16:17	ist164787
// removed symbol subclasses - variablesymbol and functionsymbol
//
// Revision 1.21	2013-05-08 11:53:49	ist164787
// print functions and main function working -- function declarations, function arguments and function local variables DO NOT WORK
//
// Revision 1.20	2013-05-07 19:03:05	ist164787
// added missing files... oops
//
// Revision 1.19	2013-04-29 16:27:07	ist164787
// Compiler already produces a ASM file (doesnt do anything, though)
//
// Revision 1.17	2013-04-24 10:48:10	ist164787
// Removed Function Argument, misc minor changes
//
// Revision 1.16	2013-04-16 18:54:09	ist164787
// Added a new node: FunctionArgument. This represents an argument in a function declaration/definition
// Syntax tree is now being built (not tested)
//
// Revision 1.15	2013-04-14 20:59:23	ist164787
// MAJOR CHANGES in .y and .l and some XMLwriter.cpp; The return of LeftValue expression node
//
// Revision 1.14	2013-03-26 11:16:22	ist164787
// Reused some of compact semantics
//
// Revision 1.13	2013-03-26 11:12:31	ist164787
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
// Revision 1.8	2013-03-25 18:48:07	ist164787
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
// Revision 1.12	2012/04/10 19:10:45	david
// Minor comment cleanup.
//
// Revision 1.11	2012/04/10 19:09:47	david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.10	2012/02/18 19:37:58	david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
