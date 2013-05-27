// $Id: FunctionDefinition.h,v 1.9 2013-05-12 13:16:51 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_FUNCTIONDEFINITION_H__
#define __MF_FUNCTIONDEFINITION_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/Sequence.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/nodes/Nil.h>
#include "nodes/FunctionDeclaration.h"
#include "nodes/VariableDeclaration.h"

namespace mayfly {
  namespace node {

    /**
     * Class for describing print nodes.
     */
    class FunctionDefinition: public cdk::node::Node {
	 	ExpressionType *_type;
		bool _is_public;
		std::string _identifier;
		cdk::node::Sequence *_arguments;
		cdk::node::expression::Expression *_literal;
		cdk::node::Node *_block;

    public:
      inline FunctionDefinition(int lineno, ExpressionType *type, bool is_public, std::string *identifier, cdk::node::Sequence *arguments, cdk::node::expression::Expression *literal, cdk::node::Node *block) :
          cdk::node::Node(lineno), _type(type), _is_public(is_public), _identifier(*identifier), _arguments(arguments), _literal(literal), _block(block) {
      }

		inline FunctionDefinition(int lineno, mayfly::node::FunctionDeclaration *fdecl, cdk::node::Node *block) :
			FunctionDefinition(lineno, fdecl->type(), fdecl->is_public(), new std::string(fdecl->identifier()), fdecl->arguments(), fdecl->literal(), block) {
		}

    public:
      inline ExpressionType *type() {
        return _type;
      }

      inline bool is_public() {
        return _is_public;
      }

      inline std::string identifier() {
        return _identifier;
      }

      inline cdk::node::Sequence *arguments() {
        return _arguments;
      }

		inline cdk::node::expression::Expression *literal() {
			return _literal;
		}

      inline cdk::node::Node *block() {
        return _block;
      }

      const char *name() const {
        return "FunctionDefinition";
      }

		mayfly::node::FunctionDeclaration *makeDeclaration() {
			return new mayfly::node::FunctionDeclaration(lineno(), type(), is_public(), new std::string(identifier()), arguments(), literal());
		}

		mayfly::node::VariableDeclaration *makeReturnVariableDeclaration() {
			return new mayfly::node::VariableDeclaration(lineno(), type(), new std::string(identifier()), false, false, literal());
		}

      void accept(SemanticProcessor *sp, int level) {
        sp->processFunctionDefinition(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: FunctionDefinition.h,v $
// Revision 1.9  2013-05-12 13:16:51  ist164787
// Function arguments and return values working, I believe.. Function call doesnt work, though
//
// Revision 1.8  2013-05-11 22:15:27  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.7  2013-05-09 21:20:16  ist164787
// minor changes
//
// Revision 1.6  2013-04-29 16:27:07  ist164787
// Compiler already produces a ASM file (doesnt do anything, though)
//
// Revision 1.5  2013-04-24 10:48:10  ist164787
// Removed Function Argument, misc minor changes
//
// Revision 1.4  2013-04-22 16:46:06  ist164787
// Added missing include of FunctionDeclaration on FunctionDefinition.h
//
// Revision 1.3  2013-04-18 14:37:05  ist164787
// completed grammar, fixed some stuff on grammar and added alternative constructors for FunctionDefinition and Indexing nodes
//
// Revision 1.2  2013-04-14 20:59:23  ist164787
// MAJOR CHANGES in .y and .l and some XMLwriter.cpp; The return of LeftValue expression node
//
// Revision 1.1  2013-03-25 19:13:19  ist164787
// Added FunctionDefinition node
//
// Revision 1.1  2013-03-25 19:07:17  ist164787
// Added FunctionDefinition node
//
// Revision 1.1  2013-03-25 18:55:44  ist164787
// Added FunctionDefinition node
//
// Revision 1.2  2013-03-25 18:48:07  ist164787
// Added Block node
//
// Revision 1.1  2013-02-16 16:10:13  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.7  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.6  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
