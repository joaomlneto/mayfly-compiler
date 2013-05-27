// $Id: DoWhileNode.h,v 1.3 2013-04-16 18:54:08 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_DOWHILENODE_H__
#define __MF_DOWHILENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing while-cycle nodes.
     */
    class DoWhileNode: public cdk::node::Node {
      cdk::node::Node *_instruction;
      cdk::node::expression::Expression *_condition;

    public:
      inline DoWhileNode(int lineno, cdk::node::Node *instruction, cdk::node::expression::Expression *condition) :
          cdk::node::Node(lineno), _instruction(instruction), _condition(condition) {
      }

    public:
      inline cdk::node::expression::Expression *condition() {
        return _condition;
      }
      inline cdk::node::Node *instruction() {
        return _instruction;
      }

      const char *name() const {
        return "DoWhileNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processDoWhileNode(this, level);
      }

    };

  }// namespace node
} // namespace mayfly

#endif

