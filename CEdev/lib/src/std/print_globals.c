/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#include <format.h>

/*  Global data used by the printf support functions.                       */
/*  The compiler may manipulate this data directly to bypass the runtime    */
/*  parsing of (s)printf formats.                                           */
#ifndef _MULTI_THREAD
char __print_buff[14];
struct fmt_type __print_fmt;
unsigned char __print_len;
char __print_leading_char;  // Initial +, -, or space for number
char* __print_out;

// This points to __print_sputch except when printf is active.
// This is so that the more commonly used function does not need to set it.
void (*__print_xputch)(char) = __print_sputch;

#else		// _MULTI_THREAD
const struct fmt_type __clear_fmt_type={0};
#endif

