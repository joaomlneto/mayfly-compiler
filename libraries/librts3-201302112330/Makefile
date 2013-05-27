# $Id: Makefile,v 1.12 2013/02/03 18:46:39 david Exp $

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

LIBNAME=rts

INST_INC_DIR = $(ROOT)/usr/include/rts
INST_LIB_DIR = $(ROOT)/usr/lib
INST_DOC_DIR = $(ROOT)/usr/share/doc/packages

#FORMAT=elf
FORMAT=elf32
#FORMAT=elf64

COMMON_FLAGS = -O3 -ggdb -Wall -ansi -pedantic -nostdlib -fno-builtin -m32
CFLAGS       = $(COMMON_FLAGS) -std=c99 
CXXFLAGS     = $(COMMON_FLAGS)

SRC_C   = file.c float.c integer.c string.c
SRC_CPP = 
SRC_ASM = lib32.asm kernel.asm

OFILES_C   = $(SRC_C:%.c=%.o)
OFILES_CPP = $(SRC_CPP:%.cpp=%.o)
OFILES_ASM = $(SRC_ASM:%.asm=%.o)
OFILES     = $(OFILES_ASM) $(OFILES_C) $(OFILES_CPP)

YASM=yasm -f$(FORMAT) -gDWARF2

%.o:: %.asm
	$(YASM) $<

%.o:: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: lib$(LIBNAME).a

lib$(LIBNAME).a: $(OFILES)
	ar crl $@ $^

clean:
	rm -f lib$(LIBNAME).a $(OFILES) a.out core

install: all
	mkdir -p $(INST_INC_DIR) $(INST_LIB_DIR) $(INST_DOC_DIR)
	cp -a lib$(LIBNAME).a $(INST_LIB_DIR)
	#mv doc $(INST_DOC_DIR)/rts

#=====================================================================
#==========             T  H  E         E  N  D             ==========
#=====================================================================

# $Log: Makefile,v $
# Revision 1.12  2013/02/03 18:46:39  david
# *** empty log message ***
#
# Revision 1.11  2012/02/18 19:39:27  david
# Minor cleanup work.
#
