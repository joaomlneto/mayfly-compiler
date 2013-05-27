// $Id: LEAVE.h,v 1.3 2013/02/12 18:56:13 david Exp $
#ifndef __PF2ASM_NODE_function_LEAVE_H__
#define __PF2ASM_NODE_function_LEAVE_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {
    namespace function {

      class LEAVE: public cdk::node::Node {
      public:
        inline LEAVE(int lineno) :
          cdk::node::Node(lineno) {
        }
        inline const char *name() const { return "LEAVE"; }
        inline void accept(SemanticProcessor *sp, int level) {
          sp->processLEAVE(this, level);
        }
      };

    } // namespace nodes/function
  } // namespace node
} // namespace pf2asm

#endif

/*
 * $Log: LEAVE.h,v $
 * Revision 1.3  2013/02/12 18:56:13  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.2  2009/05/09 17:36:53  david
 * Major node cleanup. Parser simplification.
 *
 * Revision 1.1  2009/02/25 07:31:53  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 *
 */
