// $Id: Composite.h,v 1.20 2013/02/10 19:18:24 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_COMPOSITE_H__
#define __CDK8_NODE_COMPOSITE_H__

#include <cdk/nodes/Node.h>
#include <vector>
#include <cstdarg>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {

    class Composite: public Node {
      std::vector<Node*> _subnodes;

    public:
      std::vector<Node*> &subnodes() {
        return _subnodes;
      }
      size_t size() {
        return _subnodes.size();
      }
      Node *at(size_t i) {
        return _subnodes.at(i);
      }

    public:
      /**
       * The constructor of a composite node takes the same first
       * argument as any other node.
       * The second argument is the number of child nodes: this
       * argument is followed by the child nodes themselves. Note
       * that no effort is made to ensure that the given number of
       * children matches the actual children passed to the
       * function. <b>You have been warned...</b>
       *
       * @param lineno the source code line number that originated the node
       * @param nops the number of child nodes
       * @param ... the child nodes
       */
      Composite(int lineno, int nops, ...) :
          Node(lineno) {
        va_list ap;
        va_start(ap, nops);
        for (int i = 0; i < nops; i++)
        _subnodes.push_back(va_arg(ap, Node*));
        va_end(ap);
      }

    public:
      /**
       * This is the destructor for composite nodes. Note that this
       * destructor also causes the destruction of the node's
       * children.
       */
      inline ~Composite() {
        for (size_t i = 0; i < _subnodes.size(); i++) {
          Node *n = _subnodes.at(i);
          delete n;
        }
        _subnodes.clear();
      }

      /**
       * @return the name of the node's class
       */
      const char *name() const {
        return "Composite";
      }

      /**
       * @param sp semantic processor visitor
       * @param level syntactic tree level
       */
      virtual void accept(SemanticProcessor *sp, int level) {
        sp->processComposite(this, level);
      }

    };

  } // node
} // cdk

#endif

// $Log: Composite.h,v $
// Revision 1.20  2013/02/10 19:18:24  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.19  2013/02/09 19:00:35  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.18  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.17  2012/03/06 15:07:45  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
