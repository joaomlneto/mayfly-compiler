/*
 * $Id: string.h,v 1.2 2012/02/18 19:39:27 david Exp $
 *
 * Integer operations.
 * Copyright 2006-2012 by David Martins de Matos
 *
 * $Log: string.h,v $
 * Revision 1.2  2012/02/18 19:39:27  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:10  david
 * First commit of what should probably be called RTS2.
 *
 */

#ifndef __RTS_STRING_H__
#define __RTS_STRING_H__

int strlen(const char *str);

void prints(const char *s);
void printsp(unsigned long count);
void println();

char readb();
const char *readln(char *buffer, unsigned long size);

#endif
