/*
 * $Id: integer.h,v 1.2 2012/02/18 19:39:28 david Exp $
 *
 * Integer operations.
 * Copyright 2006-2012 by David Martins de Matos
 *
 * $Log: integer.h,v $
 * Revision 1.2  2012/02/18 19:39:28  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:11  david
 * First commit of what should probably be called RTS2.
 *
 */

#ifndef __RTS_INTEGER_H__
#define __RTS_INTEGER_H__

/**
 * Numbers represented as strings.
 * Assumes that the string is clean (may have starting spaces).
 * Negative numbers are supported.
 */
int atoi(const char *s);

const char *itoa(int value, char *str, unsigned long length);
void printi(int i);

int readi();

#endif
