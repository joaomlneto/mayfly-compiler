// $Id: FunctionDeclaration.h,v 1.3 2013-05-09 21:20:15 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_FUNCTIONDECLARATION_H__
#define __MF_FUNCTIONDECLARATION_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/Sequence.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing print nodes.
     */
    class FunctionDeclaration: public cdk::node::Node {
	 	ExpressionType *_type;
		bool _is_public;
		std::string _identifier;
		cdk::node::Sequence *_arguments;
		cdk::node::expression::Expression *_literal;

    public:
      inline FunctionDeclaration(int lineno, ExpressionType *type, bool is_public, std::string *identifier, cdk::node::Sequence *arguments, cdk::node::expression::Expression *literal) :
          cdk::node::Node(lineno), _type(type), _is_public(is_public), _identifier(*identifier), _arguments(arguments), _literal(literal) {
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

      const char *name() const {
        return "FunctionDeclaration";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processFunctionDeclaration(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: FunctionDeclaration.h,v $
// Revision 1.3  2013-05-09 21:20:15  ist164787
// minor changes
//
// Revision 1.2  2013-04-16 18:54:09  ist164787
// Added a new node: FunctionArgument. This represents an argument in a function declaration/definition
// Syntax tree is now being built (not tested)
//
// Revision 1.1  2013-03-25 19:07:17  ist164787
// Added FunctionDeclaration node
//
// Revision 1.1  2013-03-25 18:55:44  ist164787
// Added FunctionDeclaration node
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
