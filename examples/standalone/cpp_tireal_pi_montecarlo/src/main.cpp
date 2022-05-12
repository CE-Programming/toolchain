#include <stdint.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/real>
#include <sys/rtc.h>

using namespace ti::literals;

int main(void)
{
    /* Clear the screen */
    os_ClrHomeFull();

    /* Set the random seed based off the real time clock */
    srand(rtc_Time());

    unsigned i = 0;
    constexpr unsigned iMax = 10'000;
    unsigned count = 0; /* points in the unit circle's first quadrant */

    auto print = [&]()
    {
        const auto piApprox = ti::real(count) / i * 4;

        char buf[24] = "PI is about ";
        constexpr size_t bufOffset = 12;
        piApprox.toCString(buf + bufOffset);

        os_PutStrFull(buf);
        os_NewLine();
    };

    while (++i <= iMax)
    {
        const auto x = ti::real(rand()) / RAND_MAX;
        const auto y = ti::real(rand()) / RAND_MAX;
        const auto z = x*x + y*y;
        if (z <= 1)
        {
            count++;
        }

        if (os_GetCSC())
        {
            break;
        }

        if (i % 100 == 0)
        {
            print();
        }
    }

    print();

    os_PutStrFull("Press any key to quit");
    while (!os_GetCSC());

    return 0;
}
