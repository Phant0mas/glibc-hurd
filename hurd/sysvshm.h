/* SysV shared memory for Hurd.
   Copyright (C) 2005-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _HURD_SYSVSHM_H
#define _HURD_SYSVSHM_H

#include <paths.h>
#include <hurd.h>

/* The area (from top to bottom) that is used for private keys.  These
   are all keys that have the second highest bit set.  */
#define SHM_PRIV_KEY_START	INT_MAX
#define SHM_PRIV_KEY_END	((INT_MAX / 2) + 1)

#define SHM_PREFIX		"sysvshm-"
#define SHM_DIR			_PATH_DEV "shm/"

/* The maximum number of characters in a shared memory segment file name.
   32 is the max number of characters in a 128 bit number in hex.  */
#if __WORDSIZE > 128
#error Need to increase SHM_NAMEMAX.
#else
#define SHM_NAMEMAX (sizeof (SHM_PREFIX) - 1 + 32 + 1)
#endif

/* Use this with printf and its variants.  */
#define SHM_NAMEPRI SHM_PREFIX "%0x"


/* Adds a segment attachment.  */
error_t __sysvshm_add (void *addr, size_t size);

/* Removes a segment attachment.  On success, returns 0 and sets *SIZE to its
   size. Returns EINVAL if not found.  */
error_t __sysvshm_remove (void *addr, size_t *size);

#endif /* sysvshm.h */
