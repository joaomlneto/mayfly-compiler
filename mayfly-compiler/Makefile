# $Id: Makefile,v 1.13 2013-05-16 14:25:24 ist164787 Exp $
#---------------------------------------------------------------
#             CONFIGURE THESE VARIABLES IF NEEDED
#---------------------------------------------------------------

ROOT = #${HOME}/compiladores/root
CDK_INC_DIR = $(ROOT)/usr/include
CDK_LIB_DIR = $(ROOT)/usr/lib64

L_NAME=MFScanner
Y_NAME=MFParser

#---------------------------------------------------------------
#    PROBABLY, NO NEED TO CHANGE ANYTHING BEYOND THIS POINT
#---------------------------------------------------------------

LFLAGS   = 
YFLAGS   = -dtv
CXXFLAGS = -std=c++11 -DYYDEBUG=1 -Wall -O0 -ggdb -Isemantics -I. -I$(CDK_INC_DIR) -I$(CDK_INC_DIR)/cdk
LDFLAGS  = -L$(CDK_LIB_DIR) -lcdk
COMPILER = mayfly

SRC_CPP = $(wildcard nodes/**/*.cpp) $(wildcard semantics/*.cpp) $(wildcard ./*.cpp)
OFILES  = $(SRC_CPP:%.cpp=%.o)

#---------------------------------------------------------------
#                DO NOT CHANGE AFTER THIS LINE
#---------------------------------------------------------------

all: nodes/all.h $(COMPILER)

%.tab.o:: %.tab.c
	$(CXX) $(CXXFLAGS) -DYYDEBUG -c $< -o $@

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
# Revision 1.13  2013-05-16 14:25:24  ist164787
# Fixed double variable declarations
#
# Revision 1.12  2013-05-15 19:51:49  ist164787
# Classic, messed Makefile flags again
#
# Revision 1.11  2013-05-15 19:51:27  ist164787
# Return node works... I hope
#
# Revision 1.10  2013-05-15 16:04:29  ist164787
# oops sorry messed up the optimization flags in mayfly again...
#
# Revision 1.9  2013-05-15 11:05:04  ist164787
# Segment management functions
#
# Revision 1.8  2013-05-14 12:08:52  ist164787
# oops modified makefile by accident. using -O3 instead of -O0 again
#
# Revision 1.7  2013-05-14 12:08:16  ist164787
# Fixed most binary expressions when dealing with left values, as they only push their addresses when visited, not their values... some nodes still need to be modified to reflect these changes
#
# Revision 1.6  2013-05-13 21:01:17  ist164787
# TypeValidator almost finished, Function Calls are full of awesome, printnode prints everything... other minor changes i dont remember
#
# Revision 1.5  2013-05-13 19:10:05  ist164787
# ExpressionAsInstruction node added
#
# Revision 1.4  2013-05-11 18:18:41  ist164787
# function declarations working, part of vardecls working
#
# Revision 1.3  2013-05-11 15:35:35  ist164787
# vardecls in pfwriter - began changes
#
# Revision 1.2  2013-03-21 17:08:48  ist164787
# *** empty log message ***
#
# Revision 1.1  2013-02-16 16:10:15  ist13500
# This is a base mayfly version.
# This is just Compact with the names changed.
#
# 
#
