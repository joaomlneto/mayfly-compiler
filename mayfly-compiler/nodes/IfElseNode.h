// $Id: IfElseNode.h,v 1.3 2013-04-16 18:54:09 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_IFELSENODE_H__
#define __MF_IFELSENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing if-then-else nodes.
     */
    class IfElseNode: public cdk::node::Node {
      cdk::node::expression::Expression *_condition;
      cdk::node::Node *_thenblock, *_elseblock;

    public:
      inline IfElseNode(int lineno, cdk::node::expression::Expression *condition, cdk::node::Node *thenblock,
                        cdk::node::Node *elseblock) :
          cdk::node::Node(lineno), _condition(condition), _thenblock(thenblock), _elseblock(elseblock) {
      }

    public:
      inline cdk::node::expression::Expression *condition() {
        return _condition;
      }
      inline cdk::node::Node *thenblock() {
        return _thenblock;
      }
      inline cdk::node::Node *elseblock() {
        return _elseblock;
      }

      const char *name() const {
        return "IfElseNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processIfElseNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: IfElseNode.h,v $
// Revision 1.3  2013-04-16 18:54:09  ist164787
// Added a new node: FunctionArgument. This represents an argument in a function declaration/definition
// Syntax tree is now being built (not tested)
//
// Revision 1.2  2013-03-26 10:58:49  ist164787
// Changed generic Node child to Block in For, If and DoWhile nodes
//
// Revision 1.1  2013-02-16 16:10:13  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.8  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.7  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
