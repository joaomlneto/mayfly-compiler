// $Id: Double.h,v 1.10 2013/02/11 20:56:51 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_EXPRESSION_DOUBLE_H__
#define __CDK8_NODE_EXPRESSION_DOUBLE_H__

#include <cdk/nodes/expressions/Simple.h>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding double
       * precision values.
       */
      class Double: public virtual Simple<double> {
      public:
        inline Double(int lineno, double d) :
            Simple<double>(lineno, d) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "Double";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processDouble(this, level);
        }

      };

    } // expression
  } // node
} // cdk

#endif

// $Log: Double.h,v $
// Revision 1.10  2013/02/11 20:56:51  david
// *** empty log message ***
//
// Revision 1.9  2013/02/09 19:00:33  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.8  2012/04/10 19:01:04  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.7  2012/03/06 15:07:45  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
