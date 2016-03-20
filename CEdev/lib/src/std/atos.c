/* Copyright (c) 2000-2008 Zilog, Inc. */

#include <stdlib.h>
#include <stddef.h>

/**
 *
 * atos - ASCII to short integer conversion
 *
 * Inputs:
 *	str - pointer to the character string
 *
 * Returns:
 *	the value of the number
 *
 */

short int atos(char *cp) {
  return(strtol(cp,NULL,10));
}
