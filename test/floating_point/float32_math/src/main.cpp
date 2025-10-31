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
#include <complex>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static int32_t calc_ULP(float guess, float truth) {
    if (std::signbit(guess) == std::signbit(truth)) {
        return std::bit_cast<int32_t>(guess) - std::bit_cast<int32_t>(truth);
    }
    return (
        std::bit_cast<int32_t>(std::fabs(guess)) + std::bit_cast<int32_t>(std::fabs(truth))
    ) * (std::signbit(guess) ? -1 : 1);
}

constexpr int Maximum_ULP = 512;
static int32_t fail_ulp = 0;

static bool test_result(float guess, float truth) {
    if (std::bit_cast<uint32_t>(guess) != std::bit_cast<uint32_t>(truth)) {
        int32_t ulp = calc_ULP(guess, truth);
        if (std::abs(ulp) > Maximum_ULP) {
            fail_ulp = ulp;
            return true;
        }
    }
    return false;
}

#define TEST(guess, truth) if (test_result(guess, truth)) { return __LINE__; }

static int run_test(void) {

    TEST(std::exp   (    6.3f),  544.5719101259290330593886677332f);
    TEST(std::exp   (   -4.2f),  0.014995576820477706211984360229f);
    TEST(std::log   ( 1.0e-6f), -13.81551055796427410410794872811f);
    TEST(std::log   ( 3.0e+8f),  19.51929303262047516353917687440f);

    TEST(std::expm1 (    0.2f),  0.221402758160169833921071994640f);
    TEST(std::expm1 ( -0.001f), -9.995001666250083319446428323e-4f);
    TEST(std::log1p (   -0.2f), -0.223143551314209755766295090310f);
    TEST(std::log1p (  0.001f),  9.995003330835331668093989205e-4f);

    TEST(std::sin   (    1.0f),  0.841470984807896506652502321630f);
    TEST(std::sin   (   -0.6f), -0.564642473395035357200945445659f);
    TEST(std::cos   (    1.5f),  0.070737201667702910088189851434f);
    TEST(std::cos   (   -2.7f), -0.904072142017061147982527281943f);
    TEST(std::tan   (    1.2f),  2.572151622126318935409994236033f);
    TEST(std::tan   (   -3.0f),  0.142546543074277805295635410534f);

    TEST(std::asin  (    0.8f),  0.927295218001612232428512462922f);
    TEST(std::asin  (   -0.2f), -0.201357920790330791455125552218f);
    TEST(std::acos  (   -0.9f),  2.690565841793530805917998747485f);
    TEST(std::acos  (    0.9f),  0.451026811796262432544644635794f);
    TEST(std::atan  (   12.0f),  1.487655094906455389320653376989f);
    TEST(std::atan  (   -1.1f), -0.832981266674431705417693561837f);

    TEST(std::sinh  (    5.0f),  74.20321057778875897700947199607f);
    TEST(std::sinh  (   -9.0f), -4051.541902082789960515223595898f);
    TEST(std::cosh  (    8.0f),  1490.479161252178088627715460421f);
    TEST(std::cosh  (   -2.0f),  3.762195691083631459562213477774f);
    TEST(std::tanh  (    0.8f),  0.664036770267848963684844656400f);
    TEST(std::tanh  (   -3.2f), -0.996682397839651156180968063061f);

    TEST(std::asinh (    2.5f),  1.647231146371095710624858610444f);
    TEST(std::asinh (   -9.6f), -2.957611980815783849435355905152f);
    TEST(std::acosh (    3.5f),  1.924847300238413789991035653698f);
    TEST(std::acosh (  1.001f),  0.044717633608309309571769903614f);
    TEST(std::atanh (    0.3f),  0.309519604203111715474067349061f);
    TEST(std::atanh (   -0.9f), -1.472219489583220230004513715944f);

    TEST(std::erfc  (   -1.3f),  1.934007944940652436603893327504f);
    TEST(std::erfc  (    2.0f),  0.004677734981047265837930743633f);
    TEST(std::erf   (   -2.2f), -0.998137153702018108556548243971f);
    TEST(std::erf   (    0.5f),  0.520499877813046537682746653892f);

    TEST(std::lgamma(   10.0f),  12.80182748008146961120771787457f);
    TEST(std::lgamma(   -1.4f),  0.978052353322177034295788021952f);
    TEST(std::tgamma(    7.7f),  2769.830362327313660274177737214f);
    TEST(std::tgamma(   -2.3f), -1.447107394255917263858607780549f);

    TEST(std::hypot(1.23f, 4.56f, 7.89f), 9.195575022803087326242198470012610630662f);

    using namespace std::complex_literals;
    std::complex<double> z1 = 1.0 + 2i;
    std::complex<double> z2 = 3.0 - 4.0i;
    std::complex<double> z3 = std::conj(z1 * z2);
    if (!(std::real(z3) == 11.0 && std::imag(z3) == -2.0)) {
        return __LINE__;
    }

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
            printf("ULP: %ld\n", fail_ulp);
        #endif
    } else {
        fputs("All tests passed", stdout);
    }

    while (!os_GetCSC());

    return 0;
}
