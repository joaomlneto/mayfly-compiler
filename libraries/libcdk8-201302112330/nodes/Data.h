// $Id: Data.h,v 1.18 2013/02/09 19:00:34 david Exp $ -*- c++ -*-
#ifndef __CDK8_NODE_DATA_H__
#define __CDK8_NODE_DATA_H__

#include <cdk/nodes/Node.h>
#include "SemanticProcessor.h"

namespace cdk {
  namespace node {

    /**
     * Class for describing syntactic tree leaves for holding data
     * buffers. This class does not inherit from the <tt>Simple</tt>
     * template.
     */
    class Data: public Node {
      void *_data; // pointer to data
      size_t _size; // size of data

    public:
      /**
       * Constructor for nodes that hold opaque data buffers.
       * Each buffer is characterized by its data and the
       * corresponding data size.
       *
       * @param lineno the source code line number corresponding to this node
       * @param data the opaque data buffer
       * @param nbytes the size (bytes) of the data buffer
       */
      inline Data(int lineno, void *data, size_t nbytes) :
          Node(lineno), _data(data), _size(nbytes) {
      }

      /**
       * The destructor. We have defined it explicitly (even though
       * it was not needed) to emphasize that the data buffer is
       * <b>not</b> destroyed when the node itself dies.
       */
      ~Data() {
      }

      inline void *data() {
        return _data;
      }
      inline size_t size() {
        return _size;
      }

      /**
       * @return the name of the node's class
       */
      const char *name() const {
        return "Data";
      }

      /**
       * @param sp semantic processor visitor
       * @param level syntactic tree level
       */
      virtual void accept(SemanticProcessor *sp, int level) {
        sp->processData(this, level);
      }

    };

  } // node
} // cdk

#endif

// $Log: Data.h,v $
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
