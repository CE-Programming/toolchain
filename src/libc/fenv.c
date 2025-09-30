#include <fenv.h>

const fenv_t __fe_dfl_env = FE_TONEAREST;
fenv_t __fe_cur_env = __fe_dfl_env;

extern inline int feclearexcept(int __excepts);

extern inline int fegetexceptflag(fexcept_t *__flagp, int __excepts);

extern inline int feraiseexcept(int __excepts);

extern inline int fesetexceptflag(const fexcept_t *__flagp, int __excepts);

extern inline int fetestexcept(int __excepts);

extern inline int fegetround(void);

extern inline int fesetround(int __rounding_mode);

extern inline int fegetenv(fenv_t *__envp);

extern inline int feholdexcept(fenv_t *__envp);

extern inline int fesetenv(const fenv_t *__envp);

extern inline int feupdateenv(const fenv_t *__envp);
