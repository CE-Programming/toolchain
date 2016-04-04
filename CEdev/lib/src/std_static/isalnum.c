/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/

#define CTL	0x80	/* control character */
#define WS	0x40	/* whitespace character */
#define SP	0x20	/* space character */
#define HEX	0x10	/* hex digit (A-Z,a-z) */
#define UC	0x08	/* uppercase letter */
#define LC	0x04	/* lowercase letter */
#define PUN	0x02	/* punctuation */
#define DIG	0x01	/* decimal digit (0-9) */

extern __rom unsigned char __maptab[];

int isalnum(int c)
{
  if( (unsigned char)c & (unsigned char)0x80 )
	return (0);

  return(__maptab[c] & (unsigned char)(UC|LC|DIG));
}

