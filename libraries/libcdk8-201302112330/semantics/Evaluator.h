// $Id: Evaluator.h,v 1.10 2013/02/09 19:00:34 david Exp $ -*- c++ -*-
#ifndef __CDK8_SEMANTICS_EVALUATOR_H__
#define __CDK8_SEMANTICS_EVALUATOR_H__

#include <iostream>
#include <map>
#include <string>

namespace cdk {
  class Compiler;
  namespace node {
    class Node;
  }

  namespace semantics {

    class Evaluator {
      /**
       * This is the registry for all evaluators, indexed by target.
       * Subclasses register their instances here through calls to the
       * superclass constructor.
       */
      static Evaluator *&evaluatorsByTarget(const std::string &target) {
        static std::map<std::string, Evaluator*> evaluatorsByTarget;
        return evaluatorsByTarget[target];
      }

    protected:
      Evaluator(const char *target) {
        evaluatorsByTarget(target) = this;
      }

    public:
      /**
       * How to get an evaluator for a given target.
       * @param target the target name: "asm", "c", "xml", etc.
       * @return a pointer to the evaluator object
       */
      static Evaluator *getEvaluatorFor(const std::string &target) {
        return evaluatorsByTarget(target);
      }

    public:
      //! How to destroy an evaluator.
      virtual ~Evaluator() {}

    public:
      /**
       * Evaluation algorithm for a syntax tree: processes the
       * tree and sends the result to the output stream.
       * @param compiler object representing the compiler as a whole
       * @return true if the operation is successful
       */
      virtual bool evaluate(cdk::Compiler *compiler) = 0;

    }; // class Evaluator

  } // namespace semantics
} // namespace cdk

#endif

// $Log: Evaluator.h,v $
// Revision 1.10  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.9  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.8  2012/03/06 15:07:46  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
// Revision 1.7  2012/02/18 19:38:59  david
// This is the first commit in CDK7. Evaluators and code generators are now aware
// of the debug command line options.
//
