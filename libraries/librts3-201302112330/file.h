/*
 * $Id: file.h,v 1.2 2012/02/18 19:39:28 david Exp $
 *
 * Basic file I/O operations.
 * Copyright 2012 by David Martins de Matos
 *
 * $Log: file.h,v $
 * Revision 1.2  2012/02/18 19:39:28  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/06 20:34:11  david
 * First commit of what should probably be called RTS2.
 *
 */
#ifndef __RTS_FILE_H__
#define __RTS_FILE_H__

void fprints(int fd, const char *str);
char freadb(int fd);

#endif
