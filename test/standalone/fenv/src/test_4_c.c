#include <fenv.h>
#include <math.h>

#include "func.h"

int test_4_c(void) {
    int (*clearexcept)(int) = feclearexcept;
    int (*testexcept)(int) = fetestexcept;
    C(fegetround() == FE_DOWNWARD);
    C(feclearexcept(FE_ALL_EXCEPT) == 0);
    C(ilogbf(*(const float*)0xE40000) == FP_ILOGB0);
    C(fegetround() == FE_DOWNWARD);
    C(testexcept(FE_ALL_EXCEPT) != 0);
    C(clearexcept(FE_INVALID) == 0);
    C(fetestexcept(FE_ALL_EXCEPT) == 0);
    return 0;
}
