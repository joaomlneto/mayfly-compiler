// $Id: BinaryExpression.h,v 1.10 2013/02/09 19:00:33 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_EXPRESSION_BINARYEXPRESSION_H__
#define __CDK8_NODE_EXPRESSION_BINARYEXPRESSION_H__

#include <cdk/nodes/expressions/Expression.h>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {
    namespace expression {

      /**
       * Class for describing binary operators.
       */
      class BinaryExpression: public Expression {
        Expression *_left, *_right;

      public:
        /**
         * @param lineno source code line number for this nodes
         * @param left first operand
         * @param right second operand
         */
        inline BinaryExpression(int lineno, Expression *left, Expression *right) :
            Expression(lineno), _left(left), _right(right) {
        }

        inline Expression *left() {
          return _left;
        }
        inline Expression *right() {
          return _right;
        }

      };

    } // expression
  } // node
} // cdk

#endif

// $Log: BinaryExpression.h,v $
// Revision 1.10  2013/02/09 19:00:33  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.9  2012/04/10 19:01:04  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.8  2012/03/06 15:07:45  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
