/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/

/*************************************************
*
* labs - long absolute value
*
* Inputs:
*	j	- value to calculate abs of
*
* Returns:
*	absloute value of j
*
*************************************************/
long labs(long j)
{
  if (j < 0)
    return(-j);
  else
    return(j);
}
