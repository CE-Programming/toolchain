/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by			*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/

extern unsigned long _next;

/*************************************************
*
* srand - set the seed for rand
*
* Inputs:
*	seed - the seed for rand
*
* Returns:
*	 none
*
*************************************************/
void srand(unsigned int seed)
{
  _next = seed;
}


