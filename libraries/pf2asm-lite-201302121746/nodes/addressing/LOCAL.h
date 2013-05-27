// $Id: LOCAL.h,v 1.3 2013/02/12 18:56:15 david Exp $
#ifndef __PF2ASM_NODE_addressing_LOCAL_H__
#define __PF2ASM_NODE_addressing_LOCAL_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {
    namespace addressing {

      class LOCAL: public cdk::node::Node {
        int _offset;

      public:
        inline LOCAL(int lineno, int offset) :
          cdk::node::Node(lineno), _offset(offset) {
        }
        inline int offset() const {
          return _offset;
        }
        inline const char *name() const { return "LOCAL"; }
        inline void accept(SemanticProcessor *sp, int level) {
          sp->processLOCAL(this, level);
        }
      };

    } // namespace nodes/addressing
  } // namespace node
} // namespace pf2asm

#endif

/*
 * $Log: LOCAL.h,v $
 * Revision 1.3  2013/02/12 18:56:15  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.2  2009/05/09 17:36:53  david
 * Major node cleanup. Parser simplification.
 *
 * Revision 1.1  2009/02/25 07:31:58  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 *
 */

