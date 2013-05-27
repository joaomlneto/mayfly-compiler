#ifndef __MF_NODE_EXPRESSION_NOT_H__
#define __MF_NODE_EXPRESSION_NOT_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing the negation operator
       */
      class NOT: public cdk::node::expression::UnaryExpression {
      public:
        inline NOT(int lineno, Expression *arg) :
          UnaryExpression(lineno, arg) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "NOT";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processNOT(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif
