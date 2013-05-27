/*
 * $Id: kernel.h,v 1.2 2012/02/18 19:39:28 david Exp $
 *
 * System call interface.
 * Selected declarations for use by other parts of the RTS.
 * Copyright 2012 by David Martins de Matos
 *
 * $Log: kernel.h,v $
 * Revision 1.2  2012/02/18 19:39:28  david
 * Minor cleanup work.
 *
 * Revision 1.1  2012/02/07 14:16:38  david
 * Replaced the system call interface.
 *
 */
#ifndef __RTS_KERNEL_H__
#define __RTS_KERNEL_H__

// These are basic file-related syscalls: see kernel.asm
// The declarations used here are Linux-friendly without C library typedefs (but compatible).
// For more information (manual pages): man 2 name-of-call-without-sys_-prefix
// Example: man 2 read
long int sys_read(int fd, void *buffer, unsigned long count);
long int sys_write(int fd, const void *buffer, unsigned long count);

// These two declarations are actually unnecessary (they are not used by the RTS itself).
int sys_open(const char *pathname, int flags, unsigned int mode);
int sys_close(int fd);

#endif
