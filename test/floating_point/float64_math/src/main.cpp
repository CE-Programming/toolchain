#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include <bit>
#include <cmath>
#include <numbers>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static int64_t calc_ULP(long double guess, long double truth) {
    if (std::signbit(guess) == std::signbit(truth)) {
        return std::bit_cast<int64_t>(guess) - std::bit_cast<int64_t>(truth);
    }
    return (
        std::bit_cast<int64_t>(std::fabs(guess)) + std::bit_cast<int64_t>(std::fabs(truth))
    ) * (std::signbit(guess) ? -1 : 1);
}

constexpr int Maximum_ULP = 512;
static int64_t fail_ulp = 0;

static bool test_result(long double guess, long double truth) {
    if (std::bit_cast<uint64_t>(guess) != std::bit_cast<uint64_t>(truth)) {
        int64_t ulp = calc_ULP(guess, truth);
        if (std::abs(ulp) > Maximum_ULP) {
            fail_ulp = ulp;
            return true;
        }
    }
    return false;
}

#define TEST(guess, truth) if (test_result(guess, truth)) { return __LINE__; }

static int run_test(void) {
    
    TEST(std::exp   (    6.3L),  544.5719101259290330593886677332L);
    TEST(std::exp   (   -4.2L),  0.014995576820477706211984360229L);
    TEST(std::log   ( 1.0e-6L), -13.81551055796427410410794872811L);
    TEST(std::log   ( 3.0e+8L),  19.51929303262047516353917687440L);
 
    TEST(std::expm1 (    0.2L),  0.221402758160169833921071994640L);
    TEST(std::expm1 (-1.0e-8L), -9.999999950000000166666666250e-9L);
    TEST(std::log1p (   -0.2L), -0.223143551314209755766295090310L);
    TEST(std::log1p ( 1.0e-8L),  9.999999950000000333333330833e-9L);
   
    TEST(std::sin   (    1.0L),  0.841470984807896506652502321630L);
    TEST(std::sin   (   -0.6L), -0.564642473395035357200945445659L);
    TEST(std::cos   (    1.5L),  0.070737201667702910088189851434L);
    TEST(std::cos   (   -2.7L), -0.904072142017061147982527281943L);
    TEST(std::tan   (    1.2L),  2.572151622126318935409994236033L);
    TEST(std::tan   (   -3.0L),  0.142546543074277805295635410534L);

    TEST(std::asin  (    0.8L),  0.927295218001612232428512462922L);
    TEST(std::asin  (   -0.2L), -0.201357920790330791455125552218L);
    TEST(std::acos  (   -0.9L),  2.690565841793530805917998747485L);
    TEST(std::acos  (    0.9L),  0.451026811796262432544644635794L);
    TEST(std::atan  (   12.0L),  1.487655094906455389320653376989L);
    TEST(std::atan  (   -1.1L), -0.832981266674431705417693561837L);

    TEST(std::sinh  (    5.0L),  74.20321057778875897700947199607L);
    TEST(std::sinh  (   -9.0L), -4051.541902082789960515223595898L);
    TEST(std::cosh  (    8.0L),  1490.479161252178088627715460421L);
    TEST(std::cosh  (   -2.0L),  3.762195691083631459562213477774L);
    TEST(std::tanh  (    0.8L),  0.664036770267848963684844656400L);
    TEST(std::tanh  (   -3.2L), -0.996682397839651156180968063061L);

    TEST(std::asinh (    2.5L),  1.647231146371095710624858610444L);
    TEST(std::asinh (   -9.6L), -2.957611980815783849435355905152L);
    TEST(std::acosh (    3.5L),  1.924847300238413789991035653698L);
    TEST(std::acosh (  1.001L),  0.044717633608309309571769903614L);
    TEST(std::atanh (    0.3L),  0.309519604203111715474067349061L);
    TEST(std::atanh (   -0.9L), -1.472219489583220230004513715944L);

    TEST(std::erfc  (   -1.3L),  1.934007944940652436603893327504L);
    TEST(std::erfc  (    3.1L),  0.000011648657367199596033706164L);
    TEST(std::erf   (   -2.2L), -0.998137153702018108556548243971L);
    TEST(std::erf   (    0.5L),  0.520499877813046537682746653892L);

    TEST(std::lgamma(   10.0L),  12.80182748008146961120771787457L);
    TEST(std::lgamma(   -1.4L),  0.978052353322177034295788021952L);
    TEST(std::tgamma(    7.7L),  2769.830362327313660274177737214L);
    TEST(std::tgamma(   -2.3L), -1.447107394255917263858607780549L);

    TEST(std::hypot(1.23L, 4.56L, 7.89L), 9.195575022803087326242198470012610630662L);

    /* passed all */
    return 0;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_test();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608\n")];
        boot_sprintf(buf, "Failed test L%d\n", failed_test);
        fputs(buf, stdout);
        #if 0
            /* debugging */
            printf("ULP: %lld\n", fail_ulp);
        #endif
    } else {
        fputs("All tests passed", stdout);
    }

    while (!os_GetCSC());

    return 0;
}
