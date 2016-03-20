/* Copyright (c) 2000-2008 Zilog, Inc. */

#include <stddef.h>
#include <math.h>
#include <stdlib.h>

/**
 *
 * atof - ASCII to float conversion
 *
 * Inputs:
 *	str - pointer to the character string
 *
 * Returns:
 *	the value of the number
 *
 */
 
double atof(char *str) {
  return(strtod(str,NULL));
}
