# $Id: Makefile,v 1.2 2013/02/12 18:56:17 david Exp $
#---------------------------------------------------------------
#             CONFIGURE THESE VARIABLES IF NEEDED
#---------------------------------------------------------------

ROOT = ${HOME}/compiladores/root
RTS_LIB_DIR = $(ROOT)/usr/lib

COMPILER=../pf2asm
ASM=yasm

#---------------------------------------------------------------
#    PROBABLY, NO NEED TO CHANGE ANYTHING BEYOND THIS POINT
#---------------------------------------------------------------

COMPILER_FLAGS = 
LDFLAGS  = -m elf_i386 -L$(RTS_LIB_DIR) -lrts

SOURCES     = $(wildcard *.pf)
OBJECTS     = $(SOURCES:%.pf=%.o)
EXECUTABLES = $(SOURCES:%.pf=%)

#---------------------------------------------------------------
#                DO NOT CHANGE AFTER THIS LINE
#---------------------------------------------------------------

all: $(EXECUTABLES)

%.asm: %.pf
	$(COMPILER) $< -o $@

%.o: %.asm
	$(ASM) -felf32 $< -o $@

%:%.o
	$(LD) $< -o $@ $(LDFLAGS)

clean:
	$(RM) $(OBJECTS) $(EXECUTABLES) *.c *.asm

#---------------------------------------------------------------
#                           THE END
#---------------------------------------------------------------
# $Log: Makefile,v $
# Revision 1.2  2013/02/12 18:56:17  david
# Major code cleanup and simplification. Uses CDK8. C++11 is required.
#
# Revision 1.1  2012/02/19 20:37:37  david
# Added makefile for tests.
#
