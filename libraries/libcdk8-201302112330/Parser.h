// $Id: Parser.h,v 1.2 2013/02/11 20:56:50 david Exp $ -*- c++ -*-
#ifndef __CDK8_SEMANTICS_PARSER_H__
#define __CDK8_SEMANTICS_PARSER_H__

#include <iostream>
#include <map>
#include <string>

namespace cdk {

  class Compiler;

  class Parser {
    //! @var _istream is the input stream (associated with g_ifile) for use by the scanner
    std::istream *_istream;

    //! @var _ostream is the output stream (associated with g_ofile) for use by the scanner
    std::ostream *_ostream;

  protected:
    inline Parser() :
        _istream(nullptr), _ostream(nullptr) {
    }

  public:
    //! How to destroy a parser.
    virtual ~Parser() {
    }

  public:
    inline std::istream &istream() {
      return *_istream;
    }
    inline void istream(std::istream &istr) {
      _istream = &istr;
      switchStreams();
    }
    inline void istream(std::istream *istr) {
      _istream = istr;
      switchStreams();
    }

    inline std::ostream &ostream() {
      return *_ostream;
    }
    inline void ostream(std::ostream &ostr) {
      _ostream = &ostr;
      switchStreams();
    }
    inline void ostream(std::ostream *ostr) {
      _ostream = ostr;
      switchStreams();
    }

    virtual void switchStreams() = 0;

  public:
    /**
     * Parse algorithm: the compiler object stores the result.
     * @param compiler the compiler object this parser belongs to.
     * @return true if the operation is successful
     */
    virtual int parse(cdk::Compiler *compiler) = 0;

  };

}// namespace cdk

#endif

/*
 * $Log: Parser.h,v $
 * Revision 1.2  2013/02/11 20:56:50  david
 * *** empty log message ***
 *
 * Revision 1.1  2013/02/10 19:18:24  david
 * Code cleanup and simplification. C++11 is now mandatory.
 *
 * Revision 1.8  2013/02/09 19:00:35  david
 * First CDK8 commit. Major code simplification.
 * Starting C++11 implementation.
 *
 * Revision 1.7  2012/04/10 19:01:05  david
 * Removed initialization-dependent static members in factories.
 * Handling of ProgramNodes is now better encapsulated by visitors (not done
 * by evaluators, as before). Major cleanup (comments).
 *
 * Revision 1.6  2012/03/06 15:07:46  david
 * Added subtype to ExpressionType. This allows for more expressiveness in
 * type description.
 *
 */

