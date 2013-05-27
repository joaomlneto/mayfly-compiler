/*
 * $Id: file.c,v 1.3 2012/02/18 19:39:27 david Exp $
 *
 * Basic file I/O operations.
 * Copyright 2012 by David Martins de Matos
 *
 * $Log: file.c,v $
 * Revision 1.3  2012/02/18 19:39:27  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:10  david
 * First commit of what should probably be called RTS2.
 *
 */

#include "kernel.h"
#include "file.h"
#include "string.h"

/**
 * Print C-style string to output channel specified by descriptor.
 * @param fd output file descriptor
 * @param str string to be written
 */
void fprints(int fd, const char *str) {
  if (str == 0) return; // NULL pointer
  sys_write(fd, str, strlen(str));
}

/**
 * Read single byte (char) from input channel specified by descriptor.
 * @param input file descriptor
 */
char freadb(int fd) {
  char character = '\0';
  sys_read(fd, (void *)&character, 1UL);
  return character;
}
