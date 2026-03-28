//------------------------------------------------------------------------------
// Common Config
//------------------------------------------------------------------------------

#define NANOPRINTF_IMPLEMENTATION
#define NANOPRINTF_VISIBILITY_STATIC
#define NANOPRINTF_STATIC_GLOBALS

#if NANOPRINTF_USE_LONG_DOUBLE_PRECISION == 1
#define NANOPRINTF_CONVERSION_FLOAT_TYPE unsigned long long
#else
#define NANOPRINTF_CONVERSION_FLOAT_TYPE unsigned long
#endif

// Not applicable since sizeof(float) == sizeof(double) on the ez80
#define NANOPRINTF_USE_FLOAT_SINGLE_PRECISION 0

//------------------------------------------------------------------------------

#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> /* malloc */

static void npf_putc_std(int c, void *ctx) {
  (void)ctx;
  outchar((char)c);
}

static void npf_fputc_std(int c, void *ctx) {
  fputc(c, (FILE*)ctx);
}

#include "nanoprintf.h"

int vsnprintf(char *__restrict buffer, size_t bufsz, char const *__restrict format, va_list vlist) {
  npf_bufputc_ctx_t bufputc_ctx;
  bufputc_ctx.dst = buffer;
  bufputc_ctx.len = bufsz;
  bufputc_ctx.cur = 0;

  npf_putc const pc = buffer ? npf_bufputc : npf_bufputc_nop;
  int const n = npf_vpprintf(pc, &bufputc_ctx, format, vlist);

  if (buffer && bufsz) {
#ifdef NANOPRINTF_SNPRINTF_SAFE_EMPTY_STRING_ON_OVERFLOW
    buffer[(n < 0 || (unsigned)n >= bufsz) ? 0 : n] = '\0';
#else
    buffer[n < 0 ? 0 : NPF_MIN((unsigned)n, bufsz - 1)] = '\0';
#endif
  }

  return n;
}

int snprintf(char *__restrict buffer, size_t bufsz, const char *__restrict format, ...) {
  va_list val;
  va_start(val, format);
  int const rv = vsnprintf(buffer, bufsz, format, val);
  va_end(val);
  return rv;
}

int vsprintf(char *__restrict buffer, const char *__restrict format, va_list vlist)
{
  return vsnprintf(buffer, (size_t)INT_MAX, format, vlist);
}

int sprintf(char *__restrict buffer, const char *__restrict format, ...)
{
  va_list va;
  va_start(va, format);
  const int ret = vsnprintf(buffer, (size_t)INT_MAX, format, va);
  va_end(va);
  return ret;
}

int vasprintf(char **__restrict p_str, const char *__restrict format, va_list vlist) {
  *p_str = NULL;
  int str_len = vsnprintf(NULL, 0, format, vlist);
  if (str_len < 0) {
    return str_len;
  }
  size_t buf_len = (size_t)str_len + 1;
  char* buf = (char*)malloc(buf_len);
  if (buf == NULL) {
    // malloc failure
    return -1;
  }
  int ret = vsnprintf(buf, buf_len, format, vlist);
  if (ret < 0) {
    free(buf);
    return ret;
  }
  *p_str = buf;
  return ret;
}

int asprintf(char **__restrict p_str, const char *__restrict format, ...) {
  va_list va;
  va_start(va, format);
  const int ret = vasprintf(p_str, format, va);
  va_end(va);
  return ret;
}

__attribute__((__always_inline__))
int vfprintf(FILE* __restrict stream, const char* __restrict format, va_list vlist)
{
  return npf_vpprintf(npf_fputc_std, (void*)stream, format, vlist);
}

int fprintf(FILE* __restrict stream, const char* __restrict format, ...)
{
  va_list va;
  va_start(va, format);
  const int ret = vfprintf(stream, format, va);
  va_end(va);
  return ret;
}

__attribute__((__always_inline__))
int vprintf(const char *__restrict format, va_list vlist)
{
  return npf_vpprintf(npf_putc_std, NULL, format, vlist);
}

int printf(char const *__restrict format, ...) {
  va_list va;
  va_start(va, format);
  int const rv = vprintf(format, va);
  va_end(va);
  return rv;
}
