/* Copyright (c) 2000-2008 Zilog, Inc. */

#include <stdlib.h>
#include <stddef.h>

/**
 *
 * atoi - ASCII to integer conversion
 *
 * Inputs:
 *	str - pointer to the character string
 *
 * Returns:
 *	the value of the number
 *
 */
 
int atoi(char *cp) {
  return(strtol(cp,NULL,10));
}
