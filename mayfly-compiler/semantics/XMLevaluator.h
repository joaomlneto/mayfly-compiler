// $Id: XMLevaluator.h,v 1.1 2013-02-16 16:10:14 ist13500 Exp $
#ifndef __MF_SEMANTICS_XMLEVALUATOR_H__
#define __MF_SEMANTICS_XMLEVALUATOR_H__

#include <cdk/semantics/Evaluator.h>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/nodes/Node.h>
#include <cdk/Compiler.h>
#include "semantics/XMLwriter.h"

namespace mayfly {
  namespace semantics {

    class XMLevaluator: public cdk::semantics::Evaluator {
      static XMLevaluator _self;

    protected:
      inline XMLevaluator(const char *target = "xml") :
        cdk::semantics::Evaluator(target) {
      }

    public:
      inline bool evaluate(cdk::Compiler *compiler) {
        XMLwriter sp(compiler->ostream(), compiler->debug());
        compiler->ast()->accept(&sp, 0);
        return true;
      }

    };

  } // namespace semantics
} // namespace mayfly

#endif
// $Log: XMLevaluator.h,v $
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.7  2013/02/12 17:43:57  david
// Further code simplification (evaluators).
//
// Revision 1.6  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.5  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
