// $Id: DDUP.h,v 1.2 2013/02/12 18:56:14 david Exp $
#ifndef __PF2ASM_NODE_nodes_DDUP_H__
#define __PF2ASM_NODE_nodes_DDUP_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {

    class DDUP: public cdk::node::Node {
    public:
      inline DDUP(int lineno) :
        cdk::node::Node(lineno) {
      }
      inline const char *name() const { return "DDUP"; }
      inline void accept(SemanticProcessor *sp, int level) {
        sp->processDDUP(this, level);
      }
    };

  } // namespace node
} // namespace pf2asm

#endif

/*
 * $Log: DDUP.h,v $
 * Revision 1.2  2013/02/12 18:56:14  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.1  2012/02/19 20:30:14  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 *
 */
