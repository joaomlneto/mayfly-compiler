// $Id: Block.h,v 1.2 2013-05-15 12:51:54 ist164787 Exp $ -*- c++ -*-
#ifndef __MF_BLOCK_H__
#define __MF_BLOCK_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/Sequence.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing if-then nodes.
     */
    class Block: public cdk::node::Node {
      cdk::node::Sequence *_declarations, *_instructions;

    public:
      inline Block(int lineno, cdk::node::Sequence *declarations, cdk::node::Sequence *instructions) :
          cdk::node::Node(lineno), _declarations(declarations), _instructions(instructions) {
      }

    public:
      inline cdk::node::Sequence *declarations() {
        return _declarations;
      }
		inline cdk::node::Sequence *instructions() {
        return _instructions;
      }
      const char *name() const {
        return "Block";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processBlock(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: Block.h,v $
// Revision 1.2  2013-05-15 12:51:54  ist164787
// Nested block declarations in functions working, fixed block attribute name from definitions to instructions... seems legit now
//
// Revision 1.1  2013-03-25 18:48:07  ist164787
// Added Block node
//
// Revision 1.1  2013-02-16 16:10:13  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.8  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.7  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
