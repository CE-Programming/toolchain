/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#include <format.h>
#include <string.h>
#include <stdlib.h>

extern void (*__print_xputch)(char);

/* Send a character to the printf/sprintf destination                      */
/* The compiler may generate direct calls to this to bypass the runtime    */
/* parsing of printf formats.                                              */

void __print_putch(char ch)
{
	(*__print_xputch)(ch);
}
