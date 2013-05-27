// $Id: Compiler.h,v 1.16 2013/02/11 20:56:50 david Exp $ -*- c++ -*-
#ifndef __CDK8_COMPILER_H__
#define __CDK8_COMPILER_H__

#include <cstdlib>
#include <string>
#include <iostream>
#include <cdk/Parser.h>
#include <cdk/semantics/Evaluator.h>

namespace cdk {

  namespace node {
    class Node;
  }

  /**
   * This is the compiler superclass: it provides various variables
   * for keeping track of what the compiler is doing.
   * It is no longer abstract (as in previous versions) and it no
   * longer contains explicit scanner and parser objects, but rather
   * a more abstract syntactic parser object encapsulating both the
   * scanner and the parser. Thus the parsing operation is similar
   * to the semantic evaluation and depends only on an abstract
   * interface and on the configuration provided by the specific
   * factories.
   */
  class Compiler {

    /** @var _name is the compiler's name */
    std::string _name;

    /** @var _extension is extension of the output file */
    std::string _extension;

    /** @var _ifile is the input file name */
    std::string _ifile;

    /** @var _ofile is the output file name */
    std::string _ofile;

  protected:

    /** @var _parser is a reference to the parser (scanner + parser itself) */
    cdk::Parser *_parser;

    /**
     * @var _ast is the root of the syntax tree.
     * This is the root of the syntactic tree. It will be defined when the
     * bottom-up syntactic analysis ends (yyparse). This variable will be used by the
     * different semantic processors (evaluate).
     */
    cdk::node::Node *_ast;

  private:

    /** @var _optimize is a flag: optimization (default behaviour unavailable) */
    bool _optimize;

    /** @var _debug is a flag: debug (default behaviour: false) */
    bool _debug;

    /** Compilation errors */
    int _errors;

  public:
    inline Compiler(const std::string &language, cdk::Parser *parser) :
        _name(language), _extension("asm"), _ifile("<<STDIN>>"), _ofile("<<STDOUT>>"), _parser(
            parser), _ast(nullptr), _optimize(false), _debug(false), _errors(0) {
    }

    virtual ~Compiler() {
      // EMPTY
    }

  public:
    inline const std::string &name() const {
      return _name;
    }
    inline void name(const std::string &name) {
      _name = name;
    }

    inline const std::string &extension() const {
      return _extension;
    }
    inline void extension(const std::string &extension) {
      _extension = extension;
    }

    inline const std::string &ifile() const {
      return _ifile;
    }
    inline void ifile(const std::string &ifile) {
      _ifile = ifile;
    }

    inline const std::string &ofile() const {
      return _ofile;
    }
    inline void ofile(const std::string &ofile) {
      _ofile = ofile;
    }

    inline std::istream &istream() {
      return _parser->istream();
    }
    inline void istream(std::istream &istr) {
      _parser->istream(istr);
    }
    inline void istream(std::istream *istr) {
      _parser->istream(istr);
    }

    inline std::ostream &ostream() {
      return _parser->ostream();
    }
    inline void ostream(std::ostream &ostr) {
      _parser->ostream(ostr);
    }
    inline void ostream(std::ostream *ostr) {
      _parser->ostream(ostr);
    }

  public:
    inline cdk::node::Node *ast() {
      return _ast;
    }
    inline void ast(cdk::node::Node *ast) {
      _ast = ast;
    }

  public:
    inline bool optimize() const {
      return _optimize;
    }
    inline void optimize(bool optimize) {
      _optimize = optimize;
    }

    inline bool debug() const {
      return _debug;
    }
    inline void debug(bool debug) {
      _debug = debug;
    }

    inline int errors() const {
      return _errors;
    }

  public:
    inline int parse() {
      if (_parser)
        return _parser->parse(this);
      else {
        std::cerr << "FATAL: No parser available. Exiting..." << std::endl;
        exit(1);
      }
    }

  public:
    /**
     * Starts processing at _ast and produces the output file.
     * The specific processing strategy is provided independently by each compiler
     * implementation (Evaluator subclasses).
     * @note Implementation-dependent.
     * @see cdk::semantics::Evaluator
     */
    virtual bool evaluate() {
      cdk::semantics::Evaluator *evaluator = cdk::semantics::Evaluator::getEvaluatorFor(_extension);
      if (evaluator)
        return evaluator->evaluate(this);
      else {
        std::cerr << "FATAL: No evaluator defined for target '" << _extension << "'. Exiting..."
            << std::endl;
        exit(1);
      }
    }

  };

}      // namespace cdk

#endif

// $Log: Compiler.h,v $
// Revision 1.16  2013/02/11 20:56:50  david
// *** empty log message ***
//
// Revision 1.15  2013/02/10 19:18:24  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.14  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.13  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.12  2012/03/06 15:07:46  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
// Revision 1.11  2012/02/18 19:38:59  david
// This is the first commit in CDK7. Evaluators and code generators are now aware
// of the debug command line options.
//
