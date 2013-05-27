#ifndef __MF_NODE_EXPRESSION_FUNCTIONCALL_H__
#define __MF_NODE_EXPRESSION_FUNCTIONCALL_H__

#include <cdk/nodes/expressions/BinaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing the lower-than-or-equal operator
       */
      class FunctionCall: public cdk::node::expression::Expression {
		protected:
			std::string _identifier;
			cdk::node::Sequence *_arguments;
      public:
        /**
         * @param lineno source code line number for this nodes
         * @param name function name
         * @param arguments function arguments
         */
        inline FunctionCall(int lineno, std::string *identifier, cdk::node::Sequence *arguments) :
          Expression(lineno), _identifier(*identifier), _arguments(arguments) {
        }

		  inline std::string identifier() {
		    return _identifier;
		  }

        inline cdk::node::Sequence *arguments() {
		    return _arguments;
		  }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "FunctionCall";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processFunctionCall(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif
