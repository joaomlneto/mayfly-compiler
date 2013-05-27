#ifndef __MF_NODE_EXPRESSION_READ_H__
#define __MF_NODE_EXPRESSION_READ_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include "SemanticProcessor.h"

namespace mayfly {
	namespace node {
		namespace expression {
			/**
			 * Class for describing the negation operator
			 */
			class Read: public cdk::node::expression::Expression {
			private:
	 			mayfly::node::expression::Assignment *_parent_assignment = NULL;

			public:
				inline Read(int lineno) :
					Expression(lineno) {
				}

				/**
				 * @return the name of the node's class
				 */
				const char *name() const {
					return "Read";
				}

				void parent_assignment(mayfly::node::expression::Assignment * const parent_assignment) {
					_parent_assignment = parent_assignment;
				}

				mayfly::node::expression::Assignment * parent_assignment() {
					return _parent_assignment;
				}

				/**
				 * @param sp semantic processor visitor
				 * @param level syntactic tree level
				 */
				virtual void accept(SemanticProcessor *sp, int level) {
					sp->processRead(this, level);
				}

			};

		} // expression
	} // node
} // mayfly

#endif
