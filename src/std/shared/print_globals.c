/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#include <format.h>

void __print_sputch(char ch);

/*  Global data used by the printf support functions.                       */
/*  The compiler may manipulate this data directly to bypass the runtime    */
/*  parsing of (s)printf formats.                                           */
char __print_buff[14];
struct fmt_type __print_fmt;
unsigned char __print_len;
char __print_leading_char;  // Initial +, -, or space for number
char *__print_out;

// This points to __print_sputch except when printf is active.
// This is so that the more commonly used function does not need to set it.
void (*__print_xputch)(char) = __print_sputch;

