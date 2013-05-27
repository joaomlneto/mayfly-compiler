// $Id: ADDRA.h,v 1.3 2013/02/12 18:56:15 david Exp $
#ifndef __PF2ASM_NODE_addressing_ADDRA_H__
#define __PF2ASM_NODE_addressing_ADDRA_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {
    namespace addressing {

      class ADDRA: public cdk::node::Node {
        std::string _label;

      public:
        inline ADDRA(int lineno, std::string &label) :
            cdk::node::Node(lineno), _label(label) {
        }
        inline const std::string &label() const {
          return _label;
        }
        inline const char *name() const { return "ADDRA"; }
        inline void accept(SemanticProcessor *sp, int level) {
          sp->processADDRA(this, level);
        }
      };

    } // namespace nodes/addressing
  } // namespace node
} // namespace pf2asm

#endif

/*
 * $Log: ADDRA.h,v $
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
