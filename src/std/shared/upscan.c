/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stdarg.h>
#include <format.h>
#include <ctype.h>
#include <string.h>

#define rom  // ez8 keyword

/*  NOTE:                                                                     */
/*     This code is duplicated in the optimizer to implement the  GENPRINTF   */
/*     feature.  If you change this, merge the changes in to the optimizer    */
/*     file genprintf.c too.!                                                 */

/* classes */

#define FLAGS 0
#define DIGIT 1
#define SIZE 2
#define DOT 3
#define TYPES 4
#define PERCENT 5
#define AST 6
#define OTHER 7

/* actions */

#define ACC -1
#define ERR -2

#define CR 13
#define LF 10

#define TRUE 1
#define FALSE 0

/*
						    P
						    E
				F   D		T   R	   O
				L   I	S	Y   C	   T
				A   G	I   D	P   E	A  H
				G   I	Z   O	E   N	S  E
				S   T	E   T	S   T	T  R	*/
static rom const char pscan_fsa[9][8] = {
		/* 0 */      {ERR,ERR,ERR,ERR,ERR,  1,ERR,ERR},
		/* 1 */      {	2,  3,	6,  4,	7,  8,	3,ERR},
		/* 2 */      {	2,  3,	6,  4,	7,ERR,	3,ERR},
		/* 3 */      {ERR,  3,	6,  4,	7,ERR,  3,ERR},
		/* 4 */      {ERR,  5,ERR,ERR,  7,ERR,	5,ERR},
		/* 5 */      {ERR,  5,	6,ERR,	7,ERR,  5,ERR},
		/* 6 */      {ERR,ERR,ERR,ERR,	7,ERR,ERR,ERR},
		/* 7 */      {ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC},
		/* 8 */      {ACC,ACC,ACC,ACC,ACC,ACC,ACC,ACC},
			     };

/*************************************************
*
* _u_pscan - scan a printf format string
*
* Adopted from funtion of same name in target rtl
*   pfmt  - pointer to format string to parse, advanced to a '%'
*         - on return is advanced to first char past format spec
*
*   node- pointer to  the FCALL node, used for args
*
*   p_argnum - pointer to the index in node->sons[] of the next arg.
*             (These count downward!)

*
*************************************************/
char _PTR_ _u_pscan (char _PTR_ fmt,struct fmt_type _PTR_ str,va_list _PTR_ argp)
{
  int pstate;
  int state = 0;
  int class;
  char ch;
  unsigned char precision_given = FALSE;

  str->flags = 0;
  str->field_width = 0;
  str->precision = 0;
  str->size = 0;
  str->type = '\0';

  for(;;) {
    ch = *(fmt++);
    switch (ch) {
      case '-':
      case '+':
      case ' ':
      case '#':
		class = FLAGS;
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
		class = DIGIT;
		break;
      case '.':
		class = DOT;
		break;
      case '*':
		class = AST;
		break;
      case 'h':
      case 'l':
      case 'L':
		class = SIZE;
		break;
      case 'd':
      case 'i':
      case 'o':
      case 'u':
      case 'x':
      case 'X':
      case 'f':
      case 'e':
      case 'E':
      case 'g':
      case 'G':
      case 'c':
      case 's':
      case 'p':
      case 'n':
		class = TYPES;
		break;
      case '%':
		class = PERCENT;
		break;

      default:
		class = OTHER;
		break;
    }

    pstate = state;
    state = pscan_fsa[state][class];

    switch (state) {
      case ACC:
		str->status = FMT_OK;
		return(fmt-1);
      case ERR:
		str->status = FMT_ERR;
		return(fmt-1);

      case 2:
		switch (ch) {

		  case '-':
			str->flags |= FMT_FLAG_MINUS;
			break;
		  case '+':
			str->flags |= FMT_FLAG_PLUS;
			break;
		  case ' ':
			str->flags |= FMT_FLAG_SPACE;
			break;
		  case '#':
			str->flags |= FMT_FLAG_POUND;
			break;
		}
		break;

      case 3:
		if (ch == '*')
		  str->field_width = va_arg(*argp,int);
		else {
		  if (pstate != state &&
			ch == '0')
		    str->flags |= FMT_FLAG_PAD_ZERO;
		  str->field_width = str->field_width * 10 + (ch - '0');
		}
		break;
      case 4:
		precision_given = TRUE;
		break;
      case 5:
		if (ch == '*')
		  str->precision = va_arg(*argp,int);
		else
		  str->precision = str->precision * 10 + (ch - '0');
		break;
      case 6:
		str->size = ch;
		break;
      case 7:
		str->type = tolower(ch);
		if (isupper(ch))
		  str->flags |= FMT_FLAG_UPPERCASE;
		if (str->field_width < 0)
		{
		  str->flags |= FMT_FLAG_MINUS;
		  str->field_width = -str->field_width;
		}
		if (!precision_given || str->precision < 0)
		{
		  if (ch == 'e' ||
		      ch == 'E' ||
		      ch == 'g' ||
		      ch == 'G' ||
		      ch == 'f')
		    str->precision = DEFAULT_PRECISION;
		  else
		    str->precision = 0;
		}
                if (ch == 's' && precision_given)
		  str->flags |= FMT_FLAG_PRECISION;
		break;
      case 8:
		str->status = FMT_PASS_THRU;
		str->chr = ch;
		return(fmt);
    }
  }
}



