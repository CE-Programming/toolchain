#include <fenv.h>

#include "func.h"

fenv_t env_data;

int test_1_c(void) {
    C(fegetround() == FE_TONEAREST);
    C(fetestexcept(FE_ALL_EXCEPT) == 0);

    C(fesetround(FE_DOWNWARD) == 0);
    C(feraiseexcept(FE_DIVBYZERO) == 0);

    C(feholdexcept(&env_data) == 0);

    return 0;
}
