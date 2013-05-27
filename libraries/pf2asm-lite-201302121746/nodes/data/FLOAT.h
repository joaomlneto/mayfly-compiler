// $Id: FLOAT.h,v 1.3 2013/02/12 18:56:15 david Exp $
#ifndef __PF2ASM_NODE_data_FLOAT_H__
#define __PF2ASM_NODE_data_FLOAT_H__

#include <cdk/nodes/Node.h>
#include "semantics/SemanticProcessor.h"

namespace pf2asm {
  namespace node {
    namespace data {

      class FLOAT: public cdk::node::Node {
        double _value;

      public:
        inline FLOAT(int lineno, float value) :
          cdk::node::Node(lineno), _value(value) {
        }
        inline double value() const {
          return _value;
        }
        inline const char *name() const { return "FLOAT"; }
        inline void accept(SemanticProcessor *sp, int level) {
          sp->processFLOAT(this, level);
        }
      };

    } // namespace nodes/data
  } // namespace node
} // namespace pf2asm

#endif


/*
 * $Log: FLOAT.h,v $
 * Revision 1.3  2013/02/12 18:56:15  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.2  2009/05/09 17:36:54  david
 * Major node cleanup. Parser simplification.
 *
 * Revision 1.1  2009/02/25 07:31:53  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 *
 */
