// $Id: Node.h,v 1.18 2013/02/09 19:00:34 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_NODE_H__
#define __CDK8_NODE_NODE_H__

#include <iostream>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {

    /**
     * Class for describing syntactic tree nodes.
     * This is an abstract class and forms the root of the node hierarchy.
     * The node hierarchy is organized in a structure according to the
     * <i>Composite</i> design pattern: class <tt>Node</tt> is the root
     * of the hierarchy; class <tt>Simple</tt> is a template for leaves
     * holding simple (atomic) types; <tt>Composite</tt> represents the
     * recursive structure. Note that other recursion classes are possible
     * by extending any of the classes in namespace <tt>cdk::node</tt>.
     */
    class Node {
      int _lineno; // source line

    protected:
      /**
       * Simple constructor.
       *
       * @param lineno the source code line number corresponding to the node
       */
      inline Node(int lineno) :
          _lineno(lineno) {
      }

    public:
      virtual ~Node() {}

    public:
      /** @return the line number of the corresponding source code */
      inline int lineno() const {
        return _lineno;
      }

      /**
       * @return the name of the node's class
       */
      virtual const char *name() const = 0;

      /**
       * Every node must provide this method.
       *
       * @param sp semantic processor visitor
       * @param level syntactic tree level
       */
      virtual void accept(SemanticProcessor *sp, int level) = 0;

    };

  } // node
} // cdk

#endif

// $Log: Node.h,v $
// Revision 1.18  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.17  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.16  2012/03/06 15:07:45  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
