// $Id: Sequence.h,v 1.16 2013/02/11 20:56:50 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_SEQUENCE_H__
#define __CDK8_NODE_SEQUENCE_H__

#include <cdk/nodes/Node.h>
#include <vector>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {

    /**
     * Class representing a node sequence, for instance, in an
     * instruction block or in an argument list.
     */
    class Sequence: public Node {

      typedef std::vector<Node*> sequence_type;
      sequence_type _nodes;

    public:
      typedef sequence_type::iterator iterator;

    public:
      /**
       * Example: constructor for a left recursive production node:
       * <pre>
       * sequence: item {$$ = new Sequence(LINE, $1);}* | sequence item {$$ = new Sequence(LINE, $2, $1);}* </pre>
       * The constructor of a sequence node takes the same first two
       * arguments as any other node.
       * The third argument is the number of child nodes: this
       * argument is followed by the child nodes themselves. Note
       * that no effort is made to ensure that the given number of
       * children matches the actual children passed to the
       * function. <b>You have been warned...</b>
       *
       * @param lineno the source code line number that originated the node
       * @param item is the single element to be added to the sequence
       * @param sequence is a previous sequence (nodes will be imported)
       */
      Sequence(int lineno, Node *item, Sequence *sequence = nullptr) :
          Node(lineno) {
        if (sequence != nullptr)
          _nodes = sequence->nodes();
        _nodes.push_back(item);
      }

    public:
      /**
       * This is the destructor for sequence nodes. Note that this
       * destructor also causes the destruction of the node's
       * children.
       */
      inline ~Sequence() {
        for (size_t i = 0; i < _nodes.size(); i++) {
          delete _nodes[i];
        }
        _nodes.clear();
      }

    public:
      cdk::node::Node *node(size_t i) {
        return _nodes[i];
      }
      sequence_type &nodes() {
        return _nodes;
      }
      size_t size() {
        return _nodes.size();
      }

      /**
       * @return the name of the node's class
       */
      const char *name() const {
        return "Sequence";
      }

      /**
       * @param sp semantic processor visitor
       * @param level syntactic tree level
       */
      void accept(SemanticProcessor *sp, int level) {
        sp->processSequence(this, level);
      }

    };

  } // node
} // cdk

#endif

// $Log: Sequence.h,v $
// Revision 1.16  2013/02/11 20:56:50  david
// *** empty log message ***
//
// Revision 1.15  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.14  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.13  2012/03/06 15:07:45  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
