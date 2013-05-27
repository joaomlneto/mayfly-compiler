// $Id: CompilerFactory.h,v 1.12 2013/02/10 19:18:24 david Exp $ -*- c++ -*-
#ifndef __CDK8_COMPILERFACTORY_H__
#define __CDK8_COMPILERFACTORY_H__

#include <map>
#include <string>

namespace cdk {

  class Compiler;
  class Parser;
  namespace semantics {
    class Evaluator;
  }

  /**
   * This is the main factory abstract class: it provides methods
   * for creating the lexical analyser and the compiler itself.
   * Instances of concrete subclasses will be created by the
   * "main" function to provide instances of the scanner and compiler
   * objects for a concrete language.
   *   - keys are language names
   *   - values are compiler factories
   */
  class CompilerFactory {
    static CompilerFactory *&factoriesByLanguage(const std::string &language) {
      static std::map<std::string, CompilerFactory*> factories;
      return factories[language];
    }

  protected:
    CompilerFactory(const std::string &language) {
      factoriesByLanguage(language) = this;
    }

  public:
    static CompilerFactory *getImplementation(const std::string &language) {
      return factoriesByLanguage(language);
    }

  public:
    /**
     * The superclass destructor does not do anything.
     * Probably, it would be a good idea to clean up the factories map.
     */
    virtual ~CompilerFactory() {}

  protected:
    /**
     * Create a parser object for a given language.
     * This method is now private and is called only from the compiler
     * creation method.
     * @param name input file (for debug only)
     * @return parser object pointer
     * @see createCompiler
     */
    virtual cdk::Parser *createParser(const std::string &language) = 0;

  public:
    /**
     * Create a compiler object for a given language.
     * @param name language handled by the compiler
     * @return compiler object pointer
     */
    virtual Compiler *createCompiler(const std::string &language) = 0;

  }; // class CompilerFactory

} // namespace cdk

#endif

// $Log: CompilerFactory.h,v $
// Revision 1.12  2013/02/10 19:18:24  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.11  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.10  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.9  2012/03/06 15:07:46  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
