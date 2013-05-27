/*
 * $Id: string.c,v 1.2 2012/02/18 19:39:27 david Exp $
 *
 * Integer operations.
 * Copyright 2006-2012 by David Martins de Matos
 *
 * Most of these are portable C versions of assembly versions from
 * old versions of lib.asm (Copyright 2005 by Pedro Reis Santos)
 *
 * $Log: string.c,v $
 * Revision 1.2  2012/02/18 19:39:27  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:10  david
 * First commit of what should probably be called RTS2.
 *
 */

#include "file.h"
#include "string.h"

/**
 * Trivial C-style string length function.
 */
int strlen(const char *str) {
  int length = 0;
  while (str[length] != '\0')
    length++;
  return length;
}

/**
 * Print C-style string to stdout (descriptor 1).
 * @param str string to be written
 */
void prints(const char *str) {
  fprints(1, str);
}

/**
 * Simple new-line output function.
 */
void println() {
  prints("\n");
}

/**
 * Print spaces.
 * @param count the number of spaces to print.
 */
void printsp(unsigned long count) {
  while (count-- != 0)
    prints(" ");
}

/**
 * Read single byte (char) from stdin (descriptor 0).
 */
char readb() {
  return freadb(0);
}

/* DAVID: probably buggy!!!! */
const char *readln(char *buffer, unsigned long size) {
  if (size == 0) return 0; // error
  for (int ix = 0; ix < size; ix++) {
    buffer[ix] = '\0';
    char c = readb();
    if (c == 0)
      return 0; /* error */
    if (c == '\n')
      return buffer;
    buffer[ix] = c;
  }
  buffer[size - 1] = '\0'; /* paranoia */
  return buffer;
}
