#ifndef CTYPE_H
#define CTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE  1
#define FALSE 0

int isalnum(int c);
int isalpha(int c);
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

#ifdef __cplusplus
}
#endif

#endif
