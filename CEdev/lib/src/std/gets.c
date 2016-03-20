/*======================================================================
								       
		     Copyright (C) 1987-2008 by			       
		            Zilog, Inc.           	               
			All Rights Reserved			       
							 	       
		        San Jose, California     		       
								       

========================================================================
                                eZ80

gets.c					

  Gets a line from the device.

=======================================================================*/
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <cio.h>

#define TRUE 1
#define LF 10

/*************************************************
*
* gets - get a string from the input device
*
* Inputs:
*	string - address of string
*
* Returns:
*	pointer to string or NULL
*
*************************************************/
char *gets (char *string) 
{
  char *sptr = string;
  char chr;

  while (TRUE) {
    chr = getch();

    if (chr == LF) {
      *sptr = '\0';
      return (string);
    } /* Remove LF */

    *(sptr++) = chr;

  }  /* while (TRUE) */
} /* gets */
