// $Id: PFevaluator.h,v 1.5 2013/02/12 18:56:17 david Exp $
#ifndef __PF2ASM_SEMANTICS_PFEVALUATOR_H__
#define __PF2ASM_SEMANTICS_PFEVALUATOR_H__

#include <iostream>
#include <cdk/semantics/Evaluator.h>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/nodes/Node.h>
#include <cdk/Compiler.h>
#include <cdk/generators/ix86.h>
#include "semantics/PFwriter.h"

namespace pf2asm {
  namespace semantics {

    class PFevaluator: public cdk::semantics::Evaluator {
      static PFevaluator _self;

    protected:
      PFevaluator(const char *target = "asm") :
          cdk::semantics::Evaluator(target) {
      }

    public:
      bool evaluate(cdk::Compiler *compiler) {
        std::ostream &os = compiler->ostream();

        // this symbol table will be used to check identifiers
        cdk::semantics::SymbolTable<std::string> symtab;
        cdk::generator::ix86 pf(os, compiler->debug());

        // even though a symbol table is passed it is, currently, not used
        pf2asm::semantics::PFwriter pfwriter(os, compiler->debug(), symtab, pf);

        // now the nasm/yasm code will be generated
        compiler->ast()->accept(&pfwriter, 0);

        return true;
      }

    };

  }// namespace semantics
} // namespace pf2asm

#endif

/*
 * $Log: PFevaluator.h,v $
 * Revision 1.5  2013/02/12 18:56:17  david
 * Major code cleanup and simplification. Uses CDK8. C++11 is required.
 *
 * Revision 1.4  2009/02/28 21:01:07  david
 * Minor cleanup.
 *
 * Revision 1.3  2009/02/25 07:31:57  david
 * First working version of pf2asm. This version still uses
 * byacc.
 *
 * Revision 1.2  2009/02/23 20:53:38  david
 * First PF implementation. Does not work with PF syntax nor
 * does it do anything useful.
 *
 */
