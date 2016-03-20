/*======================================================================
								       
		     Copyright (C) 1987-2008 by			       
		            Zilog, Inc.           	               
			All Rights Reserved			       
							 	       
		        San Jose, California     		       
								       

========================================================================

                        eZ80 Runtime             
  getchar()

=======================================================================*/
#include <stdio.h>
#include <cio.h>

/*************************************************
*
* getchar - get a character from stdin
*
* Inputs:
*	None
*
* Returns:
*	character or EOF
*
*************************************************/
int getchar(void)
{
  return (getch());
}


