#ifndef __MF_NODE_EXPRESSION_AND_H__
#define __MF_NODE_EXPRESSION_AND_H__

#include <cdk/nodes/expressions/BinaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing the lower-than-or-equal operator
       */
      class AND: public cdk::node::expression::BinaryExpression {
      public:
        /**
         * @param lineno source code line number for this nodes
         * @param left first operand
         * @param right second operand
         */
        inline AND(int lineno, Expression *left, Expression *right) :
          BinaryExpression (lineno, left, right) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "AND";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processAND(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif
