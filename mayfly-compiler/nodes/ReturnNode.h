// $Id: ReturnNode.h,v 1.1 2013-03-25 18:21:47 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_RETURNNODE_H__
#define __MF_RETURNNODE_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing read nodes.
     */
    class ReturnNode: public cdk::node::Node {

    public:
      inline ReturnNode(int lineno) :
          cdk::node::Node(lineno) {
      }

    public:
      const char *name() const {
        return "ReturnNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processReturnNode(this, level);
      }

    };

  }// namespace node
} // namespace mayfly

#endif

