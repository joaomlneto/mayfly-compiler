// $Id: VariableDeclaration.h,v 1.5 2013-05-16 21:55:35 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_VARIABLEDECLARATION_H__
#define __MF_VARIABLEDECLARATION_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include "nodes/expression/Assignment.h"
#include "nodes/expression/LeftValue.h"

namespace mayfly {
  namespace node {

    /**
     * Class for describing print nodes.
     */
    class VariableDeclaration: public cdk::node::Node {
	 	ExpressionType *_type;
		std::string _identifier;
		bool _is_public, _is_const;
		cdk::node::expression::Expression *_initial_value;
		bool _is_function_argument; // is it a function argument on a function definition?

    public:
      inline VariableDeclaration(int lineno,
		                           ExpressionType *type,
		                           std::string *identifier,
		                           bool is_public = false,
		                           bool is_const = false,
		                           cdk::node::expression::Expression *initial_value = NULL,
		                           bool is_function_argument = false) :
          cdk::node::Node(lineno), _type(type), _identifier(*identifier), _is_public(is_public), _is_const(is_const), _initial_value(initial_value), _is_function_argument(is_function_argument) {
      }

    public:
      inline ExpressionType *type() {
        return _type;
      }

      inline std::string identifier() {
        return _identifier;
      }

      inline bool is_public() {
        return _is_public;
      }

      inline bool is_const() {
        return _is_const;
      }

      inline cdk::node::expression::Expression *initial_value() {
        return _initial_value;
      }

		inline bool is_function_argument() {
			return _is_function_argument;
		}

      const char *name() const {
        return "VariableDeclaration";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processVariableDeclaration(this, level);
      }

		mayfly::node::expression::Assignment *makeAssignment() {
			return new mayfly::node::expression::Assignment(lineno(),
				new mayfly::node::expression::LeftValue(lineno(), identifier()),
				initial_value(),
				true); // true = it is the initialization of a variable
		}

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: VariableDeclaration.h,v $
// Revision 1.5  2013-05-16 21:55:35  ist164787
// Changed the way variables are initialized; Fixed a problem when using integer left values that would be converted to doubles *sigh* that was really lol!
//
// Revision 1.4  2013-05-11 22:15:27  ist164787
// Function arguments may be working... havent tested lol
//
// Revision 1.3  2013-05-09 21:20:16  ist164787
// minor changes
//
// Revision 1.2  2013-04-16 19:58:29  ist164787
// fixed syntax tree building - it was segfaulting
//
// Revision 1.1  2013-03-25 18:55:44  ist164787
// Added VariableDeclaration node
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
