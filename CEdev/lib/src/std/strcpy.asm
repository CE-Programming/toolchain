; (c) Copyright 2007-2008 Zilog, Inc.

	.assume ADL=1
	SEGMENT code

	XREF _strlen
	XDEF _strcpy
	
;   char * strcpy(void * d, void * s)
_strcpy        equ 0000CCh

	END

