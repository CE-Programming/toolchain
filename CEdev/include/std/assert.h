/*************************************************
 *  Copyright (C) 1999-2011 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

/* Per the 1989 C standard, assert.h should NOT be protected with include
 * guards.  One should be able to define/undefine NDEBUG and re-include
 * the file to change the assert macro.
 */

#include <debug.h>
#include <stdio.h>
#include <stdlib.h >

#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(e) if (!(e)) { \
	dbg_sprintf(dbgout,"Assertion failure: %s, file: %s, line %d\n",#e,__FILE__,__LINE__); \
	abort(); \
}
#endif
