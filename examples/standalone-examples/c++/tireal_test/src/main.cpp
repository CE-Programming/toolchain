#include <stdint.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/real>

using namespace ti::literals;

static char buf[20] = {};

static void printText(const char *text, uint8_t xpos, uint8_t ypos)
{
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}

static ti::real test()
{
    ti::real r1 = 1.0;
    r1 += ti::real(9.0).sqrt(); // same as (9.0_r).sqrt()
    ++r1;
    r1 -= 0.5;
    r1 /= 2;
    return r1.round(3);
}

static ti::real test2()
{
    return std::numeric_limits<ti::real>::min();
}

static ti::real test3()
{
    return (3.1415926535_r).sqrt();
}

int main(void)
{
    os_ClrHomeFull();

    test().toCString(buf); // default args: 0, 0, -1
    printText(buf, 0, 0); // 2.25

    test2().toCString(buf);
    printText(buf, 0, 1); // 1E-99

    test3().toCString(buf);
    printText(buf, 0, 2); // 1.772453851

    ti::real::sqrt2().toCString(buf);
    printText(buf, 0, 3); // 1.414213562

    (26_r).nPr(4_r).toCString(buf); // == 358800
    printText(buf, 0, 4);

    (44_r).nCr(6_r).toCString(buf); // == 7059052
    printText(buf, 0, 5);

    (9.6_r).fmod(3.5_r).toCString(buf); // == 2.6
    printText(buf, 0, 6);

    (9.6_r).remainder(3.5_r).toCString(buf); // == -0.9
    printText(buf, 0, 7);

    while (!os_GetCSC());
    return 0;
}
