/* Copyright (C) 2005 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <sys/param.h>
#include <sys/socket.h>


ssize_t
__recvfrom_chk (int fd, void *buf, size_t n, size_t buflen, int flags,
		__SOCKADDR_ARG addr, socklen_t *addr_len)
{
  /* In case N is greater than BUFLEN, we read BUFLEN+1 bytes.
     This might overflow the buffer but the damage is reduced to just
     one byte.  And the program will terminate right away.  */
  ssize_t nrecv = __recvfrom (fd, buf, MIN (n, buflen + 1), flags,
			      addr, addr_len);
  if (nrecv > 0 && (size_t) nrecv > buflen)
    __chk_fail ();
  return nrecv;
}