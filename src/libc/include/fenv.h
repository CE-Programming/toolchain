#ifndef _FENV_P
#define _FENV_P
typedef unsigned char __fenv_t;
extern __fenv_t __fe_cur_env;
#endif

#ifdef _FENV_P_ONLY
#undef _FENV_P_ONLY
#else

#ifndef _FENV_H
#define _FENV_H

#ifdef __cplusplus
extern "C" {
#endif

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

int feclearexcept(int);
#define feclearexcept(excepts) (__fe_cur_env &= ~((excepts) & FE_ALL_EXCEPT), 0)

int fegetexceptflag(fexcept_t *, int);
#define fegetexceptflag(flagp, excepts) (*(flagp) = __fe_cur_env & (excepts) & FE_ALL_EXCEPT, 0)

int feraiseexcept(int);
#define feraiseexcept(excepts) (__fe_cur_env |= (excepts) & FE_ALL_EXCEPT, 0)

int fesetexceptflag(const fexcept_t *, int);
#define fesetexceptflag(flagp, excepts) (__fe_cur_env = (__fe_cur_env & ~((excepts) & FE_ALL_EXCEPT)) \
                                         | (*(flagp) & (excepts) & FE_ALL_EXCEPT), 0)

int fetestexcept(int);
#define fetestexcept(excepts) (__fe_cur_env & (excepts) & FE_ALL_EXCEPT)

int fegetround(void);
#define fegetround() (__fe_cur_env & 3)

int fesetround(int);
#define fesetround(rounding_mode) (__fe_cur_env = (__fe_cur_env & ~3) | ((rounding_mode) & 3), 0)

int fegetenv(fenv_t *);
#define fegetenv(envp) (*(envp) = __fe_cur_env, 0)

int feholdexcept(fenv_t *);
#define feholdexcept(envp) (*(envp) = __fe_cur_env, __fe_cur_env &= ~FE_ALL_EXCEPT, 0)

int fesetenv(const fenv_t *);
#define fesetenv(envp) (__fe_cur_env = *(envp), 0)

int feupdateenv(const fenv_t *);
#define feupdateenv(envp) (__fe_cur_env = (__fe_cur_env & FE_ALL_EXCEPT) | *(envp), 0)

#ifdef __cplusplus
}
#endif

#endif

#endif
