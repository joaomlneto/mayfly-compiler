// $Id: JLT.h,v 1.3 2013/02/12 18:56:16 david Exp $
#ifndef __PF2ASM_NODE_jumps_JLT_H__
#define __PF2ASM_NODE_jumps_JLT_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {
    namespace jumps {

      class JLT: public cdk::node::Node {
        std::string _label;

      public:
        inline JLT(int lineno, std::string &label) :
          cdk::node::Node(lineno), _label(label) {
        }
        inline const std::string &label() const {
          return _label;
        }
        inline const char *name() const { return "JLT"; }
        inline void accept(SemanticProcessor *sp, int level) {
          sp->processJLT(this, level);
        }
      };

    } // namespace nodes/jumps
  } // namespace node
} // namespace pf2asm

#endif

/*
 * $Log: JLT.h,v $
 * Revision 1.3  2013/02/12 18:56:16  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.2  2009/05/09 17:36:55  david
 * Major node cleanup. Parser simplification.
 *
 * Revision 1.1  2009/02/25 07:32:00  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 *
 */
