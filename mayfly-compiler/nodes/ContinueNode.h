// $Id: ContinueNode.h,v 1.4 2013-05-17 22:26:16 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_CONTINUENODE_H__
#define __MF_CONTINUENODE_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing read nodes.
     */
    class ContinueNode: public cdk::node::Node {
	 protected:
       unsigned int _level;

    public:
      inline ContinueNode(int lineno, cdk::node::expression::Integer *level) :
			ContinueNode(lineno, level->value()) {
      }

		inline ContinueNode(int lineno) :
			ContinueNode(lineno, 1) {
      }

		inline ContinueNode(int lineno, unsigned int level) :
			cdk::node::Node(lineno), _level(level) {
		}


    public:
      inline unsigned int level() {
        return _level;
      }

      const char *name() const {
        return "ContinueNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processContinueNode(this, level);
      }

    };

  }// namespace node
} // namespace mayfly

#endif

