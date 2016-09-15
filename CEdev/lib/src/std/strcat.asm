; (c) Copyright 2007-2008 Zilog, Inc.

	SEGMENT code
	.assume ADL=1
	XDEF _strcat
	
;   char *strcat(char *s1,char *s2)
_strcat        equ 0000C0h
	
	END

