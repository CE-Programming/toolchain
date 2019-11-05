/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <format.h>
#include <stddef.h>
#include <stdarg.h>

/* actions */

#define ACC -1
#define ERR -2

#define CR 13
#define LF 10

/*					   +-{0..9}
			 {sp,tab,nl}{h,l,L}|   +-{d,i,o,u,x,e,f,g,s,c,p,n}
			       |       |   |   |       {others}
			   %   |   *   |   |   |   [   ]   |
			+-----------------------------------+ */
static char sscan_fsa[10][9] = {
	/* 0 */ 	{  2,  0,  1,  1,  1,  1,  1,  1,  1},
	/* 1 */ 	{ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC},
	/* 2 */ 	{  8,ERR,  3,  5,  4,  9,  6,ERR,ERR},
	/* 3 */ 	{ERR,ERR,ERR,  5,  4,  9,  6,ERR,ERR},
	/* 4 */ 	{ERR,ERR,ERR,  5,  4,  9,  6,ERR,ERR},
	/* 5 */ 	{ERR,ERR,ERR,ERR,ERR,  9,  6,ERR,ERR},
	/* 6 */ 	{  6,  6,  6,  6,  6,  6,  6,  7,  6},
	/* 7 */ 	{ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC},
	/* 8 */ 	{ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC},
	/* 9 */ 	{ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC},
			};

/*************************************************
*
* _u_sscan - scan a scanf format string
*
* Inputs:
*	fmt - pointer to format string
*	str - pointer to fmt_type structure
*	      where the results are put
*
* Returns:
*	new pointer to format string
*
*************************************************/
char *_u_sscan(char *fmt, struct fmt_type *str) {
  char pstate;
  char state = 0;
  unsigned char class;
  char ch;

  str->flags = 0;
  str->field_width = 0;
  str->precision = 0;
  str->size = 0;
  str->type = '\0';

  for (;;) {
    ch = *(fmt++);
    switch(ch) {
      case '%':
		class = 0;
		break;
      /*****   Treat these as pass through:
      case ' ':
      case '\t':
      case '\n':
		class = 1;
		break;
      ****/
      case '*':
		class = 2;
		break;
      case 'h':
      case 'l':
      case 'L':
		class = 3;
		break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
		class = 4;
		break;
      case 'A':
      case 'E':
      case 'F':
      case 'G':
      case 'X':
      case 'a':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'i':
      case 'n':
      case 'o':
      case 'p':
      case 's':
      case 'u':
      case 'x':
		class = 5;
		break;
      case '[':
		class = 6;
		break;
      case ']':
		class = 7;
		break;
      default:
		class = 8;
    }

    pstate = state;
    state = sscan_fsa[(unsigned char)state][class];

    switch (state) {
      case ACC:
		str->status = FMT_OK;
		return fmt-1;
      case ERR:
		str->status = FMT_ERR;
		return fmt-1;
      case 1:
      case 8:
		str->status = FMT_PASS_THRU;
		str->chr = ch;
		return fmt;
      case 3:
		str->flags |= FMT_FLAG_IGNORE;
		break;
      case 4:
		str->field_width = str->field_width * 10 + (ch - '0');
		break;
      case 5:
		str->size = ch;
		break;
      case 6:
		if (pstate != state) {
		  str->flags |= FMT_FLAG_SET;
		  str->set_begin = fmt;
                  /* Check for sets that start with [] or [^] */
                  if (*fmt == '^')
                     fmt++;
                  if (*fmt == ']')
                     fmt++;

		}
		break;
      case 7:
		str->set_end = fmt-1;
		break;
      case 9:
		str->type = ch;
		break;
    }
  }
}
