/*
 * $Id: integer.c,v 1.2 2012/02/18 19:39:27 david Exp $
 *
 * Integer operations.
 * Copyright 2006-2012 by David Martins de Matos
 *
 * Based on lib.asm (by Pedro Reis Santos, c. 2005)
 *
 * $Log: integer.c,v $
 * Revision 1.2  2012/02/18 19:39:27  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:09  david
 * First commit of what should probably be called RTS2.
 *
 */

#include "integer.h"
#include "string.h"

// this is the maximum buffer size for reading/writing integers as strings.
#define BUFFER_SIZE 256UL

/**
 * Convert strings to numbers.
 * Assumes that the string is clean (may have starting spaces).
 * Negative numbers are supported.
 * @param s the input string containing the number
 * @returns integer
 */
int atoi(const char *s) {
  while (*s == ' ')
    s++;

  int sign = 1;
  if (*s == '-') {
    sign = -1;
    s++;
  }
  while (*s == '0')
    s++;

  char c;
  int result = 0;
  while ((c = *s++) != '\0')
    result = 10 * result + (c - '0');
  result *= sign;
  return result;
}

/**
 * Convert numbers to strings (based on groff version).
 * Assumes that "str" has enough space for all digits.
 *
 * @param i the number to be converted
 * @param str the buffer where the number is going to be written
 * @param length maximum buffer length
 * @returns buffer with number as string
 */
const char *itoa(int i, char *str, unsigned long length) {
  if (length <= 0)
    return 0; // NULL pointer
  str[length - 1] = '\0';
  char *p = str + length - 1; /* points to terminating '\0' */
  if (i >= 0) {
    do {
      *--p = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  } else {
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}

/**
 * Print an integer to stdout.
 * Numbers are printed by first converting them to strings.
 * @param i the integer to be printed.
 */
void printi(int i) {
  char buffer[BUFFER_SIZE];
  prints(itoa(i, buffer, BUFFER_SIZE));
}

/**
 * Read an integer from stdin.
 * @return integer
 */
int readi() {
  char buffer[BUFFER_SIZE];
  const char *ret = readln(buffer, BUFFER_SIZE);
  if (ret == 0)
    return 0x80000000;
  return atoi(ret);
}
