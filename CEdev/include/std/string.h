/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#ifndef STRING_H
#define STRING_H

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned int size_t;
#endif

char * strcpy(void *s1, void *s2);
void *memcpy(void *s1, void *s2,size_t n);
int memcmp(void *s1,void *s2, size_t n);
void *memchr(void *s,int c, size_t n);
void *memset(void *s,int c, size_t n);
void *memmove(void *s1,void *s2,size_t n);

char * strncpy(char *s1, char *s2, size_t n);
char * strcat(char *s1, char *s2);
char * strncat(char *s1, char *s2, size_t n);
int strcmp(char *s1, char *s2);
int strncmp(char *s1, char *s2, size_t n);
char * strchr(char *s,int c);
size_t strcspn(char *s1, char *s2);
char * strpbrk(char *s1, char *s2);
char * strrchr(char *s,int c);
size_t strspn(char *s1, char *s2);
char * strstr(char *s1, char *s2);
char * strtok(char *s1, char *s2);
char * strerror(int errnum);
size_t strlen(char *s);

#endif
