// $Id: SymbolTable.h,v 1.9 2013/02/11 20:56:50 david Exp $ -*- c++ -*-
#ifndef __CDK8_SYMBOLTABLE_H__
#define __CDK8_SYMBOLTABLE_H__

#include <string>
#include <iostream>
#include <map>
#include <vector>

namespace cdk {
  namespace semantics {

    template<typename Symbol>
    class SymbolTable {

    private:
      typedef typename std::map<std::string, Symbol*> context_type;
      typedef typename context_type::const_iterator context_iterator;

      /** the context level */
      int _level;

      /** this is the current context */
      context_type *_current;

      /** stores a context path from the root to the current (last) context */
      std::vector<context_type*> _contexts;

    public:
      inline SymbolTable() :
          _level(0) {
        _current = new context_type;
        _contexts.push_back(_current);
      }

      /**
       * Destroy the symbol table and all symbols it contains.
       * Note that SYMBOLS ARE ALSO DELETED!!
       * Again: the death of a table also means the death of its symbols.
       * Hint: do not symbols anywhere other than on their native table.
       * Hint: do not share symbols with other tables or other data structures.
       * Remember: symbols are tightly connected to tables: they die with them.
       * ****   Y O U   H A V E   B E E N   W A R N E D   ****
       */
      inline virtual ~SymbolTable() {
        while (_level > 0)
          pop();
        destroyCurrent();
        _contexts.clear();
      }

    private:
      /**
       * First, destroy all symbols in the current context.
       * Next, remove all entries from the current context.
       * Finally, delete the current context and set the pointer to null.
       */
      void destroyCurrent() {
        for (typename context_type::iterator it = _current->begin(); it != _current->end(); it++) {
          delete it->second;
        }
        _current->clear();
        delete _current;
        _current = nullptr;
      }

    public:

      /**
       * Create a new context and make it current.
       */
      inline void push() {
        _level++;
        _current = new context_type;
        _contexts.push_back(_current);
      }

      /**
       * Destroy the current context: the previous context becomes
       * the current one. If the first context is reached no operation
       * is performed.
       */
      inline void pop() {
        if (_level == 0)
          return;
        destroyCurrent();
        _contexts.pop_back();
        _current = _contexts.back();
        _level--;
      }

      /**
       * Define a new identifier in the local (current) context.
       *
       * @param name the symbol's name.
       * @param symbol the symbol.
       * @return
       *   <tt>true</tt> if new identifier (may be defined in an upper
       *   context); <tt>false</tt> if identifier already exists in the
       *   current context.
       */
      inline bool insert(const std::string &name, Symbol *symbol) {
        context_iterator it = _current->find(name);
        if (it == _current->end()) {
          (*_current)[name] = symbol;
          return true;
        }
        return false;
      }

      /**
       * Replace the data corresponding to a symbol in the current context.
       *
       * @param name the symbol's name.
       * @param symbol the symbol.
       * @return
       *   <tt>true</tt> if the symbol exists; <tt>false</tt> if the
       *   symbol does not exist in any of the contexts.
       */
      inline bool replaceLocal(const std::string &name, Symbol *symbol) {
        typename context_type::iterator it = _current->find(name);
        if (it != _current->end()) {
          delete it->second;
          (*_current)[name] = symbol;
          return true;
        }
        return false;
      }

      /**
       * Replace the data corresponding to a symbol (look for the symbol in all
       * available contexts, starting with the innermost one).
       *
       * @param name the symbol's name.
       * @param symbol the symbol.
       * @return
       *   <tt>true</tt> if the symbol exists; <tt>false</tt> if the
       *   symbol does not exist in any of the contexts.
       */
      inline bool replace(const std::string &name, Symbol *symbol) {
        for (size_t ix = _contexts.size(); ix > 0; ix--) {
          context_type &ctx = *_contexts[ix - 1];
          context_iterator it = ctx.find(name);
          if (it != ctx.end()) {
            //FIXME: BUG: should free previous symbol
            ctx[name] = symbol;
            return true;
          }
        }
        return false;
      }

      /**
       * Search for a symbol in the local (current) context.
       *
       * @param name the symbol's name.
       * @param symbol the symbol.
       * @return
       *   <tt>true</tt> if the symbol exists; <tt>false</tt> if the
       *   symbol does not exist in the current context.
       */
      inline bool findLocal(const std::string &name, Symbol *symbol) {
        context_iterator it = _current->find(name);
        return it != _current->end();
      }

      /**
       * Search for a symbol in the avaible contexts, starting with the first
       * one and proceeding until reaching the outermost context.
       *
       * @param name the symbol's name.
       * @param from how many contexts up from the current one (zero).
       * @return
       *    <tt>nullptr</tt> if the symbol cannot be found in any of the
       *    contexts; or the symbol and corresponding attributes.
       */
      inline Symbol *find(const std::string &name, size_t from = 0) const {
        if (from >= _contexts.size())
          return nullptr;
        for (size_t ix = _contexts.size() - from; ix > 0; ix--) {
          context_type &ctx = *_contexts[ix - 1];
          context_iterator it = ctx.find(name);
          if (it != ctx.end()) {
            return it->second; // symbol data
          }
        }
        return nullptr;
      }

    };

  } // namespace semantics
} // namespace cdk

#endif

// $Log: SymbolTable.h,v $
// Revision 1.9  2013/02/11 20:56:50  david
// *** empty log message ***
//
// Revision 1.8  2013/02/11 12:10:44  david
// Fixed memory leak in symbol table (one other leak remaining).
//
// Revision 1.7  2013/02/10 19:18:24  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.6  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.5 2012/04/10 19:01:05 david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.4 2012/03/06 15:07:46 david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
