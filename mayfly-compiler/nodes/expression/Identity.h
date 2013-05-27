#ifndef __MF_NODE_EXPRESSION_IDENTITY_H__
#define __MF_NODE_EXPRESSION_IDENTITY_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing the negation operator
       */
      class Identity: public cdk::node::expression::UnaryExpression {
      public:
        inline Identity(int lineno, Expression *arg) :
          UnaryExpression(lineno, arg) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "Identity";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processIdentity(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif
