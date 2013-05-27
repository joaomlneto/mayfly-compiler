// $Id: Nil.h,v 1.19 2013/02/09 19:00:34 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_NIL_H__
#define __CDK8_NODE_NIL_H__

#include <cdk/nodes/Node.h>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {
    /**
     * Class for describing empty nodes (leaves).
     * The only data recorded by this type of node is the node's
     * attribute (i.e., the mnemonic) and the source code line
     * number.
     */
    class Nil: public Node {
    public:
      /**
       * Simple constructor.
       *
       * @param lineno the source code line number corresponding to
       * the node
       */
      inline Nil(int lineno) :
          Node(lineno) {
      }

      /**
       * @return the name of the node's class
       */
      const char *name() const {
        return "Nil";
      }

      /**
       * @param sp semantic processor visitor
       * @param level syntactic tree level
       */
      virtual void accept(SemanticProcessor *sp, int level) {
        sp->processNil(this, level);
      }

    };

  } // node
} // cdk

#endif

// $Log: Nil.h,v $
// Revision 1.19  2013/02/09 19:00:34  david
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
