// $Id: String.h,v 1.9 2013/02/09 19:00:33 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_EXPRESSION_STRING_H__
#define __CDK8_NODE_EXPRESSION_STRING_H__

#include <string>
#include <cdk/nodes/expressions/Simple.h>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding string
       * values.
       */
      class String: public virtual Simple<std::string> {
      public:
        inline String(int lineno, const char *s) :
            Simple<std::string>(lineno, s) {
        }
        inline String(int lineno, const std::string &s) :
            Simple<std::string>(lineno, s) {
        }
        inline String(int lineno, const std::string *s) :
            Simple<std::string>(lineno, *s) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "String";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processString(this, level);
        }

      };

    } // expression
  } // node
} // cdk

#endif

// $Log: String.h,v $
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
