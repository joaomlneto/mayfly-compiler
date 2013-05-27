/*
 * $Id: float.c,v 1.2 2012/02/18 19:39:27 david Exp $
 *
 * Floating point operations (float and double).
 * Copyright 2006-2012 by David Martins de Matos
 *
 * Based on dbl.c (by Pedro Reis Santos, c. 2005)
 *
 * $Log: float.c,v $
 * Revision 1.2  2012/02/18 19:39:27  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:11  david
 * First commit of what should probably be called RTS2.
 *
 */

#include "float.h"
#include "integer.h"
#include "string.h"

double readd() {
  char buf[80];
  if (readln(buf, 80) == 0)
    return 0;
  return atod(buf);
}

void printd(double d) {
  char buf[80];
  prints(dtoa(d, 7, buf));
}

double atod(const char *s) {
  int dot = 0, sign = 1;

  while (*s == ' ')
    s++;
  if (*s == '-')
    sign = -1, s++;
  while (*s == '0')
    s++;

  double d = 0;
  while (*s >= '0' && *s <= '9')
    d = d * 10 + (*s++ - '0');
  if (*s == '.') {
    s++;
    while (*s >= '0' && *s <= '9') {
      d = d * 10 + (*s++ - '0');
      if (dot <= 0)
        dot--;
    }
  }

  int exp = 0;
  if (*s == 'E' || *s == 'e')
    exp = atoi(s + 1);
  exp += dot;
  if (exp > 0)
    while (exp-- > 0)
      d = d * 10;
  else
    while (exp++ < 0)
      d = d / 10;
  if (sign < 0)
    d = -d;

  return d;
}

/* IEEE_ARITHMETIC */
#define DBL_MAX 1.7976931348623157e+308

char *dtoa(double d, int ndig, char *s) {
  static char str[32];
  int pos = 0;

  if (s == 0)
    s = str;

  if (d == 0.0) {
    s[0] = '0';
    s[1] = 0;
    return s;
  }

  if (d < 0)
    s[pos++] = '-', d = -d;

  int base = 0;
  double num = 0;
  if (d >= 1.0) {
    for (num = 1, base = 0; num < DBL_MAX; num *= 10, base++)
      if (num * 10 > d)
        break;
  } else
    for (num = 0.1, base = -1; num > 0; num /= 10, base--)
      if (num <= d)
        break;

  d /= num;

  int i = 0;
  for (i = 0; i < ndig && d != 0; i++) {
    s[pos++] = '0' + (int)d;
    if (i == 0)
      s[pos++] = '.';
    d = (d - ((int)d)) * 10;
  }
  if (d >= 5) {
    /* arredondamento simetrico */
    while (s[pos - 1] == '9')
      pos--;
    if (s[pos - 1] != '.') /* ver se e' '.' ou ultimo digito */
      s[pos - 1]++;
    else {
      pos--;
      if (s[pos - 1] != '9')
        s[pos - 1]++;
      else {
        s[pos - 1] = '1';
        base++;
      }
    }
  } else
    while (s[pos - 1] == '0')
      pos--;

  if (s[pos - 1] == '.')
    pos--;
  if (base != 0) {
    s[pos++] = 'E';
    if (base < 0)
      s[pos++] = '-', base = -base;
    if (base > 100) {
      s[pos++] = '0' + base / 100;
      base %= 100;
      s[pos++] = '0' + base / 10;
      base %= 10;
      s[pos++] = '0' + base;
    } else if (base > 10) {
      s[pos++] = '0' + base / 10;
      base %= 10;
      s[pos++] = '0' + base;
    } else
      s[pos++] = '0' + base;
  }

  s[pos] = 0;
  return s;
}

float atof(const char *s) {
  return atod(s);
}
char *ftoa(float f, int ndig, char *s) {
  return dtoa(f, ndig, s);
}
