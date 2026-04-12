#include <cfenv>
#include <stdlib.h>

#include "func.h"

extern "C" fenv_t env_data;

#ifdef fetestexcept
#error "<cfenv> functions cannot be macros in C++"
#endif

extern "C" void on_exit_func(int, void*);

int test_5_cpp(void) {
    C(std::fetestexcept(FE_OVERFLOW) == 0);
    C(std::feraiseexcept(FE_OVERFLOW) == 0);
    int (*func)(const fenv_t*);
    func = feupdateenv;
    C(func(&env_data) == 0);
    func = ::feupdateenv;
    C(func(&env_data) == 0);
    func = std::feupdateenv;
    C(func(&env_data) == 0);

    C(feupdateenv(&env_data) == 0);

    C(::feupdateenv(&env_data) == 0);
    C(std::feupdateenv(&env_data) == 0);

    C(std::fetestexcept(FE_OVERFLOW) != 0);
    C(on_exit(on_exit_func, reinterpret_cast<void*>(fesetexceptflag)) == 0);
    {
        using namespace std;
        func = feupdateenv;
        C(func(&env_data) == 0);
        func = ::feupdateenv;
        C(func(&env_data) == 0);
        func = std::feupdateenv;
        C(func(&env_data) == 0);

        C(feupdateenv(&env_data) == 0);
        C(::feupdateenv(&env_data) == 0);
        C(std::feupdateenv(&env_data) == 0);
    }
    C(std::fegetround() == FE_DOWNWARD);
    return 0;
}
