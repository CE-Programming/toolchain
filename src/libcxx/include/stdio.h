// -*- C++ -*-
#ifndef _EZCXX_STDIO_H
#define _EZCXX_STDIO_H

#include_next <stdio.h>

#pragma clang system_header

namespace std {
using ::size_t;
using ::FILE;

using ::fopen;
using ::freopen;
using ::fclose;
using ::fflush;
using ::ferror;
using ::feof;
using ::clearerr;
using ::fread;
using ::fwrite;
using ::ftell;
using ::fseek;
using ::rewind;
using ::fgetc;
using ::fgets;
using ::ungetc;
using ::fputc;
using ::fputs;
using ::remove;
using ::rename;
using ::getchar;
using ::putchar;
using ::puts;
using ::getc;
using ::putc;
using ::printf;
using ::vprintf;
using ::sprintf;
using ::vsprintf;
using ::snprintf;
using ::vsnprintf;
using ::fprintf;
using ::vfprintf;
using ::asprintf;
using ::vasprintf;
using ::sscanf;
using ::vsscanf;
using ::perror;
} // namespace std

#endif // _EZCXX_STDIO_H
