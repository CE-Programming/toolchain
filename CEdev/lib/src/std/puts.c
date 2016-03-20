/*======================================================================
								       
		     Copyright (C) 1987-2008 by			       
		            Zilog, Inc.           	               
			All Rights Reserved			       
							 	       
		        San Jose, California     		       
								       

========================================================================
                                eZ80

puts.c

  Puts a line to the output device.

=======================================================================*/
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <cio.h>

/*************************************************
*
* puts - put a string to stdout
*
* Inputs:
*	string - address of string
*
* Returns:
*	Non-zero if an error occurs, else zero
*
*************************************************/
int puts(char *str)
{
  for(;*str;++str)
    putch(*str);
  putch('\n');
  putch('\r');
  return(0);
} /* puts */
