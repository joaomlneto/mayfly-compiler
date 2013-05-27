// $Id: GLOBAL.h,v 1.2 2013/02/12 18:56:15 david Exp $
#ifndef __PF2ASM_NODE_addressing_GLOBAL_H__
#define __PF2ASM_NODE_addressing_GLOBAL_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {
    namespace addressing {

      class GLOBAL: public cdk::node::Node {
        std::string _label;
        std::string _type;

      public:
        inline GLOBAL(int lineno, std::string &label, std::string &type) :
          cdk::node::Node(lineno), _label(label), _type(type) {
        }
        inline const std::string &label() const {
          return _label;
        }
        inline const std::string &type() const {
          return _type;
        }
        inline const char *name() const { return "GLOBAL"; }
        inline void accept(SemanticProcessor *sp, int level) {
          sp->processGLOBAL(this, level);
        }
      };

    } // namespace nodes/addressing
  } // namespace node
} // namespace pf2asm

#endif

/*
 * $Log: GLOBAL.h,v $
 * Revision 1.2  2013/02/12 18:56:15  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.1  2012/02/19 20:30:18  david
 * Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
 * Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
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

