/* SysV shmdt for Hurd.
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

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "sysvshm.h"

/* Detach shared memory segment starting at address specified by
   SHMADDR from the caller's data segment.  */
int
__shmdt (const void *shmaddr)
{
  error_t err;
  size_t size;

  err = __sysvshm_remove ((void *) shmaddr, &size);
  if (err)
    {
      errno = err;
      return -1;
    }

  __munmap ((void *) shmaddr, size);
  return 0;
}

weak_alias(__shmdt, shmdt)
