// $Id: PFevaluator.h,v 1.2 2013-04-29 16:27:07 ist164787 Exp $
#ifndef __MF_SEMANTICS_PFEVALUATOR_H__
#define __MF_SEMANTICS_PFEVALUATOR_H__

#include <cdk/semantics/Evaluator.h>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/nodes/Node.h>
#include <cdk/Compiler.h>
#include <cdk/generators/ix86.h>
#include "semantics/PFwriter.h"
#include "semantics/Symbol.h"

namespace mayfly {
  namespace semantics {

    class PFevaluator: public cdk::semantics::Evaluator {
      static PFevaluator _self;

    protected:
      inline PFevaluator(const char *target = "asm") :
          cdk::semantics::Evaluator(target) {
      }

    public:
      inline bool evaluate(cdk::Compiler *compiler) {
        std::ostream &os = compiler->ostream();

        // this symbol table will be used to check identifiers
        cdk::semantics::SymbolTable<Symbol> symtab;

        // this is the backend postfix machine
        cdk::generator::ix86 pf(os, compiler->debug());

        // generate assembly code from the syntax tree
        // identifiers will be checked during code generation
        PFwriter pfwriter(os, compiler->debug(), symtab, pf);
        compiler->ast()->accept(&pfwriter, 0);

        return true;
      }

    };

  } // namespace semantics
} // namespace mayfly

#endif

// $Log: PFevaluator.h,v $
// Revision 1.2  2013-04-29 16:27:07  ist164787
// Compiler already produces a ASM file (doesnt do anything, though)
//
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
