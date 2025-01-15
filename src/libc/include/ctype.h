#ifndef _CTYPE_H
#define _CTYPE_H

#include <cdefs.h>

__BEGIN_DECLS

int isalnum(int c);

int isalpha(int c);

int isblank(int c);

int iscntrl(int c);

int isdigit(int c);

int isgraph(int c);

int islower(int c);

int isprint(int c);

int ispunct(int c);

int isspace(int c);

int isupper(int c);

int tolower(int c);

int toupper(int c);

int isascii(int c);

int isxdigit(int c);

__END_DECLS

#endif /* _CTYPE_H */
