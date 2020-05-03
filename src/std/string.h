/*
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *  Modified by Matt "MateoConLechuga" Waltz for TI84+CE platform
 */
#ifndef STRING_H
#define STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif

void *memcpy(void *, const void *, size_t);
void *memchr(const void *, int, size_t);
void *memset(void *, int, size_t);
void *memmove(void *, const void *, size_t);
int memcmp(const void *, const void *, size_t);

char *strcpy(char *, const char *);
char *strncpy(char *, const char *, size_t);
char *strcat(char *, const char *);
char *strncat(char *, const char *, size_t);
char *strchr(const char *, int);
char *strpbrk(const char *, const char *);
char *strrchr(const char *, int);
char *strstr(const char *, const char *);
char *strtok(char *, const char *);
char *strerror(int errnum);
char *strdup(const char *);
char *strndup(const char *, size_t n);
size_t strcspn(const char *, const char *);
size_t strspn(const char *, const char *);
size_t strlen(const char *);
size_t strnlen(const char *, size_t);
int strcmp(const char *, const char *);
int strncmp(const char *, const char *, size_t);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);

#ifdef __cplusplus
}
#endif

#endif
