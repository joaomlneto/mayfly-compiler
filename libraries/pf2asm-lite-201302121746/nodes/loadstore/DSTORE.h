// $Id: DSTORE.h,v 1.2 2013/02/12 18:56:13 david Exp $
#ifndef __PF2ASM_NODE_loadstore_DSTORE_H__
#define __PF2ASM_NODE_loadstore_DSTORE_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {
    namespace loadstore {

      class DSTORE: public cdk::node::Node {
      public:
        inline DSTORE(int lineno) :
          cdk::node::Node(lineno) {
        }
        inline const char *name() const { return "DSTORE"; }
        inline void accept(SemanticProcessor *sp, int level) {
          sp->processDSTORE(this, level);
        }
      };

    } // namespace nodes/loadstore
  } // namespace node
} // namespace pf2asm

#endif

/*
 * $Log: DSTORE.h,v $
 * Revision 1.2  2013/02/12 18:56:13  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.1  2012/02/19 20:30:15  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
 *
 * Revision 1.2  2009/05/09 17:36:55  david
 * Major node cleanup. Parser simplification.
 *
 * Revision 1.1  2009/02/25 07:31:57  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 *
 */
