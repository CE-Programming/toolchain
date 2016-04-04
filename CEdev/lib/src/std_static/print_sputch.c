/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#include <format.h>

/* Send a character to the sprintf destination                             */

reentrant void __print_sputch(char ch)
{
  *__print_out++ = ch;
}
