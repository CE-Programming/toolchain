#ifndef __FILEIOC_STDIO_H
#define __FILEIOC_STDIO_H

#include <cdefs.h>
#include <fileioc.h>
#include <stdio.h>

__BEGIN_DECLS

extern FILE _file_streams[FOPEN_MAX];

__END_DECLS

#endif /* __FILEIOC_STDIO_H */
