/*======================================================================
								       
		     Copyright (C) 1987-2008 by			       
		            Zilog, Inc.           	               
			All Rights Reserved			       
							 	       
		        San Jose, California     		       
								       

========================================================================

                        eZ80 Runtime
  putchar()

=======================================================================*/
#include <stdio.h>
#include <cio.h>

/*************************************************
*
* putchar - put a character to stdout
*
* Inputs:
*	character to output
*
* Returns:
*	the character written
*
*************************************************/
int putchar(int ch)
{
	return (0!=putch(ch)) ? EOF : ch ;
}


