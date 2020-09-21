/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by			*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/

/*	Mapping table for isxxx functions	*/

#define CTL	0x80	/* control character */
#define WS	0x40	/* whitespace character */
#define SP	0x20	/* space character */
#define HEX	0x10	/* hex digit (A-Z,a-z) */
#define UC	0x08	/* uppercase letter */
#define LC	0x04	/* lowercase letter */
#define PUN	0x02	/* punctuation */
#define DIG	0x01	/* decimal digit (0-9) */

const unsigned char __maptab[128] = {
/*  0 */ CTL,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
/*  8 */ PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
/* 10 */ PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
/* 18 */ PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
/* 20 */ WS|SP,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
/* 28 */ PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
/* 30 */ DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,
/* 38 */ DIG,DIG,PUN,PUN,PUN,PUN,PUN,PUN,
/* 40 */ PUN,UC|HEX,UC|HEX,UC|HEX,UC|HEX,UC|HEX,UC|HEX,UC,
/* 48 */ UC,UC,UC,UC,UC,UC,UC,UC,
/* 50 */ UC,UC,UC,UC,UC,UC,UC,UC,
/* 58 */ UC,UC,UC,PUN,PUN,PUN,PUN,PUN,
/* 60 */ PUN,LC|HEX,LC|HEX,LC|HEX,LC|HEX,LC|HEX,LC|HEX,LC,
/* 68 */ LC,LC,LC,LC,LC,LC,LC,LC,
/* 70 */ LC,LC,LC,LC,LC,LC,LC,LC,
/* 78 */ LC,LC,LC,PUN,PUN,PUN,PUN,PUN
};
