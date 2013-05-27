// $Id: Simple.h,v 1.9 2013/02/09 19:00:33 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_EXPRESSION_SIMPLE_H__
#define __CDK8_NODE_EXPRESSION_SIMPLE_H__

#include <cdk/nodes/expressions/Expression.h>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding simple
       * (atomic) types. This is a template class that will be instantiated
       * by the various classes for holding specific leaves.
       *
       * @param VisitorType is the type for visitor classes
       * @param StoredType is the type held by the leaf
       * @see Double, Integer, String
       */
      template<typename StoredType>
      class Simple: public Expression {
        StoredType _value;

      public:
        inline Simple(int lineno, const StoredType &value) :
            Expression(lineno), _value(value) {
        }

        inline const StoredType &value() const {
          return _value;
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "Simple";
        }

      };

    } // expression
  } // node
} // cdk

#endif

/*
 * $Log: Simple.h,v $
 * Revision 1.9  2013/02/09 19:00:33  david
 * First CDK8 commit. Major code simplification.
 * Starting C++11 implementation.
 *
 * Revision 1.8  2012/04/10 19:01:04  david
 * Removed initialization-dependent static members in factories.
 * Handling of ProgramNodes is now better encapsulated by visitors (not done
 * by evaluators, as before). Major cleanup (comments).
 *
 * Revision 1.7  2012/03/06 15:07:45  david
 * Added subtype to ExpressionType. This allows for more expressiveness in
 * type description.
 *
 */
