// $Id: CompilerFactory.h,v 1.1 2013-02-16 16:10:15 ist13500 Exp $ -*- c++ -*-
#ifndef __MF_MFCOMPILERFACTORY_H__
#define __MF_MFCOMPILERFACTORY_H__

#include <cdk/CompilerFactory.h>
#include <cdk/Compiler.h>
#include "YYParser.h"

namespace mayfly {

  /**
   * This class implements the compiler factory for the Mayfly compiler.
   */
  class CompilerFactory: public cdk::CompilerFactory {
    /**
     * This object is automatically registered by the constructor in the
     * superclass' language registry.
     */
    static CompilerFactory _self;

  protected:
    /**
     * @param language name of the language handled by this factory (see .cpp file)
     */
    CompilerFactory(const std::string &language) :
        cdk::CompilerFactory(language) {
    }

  protected:
    /**
     * Create a parser object for the Mayfly language.
     * This method is now private and is called only from the compiler creation
     * method.
     * @param name name of the input file (for debug only)
     * @return parser object pointer
     * @see createCompiler
     */
    cdk::Parser *createParser(const std::string &language) {
      return new mayfly::YYParser();
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

} // namespace mayfly

#endif

// $Log: CompilerFactory.h,v $
// Revision 1.1  2013-02-16 16:10:15  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.7  2013/02/12 17:43:58  david
// Further code simplification (evaluators).
//
// Revision 1.6  2013/02/11 20:56:27  david
// Minor cleanup.
//
// Revision 1.5  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.4  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.3  2012/04/10 19:09:46  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
