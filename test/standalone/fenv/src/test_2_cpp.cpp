#include <fenv.h>

#include "func.h"

#ifdef fetestexcept
#error "<fenv.h> functions cannot be macros in C++"
#endif

int test_2_cpp(void) {
    fenv_t temp;

    C(fetestexcept(FE_ALL_EXCEPT) == 0);
    C(fegetenv(&temp) == 0);
    C(feraiseexcept(FE_UNDERFLOW) == 0);

    int (*testexcept)(int) = fetestexcept;
    C(testexcept(FE_UNDERFLOW) != 0);
    C(fesetenv(&temp) == 0);
    C(testexcept(FE_UNDERFLOW) == 0);
    C(::fetestexcept(FE_ALL_EXCEPT) == 0);

    return 0;
}
