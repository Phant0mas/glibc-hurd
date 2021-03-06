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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/shm.h>


/* Description of an shm attachment.  */
struct sysvshm_attach
{
  /* Linked list.  */
  struct sysvshm_attach *next;

  /* Map address.  */
  void *addr;

  /* Map size.  */
  size_t size;
};

/* List of attachments.  */
static struct sysvshm_attach *sysvshm_list;

/* A lock to protect the linked list of shared memory attachments.  */
static struct mutex sysvshm_lock = MUTEX_INITIALIZER;


/* Adds a segment attachment.  */
error_t
__sysvshm_add (void *addr, size_t size)
{
  struct sysvshm_attach *shm;

  shm = malloc (sizeof (*shm));
  if (shm == NULL)
    return errno;

  __mutex_lock (&sysvshm_lock);
  shm->addr = addr;
  shm->size = size;
  shm->next = sysvshm_list;
  sysvshm_list = shm;
  __mutex_unlock (&sysvshm_lock);

  return 0;
}

/* Removes a segment attachment.  On success, returns 0 and sets *SIZE to its
   size. Returns EINVAL if not found.  */
error_t
__sysvshm_remove (void *addr, size_t *size)
{
  struct sysvshm_attach *shm;
  struct sysvshm_attach **pshm = &sysvshm_list;

  __mutex_lock (&sysvshm_lock);
  shm = sysvshm_list;
  while (shm != NULL)
    {
      shm = *pshm;
      if (shm->addr == addr)
	{
	  *pshm = shm->next;
	  *size = shm->size;
	  __mutex_unlock (&sysvshm_lock);
	  free (shm);
	  return 0;
	}
      pshm = &shm->next;
      shm = shm->next;
    }
  __mutex_unlock (&sysvshm_lock);
  return EINVAL;
}
