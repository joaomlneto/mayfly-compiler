// $Id: ForUpToNode.h,v 1.5 2013-05-20 13:33:17 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_FORUPTONODE_H__
#define __MF_FORUPTONODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/nodes/expressions/ADD.h>
#include <cdk/nodes/expressions/LE.h>
#include <cdk/nodes/expressions/Integer.h>
#include "nodes/expression/Assignment.h"

namespace mayfly {
  namespace node {

    /**
     * Class for describing ForUpTo-cycle nodes.
     */
    class ForUpToNode: public cdk::node::Node {
      cdk::node::expression::Expression *_leftvalue, *_start, *_end, *_step;
      cdk::node::Node *_block;

    public:
      inline ForUpToNode(int lineno,
		                   cdk::node::expression::Expression *leftvalue,
		                   cdk::node::expression::Expression *start,
		                   cdk::node::expression::Expression *end,
		                   cdk::node::expression::Expression *step,
								 cdk::node::Node *block) :
          cdk::node::Node(lineno), _leftvalue(leftvalue), _start(start), _end(end), _step(step), _block(block) {
			 if(step == NULL) {
			 	_step = new cdk::node::expression::Integer(lineno, 1);
			 }
      }

    public:
      inline cdk::node::expression::Expression *leftvalue() {
        return _leftvalue;
      }
		inline cdk::node::expression::Expression *start() {
        return _start;
      }
		inline cdk::node::expression::Expression *end() {
        return _end;
      }
		inline cdk::node::expression::Expression *step() {
        return _step;
      }
      inline cdk::node::Node *block() {
        return _block;
      }

      const char *name() const {
        return "ForUpToNode";
      }

		inline mayfly::node::expression::Assignment *make_init_assignment() {
			return new mayfly::node::expression::Assignment(
				lineno(),
				leftvalue(),
				start(),
				true);
		}

		inline cdk::node::expression::LE *make_cond_expression() {
			return new cdk::node::expression::LE(
				lineno(),
				leftvalue(),
				end());
		}

		inline mayfly::node::expression::Assignment *make_incr_assignment() {
			return new mayfly::node::expression::Assignment(
				lineno(),
				leftvalue(),
				new cdk::node::expression::ADD(
					lineno(),
					leftvalue(),
					step()),
				true);

		}

      void accept(SemanticProcessor *sp, int level) {
        sp->processForUpToNode(this, level);
      }

    };

  }// namespace node
} // namespace mayfly

#endif

