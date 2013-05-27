#ifndef __MF_NODE_EXPRESSION_MEMORYRESERVATION_H__
#define __MF_NODE_EXPRESSION_MEMORYRESERVATION_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include "nodes/expression/Assignment.h"
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing the negation operator
       */
      class MemoryReservation: public cdk::node::expression::UnaryExpression {
		mayfly::node::expression::Assignment *_parent_assignment = NULL;

      public:
        inline MemoryReservation(int lineno, Expression *arg) :
          UnaryExpression(lineno, arg) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "MemoryReservation";
        }

		  inline void parent_assignment(mayfly::node::expression::Assignment *parent_assignment) {
		  	_parent_assignment = parent_assignment;
		  }

		  inline mayfly::node::expression::Assignment *parent_assignment() {
		  	return _parent_assignment;
		  }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processMemoryReservation(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif
