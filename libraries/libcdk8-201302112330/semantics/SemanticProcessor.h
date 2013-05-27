// $Id: SemanticProcessor.h,v 1.15 2013/02/10 19:18:23 david Exp $ -*- c++ -*-
#ifndef __CDK8_SEMANTICS_PROCESSOR_H__
#define __CDK8_SEMANTICS_PROCESSOR_H__

#include <iostream>

namespace cdk {
  namespace node {
    class Composite;
    class Sequence;
    class Data;
    class Nil;

    namespace expression {
      class ADD;
      class SUB;
      class MUL;
      class DIV;
      class MOD;
      class NE;
      class LT;
      class LE;
      class EQ;
      class GE;
      class GT;
      class NEG;
      class Identifier;
      class Double;
      class Integer;
      class String;
    }

  }
}

namespace cdkne = cdk::node::expression;

//!
//! This class is only for compiling the package: it will not be
//! installed. Specific compilers are supposed to define their own,
//! with the SAME NAME, but defining ALL processing functions
//! corresponding to their specific problem.
//!
class SemanticProcessor {
  //! The output stream
  std::ostream &_os;

protected:
  //! Debug flag
  bool _debug;

protected:
  /**
   * Initialization of a semantic processor.
   *
   * @param os is the output stream to be used by the
   *        semantic processor.
   */
  SemanticProcessor(std::ostream &os = std::cout, bool debug = false);

  /**
   * Return the current output stream.
   * @return an output stream.
   */
  inline std::ostream &os() {
    return _os;
  }

public:
  /**
   * How to destroy a semantic processor.
   */
  virtual ~SemanticProcessor();

public:
  /*
   * Each function processes (visits) the node passed as its first
   * argument. In an actual visitor class (remember that this one
   * is just for defining the framework and should be replaced),
   * the class should have a <tt>process</tt> method for each concrete
   * node type. This is very important: there is no automatic polymorphism
   * in function arguments. <b>You have been warned...</b>
   *
   * @param node is the node to be visited.
   * @param lvl is a variable for encoding the processing
   *        level. It can, of course, be safely ignored if not
   *        needed.
   */

  virtual void processComposite(cdk::node::Composite *node, int lvl = 0) = 0;
  virtual void processSequence(cdk::node::Sequence *node, int lvl = 0) = 0;
  virtual void processData(cdk::node::Data *node, int lvl = 0) = 0;
  virtual void processNil(cdk::node::Nil *node, int lvl = 0) = 0;

  virtual void processADD(cdkne::ADD *node, int lvl = 0) = 0;
  virtual void processSUB(cdkne::SUB *node, int lvl = 0) = 0;
  virtual void processMUL(cdkne::MUL *node, int lvl = 0) = 0;
  virtual void processDIV(cdkne::DIV *node, int lvl = 0) = 0;
  virtual void processMOD(cdkne::MOD *node, int lvl = 0) = 0;

  virtual void processNEG(cdkne::NEG *node, int lvl = 0) = 0;

  virtual void processNE(cdkne::NE *node, int lvl = 0) = 0;
  virtual void processLT(cdkne::LT *node, int lvl = 0) = 0;
  virtual void processLE(cdkne::LE *node, int lvl = 0) = 0;
  virtual void processEQ(cdkne::EQ *node, int lvl = 0) = 0;
  virtual void processGE(cdkne::GE *node, int lvl = 0) = 0;
  virtual void processGT(cdkne::GT *node, int lvl = 0) = 0;

  virtual void processIdentifier(cdkne::Identifier *node, int lvl = 0) = 0;

  virtual void processDouble(cdkne::Double *node, int lvl = 0) = 0;
  virtual void processInteger(cdkne::Integer *node, int lvl = 0) = 0;
  virtual void processString(cdkne::String *node, int lvl = 0) = 0;

}; // class processor

#endif

// $Log: SemanticProcessor.h,v $
// Revision 1.15  2013/02/10 19:18:23  david
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
