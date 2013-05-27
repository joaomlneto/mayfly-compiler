#ifndef __MF_NODE_EXPRESSION_ASSIGNMENT_H__
#define __MF_NODE_EXPRESSION_ASSIGNMENT_H__

#include <cdk/nodes/expressions/BinaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing the lower-than-or-equal operator
       */
      class Assignment: public cdk::node::expression::BinaryExpression {
		private:
			bool _is_initialization;
      public:
        /**
         * @param lineno source code line number for this nodes
         * @param left first operand
         * @param right second operand
         */
        inline Assignment(int lineno, Expression *left, Expression *right, bool is_initialization = false) :
          BinaryExpression (lineno, left, right), _is_initialization(is_initialization) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "Assignment";
        }

		  const bool is_initialization() const {
		  	return _is_initialization;
		  }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processAssignment(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif
