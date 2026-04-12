#ifndef _FENV_H
#define _FENV_H

#include <cdefs.h>
#include <__fenv_def.h>

enum {
    FE_DIVBYZERO  = 1 << 6,
#define FE_DIVBYZERO  FE_DIVBYZERO
    FE_INEXACT    = 1 << 5,
#define FE_INEXACT    FE_INEXACT
    FE_INVALID    = 1 << 4,
#define FE_INVALID    FE_INVALID
    FE_OVERFLOW   = 1 << 3,
#define FE_OVERFLOW   FE_OVERFLOW
    FE_UNDERFLOW  = 1 << 2,
#define FE_UNDERFLOW  FE_UNDERFLOW
    FE_ALL_EXCEPT = FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW,
#define FE_ALL_EXCEPT FE_ALL_EXCEPT

    FE_TONEAREST  = 0,
#define FE_TONEAREST  FE_TONEAREST
    FE_TOWARDZERO = 1,
#define FE_TOWARDZERO FE_TOWARDZERO
    FE_DOWNWARD   = 2,
#define FE_DOWNWARD   FE_DOWNWARD
    FE_UPWARD     = 3,
#define FE_UPWARD     FE_UPWARD
};

typedef __fenv_t fenv_t;
typedef unsigned char fexcept_t;

extern const fenv_t __fe_dfl_env;
#define FE_DFL_ENV (&__fe_dfl_env)

//------------------------------------------------------------------------------
// functions
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
int __feclearexcept(int __excepts) {
    return (__fe_cur_env &= ~((__excepts) & FE_ALL_EXCEPT), 0);
}

static inline __attribute__((__always_inline__))
int __fegetexceptflag(fexcept_t *__flagp, int __excepts) {
    return (*(__flagp) = __fe_cur_env & (__excepts) & FE_ALL_EXCEPT, 0);
}

static inline __attribute__((__always_inline__))
int __feraiseexcept(int __excepts) {
    return (__fe_cur_env |= (__excepts) & FE_ALL_EXCEPT, 0);
}

static inline __attribute__((__always_inline__))
int __fesetexceptflag(const fexcept_t *__flagp, int __excepts) {
    return (__fe_cur_env = (__fe_cur_env & ~((__excepts) & FE_ALL_EXCEPT)) | (*(__flagp) & (__excepts) & FE_ALL_EXCEPT), 0);
}

static inline __attribute__((__always_inline__))
int __fetestexcept(int __excepts) {
    return (__fe_cur_env & (__excepts) & FE_ALL_EXCEPT);
}

static inline __attribute__((__always_inline__))
int __fegetround(void) {
    return (__fe_cur_env & 3);
}

static inline __attribute__((__always_inline__))
int __fesetround(int __rounding_mode) {
    return (__fe_cur_env = (__fe_cur_env & ~3) | ((__rounding_mode) & 3), 0);
}

static inline __attribute__((__always_inline__))
int __fegetenv(fenv_t *__envp) {
    return (*(__envp) = __fe_cur_env, 0);
}

static inline __attribute__((__always_inline__))
int __feholdexcept(fenv_t *__envp) {
    return (*(__envp) = __fe_cur_env, __fe_cur_env &= ~FE_ALL_EXCEPT, 0);
}

static inline __attribute__((__always_inline__))
int __fesetenv(const fenv_t *__envp) {
    return (__fe_cur_env = *(__envp), 0);
}

static inline __attribute__((__always_inline__))
int __feupdateenv(const fenv_t *__envp) {
    return (__fe_cur_env = (__fe_cur_env & FE_ALL_EXCEPT) | *(__envp), 0);
}

//------------------------------------------------------------------------------
// prototypes
//------------------------------------------------------------------------------

__BEGIN_DECLS

int feclearexcept(int __excepts) __NOEXCEPT;

int fegetexceptflag(fexcept_t *__flagp, int __excepts) __NOEXCEPT;

int feraiseexcept(int __excepts) __NOEXCEPT;

int fesetexceptflag(const fexcept_t *__flagp, int __excepts) __NOEXCEPT;

int fetestexcept(int __excepts) __NOEXCEPT_PURE;

int fegetround(void) __NOEXCEPT_PURE;

int fesetround(int __rounding_mode) __NOEXCEPT;

int fegetenv(fenv_t *__envp) __NOEXCEPT;

int feholdexcept(fenv_t *__envp) __NOEXCEPT;

int fesetenv(const fenv_t *__envp) __NOEXCEPT;

int feupdateenv(const fenv_t *__envp) __NOEXCEPT;

#ifdef __cplusplus

inline int feclearexcept(int __excepts) __NOEXCEPT {
    return __feclearexcept(__excepts);
}

inline int fegetexceptflag(fexcept_t *__flagp, int __excepts) __NOEXCEPT {
    return __fegetexceptflag(__flagp, __excepts);
}

inline int feraiseexcept(int __excepts) __NOEXCEPT {
    return __feraiseexcept(__excepts);
}

inline int fesetexceptflag(const fexcept_t *__flagp, int __excepts) __NOEXCEPT {
    return __fesetexceptflag(__flagp, __excepts);
}

inline int fetestexcept(int __excepts) __NOEXCEPT {
    return __fetestexcept(__excepts);
}

inline int fegetround(void) __NOEXCEPT {
    return __fegetround();
}

inline int fesetround(int __rounding_mode) __NOEXCEPT {
    return __fesetround(__rounding_mode);
}

inline int fegetenv(fenv_t *__envp) __NOEXCEPT {
    return __fegetenv(__envp);
}

inline int feholdexcept(fenv_t *__envp) __NOEXCEPT {
    return __feholdexcept(__envp);
}

inline int fesetenv(const fenv_t *__envp) __NOEXCEPT {
    return __fesetenv(__envp);
}

inline int feupdateenv(const fenv_t *__envp) __NOEXCEPT {
    return __feupdateenv(__envp);
}

#endif /* __cplusplus */

__END_DECLS

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

#ifndef __cplusplus

#define feclearexcept(excepts) __feclearexcept(excepts)

#define fegetexceptflag(flagp, excepts) __fegetexceptflag(flagp, excepts)

#define feraiseexcept(excepts) __feraiseexcept(excepts)

#define fesetexceptflag(flagp, excepts) __fesetexceptflag(flagp, excepts)

#define fetestexcept(excepts) __fetestexcept(excepts)

#define fegetround() __fegetround()

#define fesetround(rounding_mode) __fesetround(rounding_mode)

#define fegetenv(envp) __fegetenv(envp)

#define feholdexcept(envp) __feholdexcept(envp)

#define fesetenv(envp) __fesetenv(envp)

#define feupdateenv(envp) __feupdateenv(envp)

#endif /* __cplusplus */

#endif /* _FENV_H */
