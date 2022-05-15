#include <fenv.h>

const fenv_t __fe_dfl_env = FE_TONEAREST;
fenv_t __fe_cur_env = __fe_dfl_env;

#define _
#define DEF(name, params, args) int name _ params { return name args; }

DEF(feclearexcept, (int excepts), (excepts))
DEF(fegetexceptflag, (fexcept_t *flagp, int excepts), (flagp, excepts))
DEF(feraiseexcept, (int excepts), (excepts))
DEF(fesetexceptflag, (const fexcept_t *flagp, int excepts), (flagp, excepts))
DEF(fetestexcept, (int excepts), (excepts))

DEF(fegetround, (void), ())
DEF(fesetround, (int rounding_mode), (rounding_mode))

DEF(fegetenv, (fenv_t *envp), (envp))
DEF(feholdexcept, (fenv_t *envp), (envp))
DEF(fesetenv, (const fenv_t *envp), (envp))
DEF(feupdateenv, (const fenv_t *envp), (envp))
