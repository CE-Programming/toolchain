#include <fenv.h>

const fenv_t __fe_dfl_env = FE_TONEAREST;
fenv_t __fe_cur_env = __fe_dfl_env;

#undef feclearexcept
#undef fegetexceptflag
#undef feraiseexcept
#undef fesetexceptflag
#undef fetestexcept
#undef fegetround
#undef fesetround
#undef fegetenv
#undef feholdexcept
#undef fesetenv
#undef feupdateenv

int feclearexcept(int __excepts) {
    return __feclearexcept(__excepts);
}

int fegetexceptflag(fexcept_t *__flagp, int __excepts) {
    return __fegetexceptflag(__flagp, __excepts);
}

int feraiseexcept(int __excepts) {
    return __feraiseexcept(__excepts);
}

int fesetexceptflag(const fexcept_t *__flagp, int __excepts) {
    return __fesetexceptflag(__flagp, __excepts);
}

int fetestexcept(int __excepts) {
    return __fetestexcept(__excepts);
}

int fegetround(void) {
    return __fegetround();
}

int fesetround(int __rounding_mode) {
    return __fesetround(__rounding_mode);
}

int fegetenv(fenv_t *__envp) {
    return __fegetenv(__envp);
}

int feholdexcept(fenv_t *__envp) {
    return __feholdexcept(__envp);
}

int fesetenv(const fenv_t *__envp) {
    return __fesetenv(__envp);
}

int feupdateenv(const fenv_t *__envp) {
    return __feupdateenv(__envp);
}
