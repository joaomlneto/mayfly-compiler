#ifndef __MF_NODE_EXPRESSION_ADDRESSING_H__
#define __MF_NODE_EXPRESSION_ADDRESSING_H__

#include <cdk/nodes/expressions/BinaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing the addressing expression
       */
      class Addressing: public cdk::node::expression::UnaryExpression {
      public:
        /**
         * @param lineno source code line number for this nodes
         * @param left pointer
         * @param right index
         */
        inline Addressing(int lineno, cdk::node::expression::Expression *lval) :
          UnaryExpression(lineno, lval) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "Addressing";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processAddressing(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif
