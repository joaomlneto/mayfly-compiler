// $Id: CompilerFactory.h,v 1.2 2013/02/12 18:56:16 david Exp $ -*- c++ -*-
#ifndef __PF_COMPILERFACTORY_H__
#define __PF_COMPILERFACTORY_H__

#include <cdk/CompilerFactory.h>
#include <cdk/Compiler.h>
#include "YYParser.h"

namespace cdk {
  class Compiler;
}

namespace pf2asm {

  /**
   * This class implements the compiler factory for the PF compiler.
   */
  class CompilerFactory: public cdk::CompilerFactory {
    /**
     * This object is automatically registered by the constructor in the
     * superclass' language registry.
     */
    static CompilerFactory _self;

  protected:
    CompilerFactory(const std::string &language) :
        cdk::CompilerFactory(language) {
    }

  protected:
    /**
     * Create a parser object for the Compact language.
     * This method is now private and is called only from the compiler creation
     * method.
     * @param name name of the input file (for debug only)
     * @return parser object pointer
     * @see createCompiler
     */
    cdk::Parser *createParser(const std::string &language) {
      return new pf2asm::YYParser();
    }

  public:
    /**
     * Create a compiler object for a given language.
     * @param name name of the language handled by the compiler
     * @return compiler object pointer
     */
    cdk::Compiler *createCompiler(const std::string &language) {
      cdk::Parser *parser = createParser(language);
      return new cdk::Compiler(language, parser);
    }

  };

} // namespace pf2asm

#endif

// $Log: CompilerFactory.h,v $
// Revision 1.2  2013/02/12 18:56:16  david
// Major code cleanup and simplification. Uses CDK8. C++11 is required.
//
// Revision 1.1  2009/03/04 20:22:24  david
// *** empty log message ***
//
// Revision 1.2  2009/02/28 21:01:06  david
// Minor cleanup.
//
// Revision 1.1  2009/02/25 07:31:56  david
// First working version of pf2asm. This version still uses
// byacc.
//
// Revision 1.1  2009/02/23 20:53:38  david
// First PF implementation. Does not work with PF syntax nor
// does it do anything useful.
//
