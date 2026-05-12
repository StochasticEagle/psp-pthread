/*
 * mutex9.c
 *
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-embedded (PTE) - POSIX Threads Library for embedded systems
 *      Copyright(C) 2008 Jason Schmidlapp
 *
 *      Contact Email: jschmidlapp@users.sourceforge.net
 *
 *
 *      Based upon Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2005 Pthreads-win32 contributors
 *
 *      Contact Email: rpj@callisto.canberra.edu.au
 *
 *      The original list of contributors to the Pthreads-win32 project
 *      is contained in the file CONTRIBUTORS.ptw32 included with the
 *      source code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 * --------------------------------------------------------------------------
 *
 * Every mutex API must reject NULL / uninitialised handles with EINVAL
 * rather than dereferencing them. On hosted targets a bad load would
 * raise SIGSEGV; on the embedded targets this library runs on the
 * kernel traps and the process dies, so the API itself has to validate
 * the pointer. This guards against the case where a caller ignored an
 * ENOMEM return from pthread_mutex_init and the mutex value stayed
 * NULL, plus the simpler case of forgetting to call init at all.
 *
 * Depends on API functions:
 *      pthread_mutex_lock()
 *      pthread_mutex_trylock()
 *      pthread_mutex_timedlock()
 *      pthread_mutex_unlock()
 *      pthread_mutex_destroy()
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "test.h"


int
pthread_test_mutex9()
{
  /* Uninitialised mutex variable (zero-initialised by C, so == NULL). */
  pthread_mutex_t mutex = NULL;
  struct timespec abstime = { 0, 0 };

  /* Passing a NULL pointer-to-mutex must give EINVAL, not crash. */
  assert(pthread_mutex_lock(NULL) == EINVAL);
  assert(pthread_mutex_trylock(NULL) == EINVAL);
  assert(pthread_mutex_timedlock(NULL, &abstime) == EINVAL);
  assert(pthread_mutex_unlock(NULL) == EINVAL);
  assert(pthread_mutex_destroy(NULL) == EINVAL);

  /* A valid pointer to a NULL-valued mutex (init failed or skipped)
   * must also give EINVAL — this is the case that used to crash on
   * targets without signal handling for bad loads.
   */
  assert(mutex == NULL);
  assert(pthread_mutex_lock(&mutex) == EINVAL);
  assert(pthread_mutex_trylock(&mutex) == EINVAL);
  assert(pthread_mutex_timedlock(&mutex, &abstime) == EINVAL);
  assert(pthread_mutex_unlock(&mutex) == EINVAL);
  assert(pthread_mutex_destroy(&mutex) == EINVAL);

  /* The mutex value must remain NULL after rejection — the API must
   * not have written through the pointer on the error path. */
  assert(mutex == NULL);

  return 0;
}
