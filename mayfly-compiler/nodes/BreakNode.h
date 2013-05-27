// $Id: BreakNode.h,v 1.4 2013-05-17 22:26:16 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_BREAKNODE_H__
#define __MF_BREAKNODE_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing read nodes.
     */
    class BreakNode: public cdk::node::Node {
      unsigned int _level;

    public:
      inline BreakNode(int lineno, cdk::node::expression::Integer *level) :
			BreakNode(lineno, level->value()) {
      }

		inline BreakNode(int lineno) :
			BreakNode(lineno, 1) {
      }

		inline BreakNode(int lineno, unsigned int level) :
			cdk::node::Node(lineno), _level(level) {
		}

    public:
      inline unsigned int level() {
        return _level;
      }

      const char *name() const {
        return "BreakNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processBreakNode(this, level);
      }

    };

  }// namespace node
} // namespace mayfly

#endif

