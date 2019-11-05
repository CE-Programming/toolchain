/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#include <format.h>
#include <stdio.h>
#include <stdarg.h>

/*************************************************
*
* vsprintf - print to a string (variable args)
*
* Inputs:
*	string - pointer to string to write to
*	fmt - format string
*	args - argument list
*
* Returns:
*	Number of characters transmitted, or
*	-1 if an error occured.
*
*************************************************/
int vsprintf(char *string, const char *fmt, va_list args) {
    return _u_print(string, (char*)fmt, args);
}
