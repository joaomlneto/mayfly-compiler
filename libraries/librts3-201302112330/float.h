/*
 * $Id: float.h,v 1.2 2012/02/18 19:39:27 david Exp $
 *
 * Floating point operations (float and double).
 * Copyright 2006-2012 by David Martins de Matos
 *
 * $Log: float.h,v $
 * Revision 1.2  2012/02/18 19:39:27  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:11  david
 * First commit of what should probably be called RTS2.
 *
 */

#ifndef __RTS_FLOAT_H__
#define __RTS_FLOAT_H__

double atod(const char *s);
char *dtoa(double d, int ndig, char *s);

#endif
