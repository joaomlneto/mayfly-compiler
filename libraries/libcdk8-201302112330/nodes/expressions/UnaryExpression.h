// $Id: UnaryExpression.h,v 1.9 2013/02/09 19:00:34 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_EXPRESSION_UNARYEXPRESSION_H__
#define __CDK8_NODE_EXPRESSION_UNARYEXPRESSION_H__

#include <cdk/nodes/expressions/Expression.h>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {
    namespace expression {

      //!
      //! Class for describing unary operators.
      //!
      class UnaryExpression: public Expression {
        Expression *_argument;

      public:
        inline UnaryExpression(int lineno, Expression *arg) :
          Expression(lineno), _argument(arg) {
        }

        inline Expression *argument() {
          return _argument;
        }

      };

    } // expression
  } // node
} // cdk

#endif

// $Log: UnaryExpression.h,v $
// Revision 1.9  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.8  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.7  2012/03/06 15:07:45  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
