; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strncmp.asm"
	.ASSUME ADL=1
	SEGMENT code
;   int strncmp(char *s1,char *s2,size_t n)
_strncmp       equ 0000DCh

	XDEF _strncmp
	END

