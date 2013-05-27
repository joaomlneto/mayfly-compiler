// $Id: Expression.h,v 1.12 2013/02/11 20:56:51 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_EXPRESSION_EXPRESSION_H__
#define __CDK8_NODE_EXPRESSION_EXPRESSION_H__

#include <cdk/nodes/Node.h>
#include "semantics/ExpressionType.h"

namespace cdk {
  namespace node {
    namespace expression {

      /**
       * Expressions are typed nodes, i.e., able to store
       * a type description.
       */
      class Expression: public cdk::node::Node {
      protected:
        // This must be a pointer, so that we can anchor a dynamic
        // object and be able to change/delete it afterwards.
        ExpressionType *_type;

      public:
        /**
         * Simple constructor.
         *
         * @param lineno the source code line number corresponding to
         * the node
         */
        inline Expression(int lineno) :
            cdk::node::Node(lineno), _type(nullptr) {
        }

        virtual ExpressionType *type() {
          return _type;
        }
        virtual void type(ExpressionType *type) {
          _type = type;
        }

      };

    }// expression
  } // node
} // cdk

#endif

// $Log: Expression.h,v $
// Revision 1.12  2013/02/11 20:56:51  david
// *** empty log message ***
//
// Revision 1.11  2013/02/09 19:00:33  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.10  2012/04/10 19:01:04  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.9  2012/03/06 15:07:45  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
