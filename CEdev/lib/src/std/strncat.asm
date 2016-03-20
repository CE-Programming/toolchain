; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strncat.asm"
	.assume ADL=1
	SEGMENT code
;   char *strncat(char *s1,char *s2,size_t n)
_strncat       equ 0000D8h

	XDEF _strncat
	END
