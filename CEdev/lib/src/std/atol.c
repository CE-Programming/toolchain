/* Copyright (c) 2000-2008 Zilog, Inc. */

#include <stddef.h>
#include <stdlib.h>

/**
 *
 * atol - ASCII to long conversion
 *
 * Inputs:
 *	str - pointer to the character string
 *
 * Returns:
 *	the value of the number
 *
 */
 
long atol(char *cp) {
  return(strtol(cp,NULL,10));
}
