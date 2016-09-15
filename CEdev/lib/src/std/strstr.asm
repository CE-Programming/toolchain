; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <string.h>
; char * strstr(char *s1, char *s2);
;-------------------------------------------------------------------------
	.assume ADL=1
	SEGMENT code
	XDEF _strstr
	
_strstr        equ 0000F0h

	END

