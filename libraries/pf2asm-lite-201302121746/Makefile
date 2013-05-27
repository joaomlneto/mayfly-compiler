# $Id: Makefile,v 1.10 2013/02/12 18:56:15 david Exp $
#---------------------------------------------------------------
#             CONFIGURE THESE VARIABLES IF NEEDED
#---------------------------------------------------------------

ROOT = ${HOME}/compiladores/root
CDK_INC_DIR = $(ROOT)/usr/include
CDK_LIB_DIR = $(ROOT)/usr/lib

L_NAME=PFScanner
Y_NAME=PFParser

#---------------------------------------------------------------
#    PROBABLY, NO NEED TO CHANGE ANYTHING BEYOND THIS POINT
#---------------------------------------------------------------

LFLAGS   = 
YFLAGS   = -dtv
CXXFLAGS = -std=c++11 -DYYDEBUG=1 -Wall -O3 -ggdb -Isemantics -I. -I$(CDK_INC_DIR) -I$(CDK_INC_DIR)/cdk
LDFLAGS  = -L$(CDK_LIB_DIR) -lcdk
COMPILER = pf2asm

SRC_CPP = $(wildcard nodes/**/*.cpp) $(wildcard semantics/*.cpp) $(wildcard ./*.cpp)
OFILES  = $(SRC_CPP:%.cpp=%.o)

#---------------------------------------------------------------
#                DO NOT CHANGE AFTER THIS LINE
#---------------------------------------------------------------

all: nodes/all.h $(COMPILER)

%.tab.o:: %.tab.c
	$(CXX) $(CXXFLAGS) -c $< -o $@
#	$(CXX) $(CXXFLAGS) -Wno-write-strings -c $< -o $@

%.o:: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o:: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.tab.c:: %.y
	 byacc -dtv -b $* $<

%.tab.h:: %.y
	 byacc -dtv -b $* $<

$(L_NAME).cpp: $(L_NAME).l
	flex $(LFLAGS) $<

$(Y_NAME).tab.c: $(Y_NAME).y
$(Y_NAME).tab.h: $(Y_NAME).y

# this is needed to force byacc to run
$(L_NAME).o: $(L_NAME).cpp $(Y_NAME).tab.h

.PHONY: ./mknodedecls.pl
nodes/all.h: ./mknodedecls.pl
	./mknodedecls.pl > nodes/all.h

$(COMPILER): $(L_NAME).o $(Y_NAME).tab.o $(OFILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) *.tab.[ch] *.o $(OFILES) $(L_NAME).cpp $(Y_NAME).output $(COMPILER)

depend: nodes/all.h
	$(CXX) $(CXXFLAGS) -MM $(SRC_CPP) > .makedeps

-include .makedeps

#---------------------------------------------------------------
#                           THE END
#---------------------------------------------------------------
# $Log: Makefile,v $
# Revision 1.10  2013/02/12 18:56:15  david
# Major code cleanup and simplification. Uses CDK8. C++11 is required.
#
# Revision 1.9  2012/02/19 20:30:16  david
# Updated to support the new CDK7. Removed STRold, LOAD2, STORE2, EXTRN, GLOBL.
# Added DDUP, DLOAD, DSTORE, EXTERN, GLOBAL.
#
# Revision 1.8  2010/03/23 08:44:14  david
# Updated to work with CDK5.
#
# Revision 1.7  2009/03/02 16:09:05  david
# Makefile cleanup.
#
# Revision 1.6  2009/03/02 13:26:51  david
# Code cleanup. Removed a few minor warnings.
#
# Revision 1.5  2009/02/28 21:01:06  david
# Minor cleanup.
#
# Revision 1.4  2009/02/25 07:31:53  david
# First working version of pf2asm. This version still uses
# byacc.
#
# Revision 1.3  2009/02/23 20:53:38  david
# First PF implementation. Does not work with PF syntax nor
# does it do anything useful.
#