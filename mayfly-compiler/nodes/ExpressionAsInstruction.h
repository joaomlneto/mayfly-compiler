// $Id: ExpressionAsInstruction.h,v 1.1 2013-05-13 19:10:05 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_EXPRESSIONASINSTRUCTION_H__
#define __MF_EXPRESSIONASINSTRUCTION_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing read nodes.
     */
    class ExpressionAsInstruction: public cdk::node::Node {
      cdk::node::expression::Expression *_expression;

    public:
		inline ExpressionAsInstruction(int lineno, cdk::node::expression::Expression * expression) :
			cdk::node::Node(lineno), _expression(expression) {
		}

    public:
      inline cdk::node::expression::Expression *expression() {
        return _expression;
      }

      const char *name() const {
        return "ExpressionAsInstruction";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processExpressionAsInstruction(this, level);
      }

    };

  }// namespace node
} // namespace mayfly

#endif

