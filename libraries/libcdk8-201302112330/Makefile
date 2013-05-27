# $Id: Makefile,v 1.28 2013/02/11 20:56:50 david Exp $
#=====================================================================
#==========      TWEAK THE 'ROOT' VARIABLE IF NECESSARY     ==========
#=====================================================================

# install in user's home directory
ROOT = #${HOME}/compiladores/root

# if installing in system dirs, use the following line instead
#ROOT= 

#=====================================================================
#==========      DO NOT CHANGE ANYTHING AFTER THIS LINE     ==========
#=====================================================================

LIBNAME=cdk

CXXFLAGS=-O3 -Isemantics -I. -ggdb -Wall -std=c++11 -pedantic

INST_INC_DIR = $(ROOT)/usr/include/$(LIBNAME)
INST_LIB_DIR = $(ROOT)/usr/lib
INST_DOC_DIR = $(ROOT)/usr/share/doc/packages/$(LIBNAME)

SRC_CPP = $(wildcard generators/*.cpp) $(wildcard semantics/*.cpp) \
          $(wildcard nodes/*.cpp) $(wildcard nodes/expressions/*.cpp) \
	        main.cpp
OFILES = $(SRC_CPP:%.cpp=%.o)

YACC=byacc
LEX=flex

%.o:: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: link lib$(LIBNAME).a docs

# dirty hack
link:
	if [ ! -e cdk ]; then ln -s . cdk; fi

docs: doc/.docsdone

doc/.docsdone: $(LIBNAME).doxyfile
	$(RM) cdk
	doxygen $<
	touch $@
	if [ ! -e cdk ]; then ln -s . cdk; fi

$(LIBNAME).doxyfile: $(SRC_CPP)

lib$(LIBNAME).a: $(OFILES)
	ar crl $@ $^

clean:
	rm -f lib$(LIBNAME).a $(OFILES) a.out core y.tab.[ch] lex.yy.c

install: all
	mkdir -p $(INST_LIB_DIR) $(INST_INC_DIR) $(INST_DOC_DIR)
	mkdir -p $(INST_INC_DIR)/nodes
	mkdir -p $(INST_INC_DIR)/nodes/expressions
	mkdir -p $(INST_INC_DIR)/semantics
	mkdir -p $(INST_INC_DIR)/generators
	cp -a Compiler.h CompilerFactory.h Parser.h $(INST_INC_DIR)
	cp -a generators/*.h $(INST_INC_DIR)/generators
	cp -a nodes/*.h $(INST_INC_DIR)/nodes
	cp -a nodes/expressions/*.h $(INST_INC_DIR)/nodes/expressions
	cp -a semantics/Evaluator.h $(INST_INC_DIR)/semantics
	cp -a semantics/ExpressionType.h $(INST_INC_DIR)/semantics
	cp -a semantics/SymbolTable.h $(INST_INC_DIR)/semantics
	cp -a lib$(LIBNAME).a $(INST_LIB_DIR)
	#DOC cp -a doc/. $(INST_DOC_DIR)/

depend:
	$(CXX) $(CXXFLAGS) -MM $(SRC_CPP) > .makedeps

-include .makedeps

#=====================================================================
#==========             T  H  E         E  N  D             ==========
#=====================================================================
# $Log: Makefile,v $
# Revision 1.28  2013/02/11 20:56:50  david
# *** empty log message ***
#
# Revision 1.27  2013/02/10 19:18:24  david
# Code cleanup and simplification. C++11 is now mandatory.
#
# Revision 1.26  2013/02/09 19:00:34  david
# First CDK8 commit. Major code simplification.
# Starting C++11 implementation.
#
# Revision 1.25  2012/04/10 19:01:05  david
# Removed initialization-dependent static members in factories.
# Handling of ProgramNodes is now better encapsulated by visitors (not done
# by evaluators, as before). Major cleanup (comments).
#
# Revision 1.24  2012/02/18 19:38:59  david
# This is the first commit in CDK7. Evaluators and code generators are now aware
# of the debug command line options.
#
