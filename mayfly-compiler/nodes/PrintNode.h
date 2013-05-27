// $Id: PrintNode.h,v 1.3 2013-04-16 18:54:09 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_PRINTNODE_H__
#define __MF_PRINTNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing print nodes.
     */
    class PrintNode: public cdk::node::Node {
      cdk::node::expression::Expression *_argument;
		bool _print_newline;

    public:
      inline PrintNode(int lineno, cdk::node::expression::Expression *argument, bool print_newline) :
          cdk::node::Node(lineno), _argument(argument), _print_newline(print_newline) {
      }

    public:
      inline cdk::node::expression::Expression *argument() {
        return _argument;
      }

		inline bool print_newline() {
		  return _print_newline;
		}

      const char *name() const {
        return "PrintNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processPrintNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: PrintNode.h,v $
// Revision 1.3  2013-04-16 18:54:09  ist164787
// Added a new node: FunctionArgument. This represents an argument in a function declaration/definition
// Syntax tree is now being built (not tested)
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
