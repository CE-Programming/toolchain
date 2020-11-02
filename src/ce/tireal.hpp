#ifndef CE_TIREAL_HPP
#define CE_TIREAL_HPP

#include "limits.hpp"

#include <tice.h>

#include <stdint.h>
#include <stdlib.h>

namespace ti
{

class real
{
    static constexpr uint8_t exponent_bias = 0x80;

public:
    enum sign : int8_t
    {
        pos =  0x00,
        neg = -0x80,
    };

    // ======== cmath _USE_MATH_DEFINES ========

    static constexpr const real& e() noexcept;
    static constexpr const real& log2e() noexcept;
    static constexpr const real& log10e() noexcept;
    static constexpr const real& ln2() noexcept;
    static constexpr const real& ln10() noexcept;
    static constexpr const real& pi() noexcept;
    static constexpr const real& pi_2() noexcept;
    static constexpr const real& pi_4() noexcept;
    static constexpr const real& _1_pi() noexcept;
    static constexpr const real& _2_pi() noexcept;
    static constexpr const real& _2_sqrtpi() noexcept;
    static constexpr const real& sqrt2() noexcept;
    static constexpr const real& sqrt1_2() noexcept;

    // ======== constructors ========

    template <typename... Args>
    constexpr real(int8_t sign, int8_t exponent, Args... mantissa) noexcept
        : value{sign, static_cast<int8_t>(exponent + exponent_bias), { static_cast<uint8_t>(mantissa)... }} {}

    constexpr real(int8_t sign, const real &r)
        : value{sign, r.value.exp, { r.value.mant[0],
                                     r.value.mant[1],
                                     r.value.mant[2],
                                     r.value.mant[3],
                                     r.value.mant[4],
                                     r.value.mant[5],
                                     r.value.mant[6] }} {}

    constexpr real() noexcept
        : real(pos, 0) {}

    constexpr real(const real_t& r) noexcept
        : value(r) {}

    explicit real(const char* s) noexcept
        : value(os_StrToReal(s, nullptr)) {}

    constexpr real(bool value) noexcept;
    real(int8_t value) noexcept : real(static_cast<int24_t>(value)) {}
    real(uint8_t value) noexcept : real(static_cast<int24_t>(value)) {}
    real(int16_t value) noexcept : real(static_cast<int24_t>(value)) {}
    real(uint16_t value) noexcept : real(static_cast<int24_t>(value)) {}
    real(int24_t value) noexcept : value(os_Int24ToReal(value)) {}
    real(uint24_t value) noexcept;
    real(int32_t value) noexcept;
//    real(uint32_t value) {};
//    real(uint64_t value) {};
//    real(int64_t value) {};
    real(float value) noexcept : value(os_FloatToReal(value)) {} // TODO figure out what NaN does
    real(double value) noexcept : real(static_cast<float>(value)) {}
    real(long double value) noexcept : real(static_cast<float>(value)) {}

    // ======== converting operators ========

    constexpr operator real_t() const noexcept { return value; }

    constexpr explicit operator bool() const noexcept { return value.mant[0] != 0; }
    explicit operator int8_t() const noexcept { return static_cast<int24_t>(*this); }
    explicit operator uint8_t() const noexcept { return static_cast<int24_t>(*this); }
    explicit operator int16_t() const noexcept { return static_cast<int24_t>(*this); }
    explicit operator uint16_t() const noexcept { return static_cast<int24_t>(*this); }
    explicit operator int24_t() const noexcept { return os_RealToInt24(&value); }
//    explicit operator uint24_t() const noexcept {}
//    explicit operator int32_t() const noexcept {}
//    explicit operator uint32_t() const noexcept {}
//    explicit operator int64_t() const noexcept {}
//    explicit operator uint64_t() const noexcept {}
    explicit operator float() const noexcept { return os_RealToFloat(&value); }
    explicit operator double() const noexcept { return static_cast<float>(*this); }
    explicit operator long double() const noexcept { return static_cast<float>(*this); }

    // ======== common operators ========

    real& operator+=(const real& rhs) { value = os_RealAdd(&value, &rhs.value); return *this; }
    real& operator-=(const real& rhs) { value = os_RealSub(&value, &rhs.value); return *this; }
    real& operator*=(const real& rhs) { value = os_RealMul(&value, &rhs.value); return *this; }
    real& operator/=(const real& rhs) { value = os_RealDiv(&value, &rhs.value); return *this; }
    real& operator%=(const real& rhs) { value = os_RealMod(&value, &rhs.value); return *this; }

    real& operator++();
    real& operator--();
    real operator++(int) { real result(*this); ++*this; return result; }
    real operator--(int) { real result(*this); --*this; return result; }

    constexpr real operator+() const noexcept { return *this; }
    constexpr real operator-() const noexcept { return real(sign(value.sign ^ neg), *this); }

    real operator+(const real& rhs) const { real result(*this); return result += rhs; }
    real operator-(const real& rhs) const { real result(*this); return result -= rhs; }
    real operator*(const real& rhs) const { real result(*this); return result *= rhs; }
    real operator/(const real& rhs) const { real result(*this); return result /= rhs; }
    real operator%(const real& rhs) const { real result(*this); return result %= rhs; }

    bool operator==(const real& rhs) const noexcept { return os_RealCompare(&value, &rhs.value) == 0; }
    bool operator!=(const real& rhs) const noexcept { return !(*this == rhs); }
    bool operator< (const real& rhs) const noexcept { return os_RealCompare(&value, &rhs.value) < 0; }
    bool operator> (const real& rhs) const noexcept { return os_RealCompare(&value, &rhs.value) > 0; }
    bool operator<=(const real& rhs) const noexcept { return !(*this > rhs); }
    bool operator>=(const real& rhs) const noexcept { return !(*this < rhs); }

#define TIRealTrivialWrap(name, func) real name() const { return os_Real##func(&value); }

    // ======== cmath ========

    constexpr real abs() const noexcept { return real(pos, *this); }
    constexpr real fabs() const noexcept { return abs(); }
    real fmod(const real& y) const { return *this - ((*this)/y.value).trunc() * y.value; }
    real remainder(const real& y) const { return *this - ((*this)/y.value).round() * y.value; }

    real remquo(const real& y, int* quo) const { const auto rem = (*this).remainder(y); *quo = (int24_t)((*this)/y).round(); return rem; }
    real fma(const real& y, const real& z) const { return (*this) * y + z; }
    real fmax(const real& y) const { return os_RealMax(&value, &y.value); }
    real fmin(const real& y) const { return os_RealMin(&value, &y.value); }
    real fdim(const real& y) const { return (*this - y).abs(); }
    static constexpr const real& nan(const char* arg) noexcept;

    TIRealTrivialWrap(exp, Exp)
    real exp2() const { return real(2).pow(*this); }
    real expm1() const { return --exp(); }
    TIRealTrivialWrap(log, Log)
    real log10() const { return (*this).log() / ln10(); }
    real log2() const { return (*this).log() / ln2(); }
    real log1p() const { return (*this + 1).log(); }

    real pow(const real& exp) const { return os_RealPow(&value, &exp.value); }
    TIRealTrivialWrap(sqrt, Sqrt)
    real cbrt() const { const auto third = real(1./3.); return os_RealPow(&value, &third.value); }
    real hypot(const real& y) const { return ((*this * *this) + (y * y)).sqrt(); }
    real hypot(const real& y, const real& z) const { return ((*this * *this) + (y * y) + (z * z)).sqrt(); }

    TIRealTrivialWrap(sin, SinRad)
    TIRealTrivialWrap(cos, CosRad)
    TIRealTrivialWrap(tan, TanRad)
    TIRealTrivialWrap(asin, AsinRad)
    TIRealTrivialWrap(acos, AcosRad)
    TIRealTrivialWrap(atan, AtanRad)

    // hyperbolic

    // erf and gamma wtf

    real ceil() const noexcept { return -(-*this).floor(); }
    TIRealTrivialWrap(floor, Floor)
    TIRealTrivialWrap(trunc, Int)
    TIRealTrivialWrap(round, RoundInt)
//    long lround() const noexcept { return round(); }
//    long long llround() const noexcept { return round(); }
//    real nearbyint() const noexcept {}
//    real rint() const noexcept {}
//    long lrint() const noexcept {}
//    long long llrint() const noexcept {}

//    real frexp(int* exp) const {}
//    real ldexp(int exp) const {}
    real modf(real* iptr) const noexcept { *iptr = trunc(); return os_RealFrac(&value); }
//    real scalbn(int exp) const {}
//    real scalbln(long exp) const {}
    constexpr int ilogb() const noexcept { return static_cast<int>(static_cast<uint8_t>(value.exp)) - exponent_bias; }
    static constexpr int ilogb0 = 0;
    static constexpr int ilogbnan = 0;
    real logb() const noexcept { return ilogb(); }
//    real nextafter(const real& to) const {}
//    real nexttoward(long double to) const {}
    constexpr real copysign(const real& y) const { return real(y.value.sign, *this); }

//    constexpr int fpclassify() const noexcept {}
    constexpr bool isfinite() const noexcept { return true; }
    constexpr bool isinf() const noexcept { return false; }
    constexpr bool isnan() const noexcept { return false; }
    constexpr bool isnormal() const noexcept { return true; }
    constexpr bool signbit() const noexcept { return value.sign < 0; }
    bool isgreater(const real& y) const noexcept { return *this > y; }
    bool isgreaterequal(const real& y) const noexcept { return *this >= y; }
    bool isless(const real& y) const noexcept { return *this < y; }
    bool islessequal(const real& y) const noexcept { return *this <= y; }
    bool islessgreater(const real& y) const noexcept { return *this != y; }
    constexpr bool isunordered(const real&) const noexcept { return false; }

    // special

    // ======== numeric ========

    real gcd(const real& n) const { return os_RealGcd(&value, &n.value); }
    real lcm(const real& n) const { return os_RealLcm(&value, &n.value); }

    // ======== custom ========

    TIRealTrivialWrap(inv, Inv)
    TIRealTrivialWrap(frac, Frac)
    TIRealTrivialWrap(degToRad, DegToRad)
    TIRealTrivialWrap(radToDeg, RadToDeg)

#undef TIRealTrivialWrap

    real nCr(const real& x) const { return os_RealNcr(&value, &x.value); }
    real nPr(const real& x) const { return os_RealNpr(&value, &x.value); }

    real round(char digits) const { return os_RealRound(&value, digits); }

    int toCString(char* destBuf, int8_t maxLength = 0, uint8_t mode = 0, int8_t digits = -1) const
    {
        return os_RealToStr(destBuf, &value, maxLength, mode, digits);
    }

private:
    real_t value{};

    static void static_assertions();
};

namespace __detail
{

template <uintmax_t base, uintmax_t n>
struct log
{
    static constexpr uintmax_t value = log<base, n / base>::value + (n >= base);
};
template <uintmax_t base>
struct log<base, 0>
{
    static constexpr uintmax_t value = 0;
};
static_assert(log<10, 1ll << 24>::value == 7, "log_10(1 << 24) == 7");
static_assert(log<10, 1000000000>::value == 9, "log_10(1000000000) == 9");
static_assert(log<10, 999999999>::value == 8, "log_10(999999999) == 8");
static_assert(log<10, 100000000>::value == 8, "log_10(100000000) == 8");
static_assert(log<10, 99999999>::value == 7, "log_10(99999999) == 7");
static_assert(log<10, 10000000>::value == 7, "log_10(10000000) == 7");
static_assert(log<10, 9999999>::value == 6, "log_10(9999999) == 6");
static_assert(log<10, 1000000>::value == 6, "log_10(1000000) == 6");
static_assert(log<10, 999999>::value == 5, "log_10(999999) == 5");
static_assert(log<10, 100000>::value == 5, "log_10(100000) == 5");
static_assert(log<10, 99999>::value == 4, "log_10(99999) == 4");
static_assert(log<10, 10000>::value == 4, "log_10(10000) == 4");
static_assert(log<10, 9999>::value == 3, "log_10(9999) == 3");
static_assert(log<10, 1000>::value == 3, "log_10(1000) == 3");
static_assert(log<10, 999>::value == 2, "log_10(999) == 2");
static_assert(log<10, 100>::value == 2, "log_10(100) == 2");
static_assert(log<10, 99>::value == 1, "log_10(99) == 1");
static_assert(log<10, 10>::value == 1, "log_10(10) == 1");
static_assert(log<10, 9>::value == 0, "log_10(9) == 0");
static_assert(log<10, 1>::value == 0, "log_10(1) == 0");
static_assert(log<10, 0>::value == 0, "log_10(0) == 0");

template <intmax_t base, intmax_t exponent>
struct pow
{
    static constexpr intmax_t value = pow<intmax_t(uintmax_t(base) * uintmax_t(base)),
                                exponent < 0 ? 0 : (exponent >> 1)>::value * (exponent < 0 ? base == 1 : exponent & 1 ? base : 1);
};
template <intmax_t base>
struct pow<base, 0>
{
    static constexpr intmax_t value = 1;
};
static_assert(pow<1, 0>::value == 1, "1^0 == 1");
static_assert(pow<1, -1>::value == 1, "1^-1 == 1");
static_assert(pow<2, -1>::value == 0, "2^-1 == 0");
static_assert(pow<3, -1>::value == 0, "3^-1 == 0");
static_assert(pow<1, -2>::value == 1, "1^-2 == 1");
static_assert(pow<2, -2>::value == 0, "2^-2 == 0");
static_assert(pow<3, -2>::value == 0, "3^-2 == 0");
static_assert(pow<2, 2>::value == 4, "2^2 == 4");
static_assert(pow<5, 5>::value == 3125, "5^5 == 3125");
static_assert(pow<10, 10>::value == 10000000000, "10^10 == 10000000000");

template <intmax_t n, intmax_t exponent, uintmax_t base = 10>
struct digit
{
    static constexpr uintmax_t value = pow<base, exponent>::value == 0 ? 0 : (n < 0 ? -n : n) / pow<base, exponent>::value % base;
};

template <intmax_t n, intmax_t exponent, uintmax_t base = 10, uintmax_t separation = 16>
struct digit_pair
{
    static constexpr uintmax_t value = digit<n, exponent, base>::value * separation + digit<n, exponent - 1, base>::value;
};
static_assert(digit_pair<-12345, 6>::value == 0x00, "digit_pair<-12345, 6> == 0x00");
static_assert(digit_pair<-12345, 5>::value == 0x01, "digit_pair<-12345, 5> == 0x01");
static_assert(digit_pair<-12345, 4>::value == 0x12, "digit_pair<-12345, 4> == 0x12");
static_assert(digit_pair<-12345, 3>::value == 0x23, "digit_pair<-12345, 3> == 0x23");
static_assert(digit_pair<-12345, 2>::value == 0x34, "digit_pair<-12345, 2> == 0x34");
static_assert(digit_pair<-12345, 1>::value == 0x45, "digit_pair<-12345, 1> == 0x45");
static_assert(digit_pair<-12345, 0>::value == 0x50, "digit_pair<-12345, 0> == 0x50");
static_assert(digit_pair<-12345, -1>::value == 0x00, "digit_pair<-12345, -1> == 0x00");

template <char... literal> struct parser;
template <> struct parser<>
{
    static constexpr intmax_t leading = 1, mantissa = 0, offset = -1, exponent = 0;
};
template <char... literal>
struct parser<'0', literal...> : parser<literal...>
{
    static constexpr intmax_t leading = parser<literal...>::leading + 1;
};
template <char digit, char... literal>
struct parser<digit, literal...> : parser<literal...>
{
    using rest = parser<literal...>;
    static constexpr intmax_t leading = parser<>::leading,
            mantissa = (digit - '0') * pow<10, 14>::value + rest::mantissa / pow<10, rest::leading>::value,
            offset = rest::offset + rest::leading;
};
template <char... literal> struct parser<'.', literal...> : parser<literal...>
{
    static constexpr intmax_t offset = parser<>::offset;
};
template <char... literal> struct parser<'e', literal...> : parser<>
{
    using rest = parser<literal...>;
    static constexpr intmax_t exponent = rest::mantissa / pow<10, 14 - rest::offset>::value;
};
template <char... literal> struct parser<'E', literal...> : parser<'e', literal...> {};
template <char... literal> struct parser<'+', literal...> : parser<literal...> {};
template <char... literal> struct parser<'-', literal...> : parser<literal...>
{
    static constexpr intmax_t mantissa = -parser<literal...>::mantissa;
};

template <real::sign sign, typename parser, intmax_t... positions> struct parse
{
    static constexpr intmax_t exponent = parser::mantissa ? parser::exponent + parser::offset : 0;
    static constexpr real value{sign, exponent < -99 ? 0 : exponent > 99 ? 99 : exponent,
                                digit_pair<(exponent < -99 ? 0 : exponent > 99 ? pow<10, 14>::value - 10 : parser::mantissa + 5),
                                            positions>::value...};
};
template <real::sign sign, typename parser, intmax_t... positions> constexpr real parse<sign, parser, positions...>::value;

template <char... literal>
constexpr const real& operator""_nr() noexcept
{
    return __detail::parse<real::neg, __detail::parser<literal...>, 14, 12, 10, 8, 6, 4, 2>::value;
}

template <intmax_t n, intmax_t exponent, unsigned... positions>
struct maker
{
    static constexpr uintmax_t abs = n < 0 ? -n : n;
    static constexpr unsigned log10 = __detail::log<10, abs>::value;
    static constexpr uintmax_t ulp = __detail::pow<10, log10 - 13>::value;
    static constexpr uintmax_t ulpNonzero = ulp == 0 ? 1 : ulp;
    static constexpr uintmax_t rounded = (abs + ulp / 2) / ulpNonzero * ulpNonzero;
    static constexpr int normalizedExponent = log10 + exponent;
    static_assert(-99 <= normalizedExponent && normalizedExponent <= 99, "Overflow");
    static constexpr real value{n < 0 ? real::neg : real::pos,
                                normalizedExponent,
                                digit_pair<rounded, log10 - positions>::value...};
};
template <intmax_t n, intmax_t exponent, unsigned... positions> constexpr real maker<n, exponent, positions...>::value;

} // namespace __detail

namespace literals
{
inline namespace real_literals
{

template <char... literal>
constexpr const real& operator""_r() noexcept
{
    return __detail::parse<real::pos, __detail::parser<literal...>, 14, 12, 10, 8, 6, 4, 2>::value;
}

} // inline namespace real_literals
} // namespace literals

template <intmax_t n, intmax_t exponent = 0>
constexpr const real& make_real() noexcept
{
    return __detail::maker<n, exponent, 0, 2, 4, 6, 8, 10, 12>::value;
}

constexpr const real& real::e()         noexcept { using namespace literals; return 2.718281828459_r;   }
constexpr const real& real::log2e()     noexcept { using namespace literals; return 1.442695040889_r;   }
constexpr const real& real::log10e()    noexcept { using namespace literals; return 0.43429448190325_r; }
constexpr const real& real::ln2()       noexcept { using namespace literals; return 0.69314718055995_r; }
constexpr const real& real::ln10()      noexcept { using namespace literals; return 2.302585092994_r;   }
constexpr const real& real::pi()        noexcept { using namespace literals; return 3.1415926535898_r;  }
constexpr const real& real::pi_2()      noexcept { using namespace literals; return 1.5707963267949_r;  }
constexpr const real& real::pi_4()      noexcept { using namespace literals; return 0.78539816339745_r; }
constexpr const real& real::_1_pi()     noexcept { using namespace literals; return 0.31830988618379_r; }
constexpr const real& real::_2_pi()     noexcept { using namespace literals; return 0.63661977236758_r; }
constexpr const real& real::_2_sqrtpi() noexcept { using namespace literals; return 1.1283791670955_r;  }
constexpr const real& real::sqrt2()     noexcept { using namespace literals; return 1.4142135623731_r;  }
constexpr const real& real::sqrt1_2()   noexcept { using namespace literals; return 0.70710678118655_r; }

constexpr real::real(bool value) noexcept
    : real(value ? make_real<1>() : make_real<0>()) {}

inline real::real(uint24_t value) noexcept
    : value(os_Int24ToReal(value))
{
    if (static_cast<int24_t>(value) < 0)
    {
        *this += make_real<1ll << 24>();
    }
}

inline real::real(int32_t value) noexcept
{
    ldiv_t ldivResult = ldiv(value, 1000);
    *this = ldivResult.quot;
    this->value.exp += 3;
    *this += ldivResult.rem;
}

inline real& real::operator++()
{
    using namespace literals;
    return *this += 1_r;
}
inline real& real::operator--()
{
    using namespace literals;
    return *this -= 1_r;
}

constexpr const real& real::nan(const char* /*arg*/) noexcept
{
    using namespace literals;
    return 0_r;
}

inline void real::static_assertions()
{
    using namespace literals;

    static_assert((-0_r).value.sign == neg &&
                  static_cast<uint8_t>((-0_r).value.exp) == exponent_bias &&
                  (-0_r).value.mant[0] == 0x00, "-0");
    static_assert((1_r).value.sign == pos &&
                  static_cast<uint8_t>((1_r).value.exp) == exponent_bias &&
                  (1_r).value.mant[0] == 0x10, "1");
    static_assert((10_r).value.sign == pos &&
                  static_cast<uint8_t>((10_r).value.exp) == exponent_bias + 1 &&
                  (10_r).value.mant[0] == 0x10, "10");
    static_assert((1e10_r).value.sign == pos &&
                  static_cast<uint8_t>((1e10_r).value.exp) == exponent_bias + 10 &&
                  (1e10_r).value.mant[0] == 0x10, "1e10");
    static_assert((12345_r).value.sign == pos &&
                  static_cast<uint8_t>((1e42_r).value.exp) == exponent_bias + 42 &&
                  (1e42_r).value.mant[0] == 0x10, "1e42");
    static_assert((12345_r).value.sign == pos &&
                  static_cast<uint8_t>((1e-42_r).value.exp) == exponent_bias - 42 &&
                  (1e-42_r).value.mant[0] == 0x10, "1e-42");
    static_assert((12345_r).value.sign == pos &&
                  static_cast<uint8_t>((12345_r).value.exp) == exponent_bias + 4 &&
                  (12345_r).value.mant[0] == 0x12 &&
                  (12345_r).value.mant[1] == 0x34 &&
                  (12345_r).value.mant[2] == 0x50, "12345");
    static_assert((-123456789012345_r).value.sign == neg &&
                  static_cast<uint8_t>((-123456789012345_r).value.exp) == exponent_bias + 14 &&
                  (-123456789012345_r).value.mant[0] == 0x12 &&
                  (-123456789012345_r).value.mant[1] == 0x34 &&
                  (-123456789012345_r).value.mant[2] == 0x56 &&
                  (-123456789012345_r).value.mant[3] == 0x78 &&
                  (-123456789012345_r).value.mant[4] == 0x90 &&
                  (-123456789012345_r).value.mant[5] == 0x12 &&
                  (-123456789012345_r).value.mant[6] == 0x35, "-123456789012345");
    static_assert((-1234567890123449999e-4_r).value.sign == neg &&
                  static_cast<uint8_t>((-1234567890123449999e-4_r).value.exp) == exponent_bias + 14 &&
                  (-1234567890123449999e-4_r).value.mant[0] == 0x12 &&
                  (-1234567890123449999e-4_r).value.mant[1] == 0x34 &&
                  (-1234567890123449999e-4_r).value.mant[2] == 0x56 &&
                  (-1234567890123449999e-4_r).value.mant[3] == 0x78 &&
                  (-1234567890123449999e-4_r).value.mant[4] == 0x90 &&
                  (-1234567890123449999e-4_r).value.mant[5] == 0x12 &&
                  (-1234567890123449999e-4_r).value.mant[6] == 0x34, "-1.2345678901234e14");

    static_assert(make_real<-0>().value.sign == pos &&
                  static_cast<uint8_t>(make_real<-0>().value.exp) == exponent_bias &&
                  make_real<-0>().value.mant[0] == 0x00,
                  "make_real<-0>() == 0");
    static_assert(make_real<1>().value.sign == pos &&
                  static_cast<uint8_t>(make_real<1>().value.exp) == exponent_bias &&
                  make_real<1>().value.mant[0] == 0x10,
                  "make_real<1>() == 1");
    static_assert(make_real<1, 42>().value.sign == pos &&
                  static_cast<uint8_t>(make_real<1, 42>().value.exp) == exponent_bias + 42 &&
                  make_real<1, 42>().value.mant[0] == 0x10,
                  "make_real<1, 42>() == 1e42");
    static_assert(make_real<1, -42>().value.sign == pos &&
                  static_cast<uint8_t>(make_real<1, -42>().value.exp) == exponent_bias - 42 &&
                  make_real<1, -42>().value.mant[0] == 0x10,
                  "make_real<1, -42>() == 1e-42");
    static_assert(make_real<-12345>().value.sign == neg &&
                  static_cast<uint8_t>(make_real<-12345>().value.exp) == exponent_bias + 4 &&
                  make_real<-12345>().value.mant[0] == 0x12 &&
                  make_real<-12345>().value.mant[1] == 0x34 &&
                  make_real<-12345>().value.mant[2] == 0x50,
                  "make_real<-12345>() == -12345");
    static_assert(make_real<-123456789012345>().value.sign == neg &&
                  static_cast<uint8_t>(make_real<-123456789012345>().value.exp) == exponent_bias + 14 &&
                  make_real<-123456789012345>().value.mant[0] == 0x12 &&
                  make_real<-123456789012345>().value.mant[1] == 0x34 &&
                  make_real<-123456789012345>().value.mant[2] == 0x56 &&
                  make_real<-123456789012345>().value.mant[3] == 0x78 &&
                  make_real<-123456789012345>().value.mant[4] == 0x90 &&
                  make_real<-123456789012345>().value.mant[5] == 0x12 &&
                  make_real<-123456789012345>().value.mant[6] == 0x35,
                  "make_real<-123456789012345>() == -1.2345678901235e14");
    static_assert(make_real<-1234567890123449999, -4>().value.sign == neg &&
                  static_cast<uint8_t>(make_real<-1234567890123449999, -4>().value.exp) == exponent_bias + 14 &&
                  make_real<-1234567890123449999, -4>().value.mant[0] == 0x12 &&
                  make_real<-1234567890123449999, -4>().value.mant[1] == 0x34 &&
                  make_real<-1234567890123449999, -4>().value.mant[2] == 0x56 &&
                  make_real<-1234567890123449999, -4>().value.mant[3] == 0x78 &&
                  make_real<-1234567890123449999, -4>().value.mant[4] == 0x90 &&
                  make_real<-1234567890123449999, -4>().value.mant[5] == 0x12 &&
                  make_real<-1234567890123449999, -4>().value.mant[6] == 0x34,
                  "make_real<-1234567890123449999, -4>() == -1.2345678901234e14");
}

} // namespace ti

namespace std
{

template <>
class numeric_limits<ti::real>
{
public:
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = true;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr std::float_denorm_style has_denorm = std::float_denorm_style::denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr std::float_round_style round_style = std::float_round_style::round_to_nearest;
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;
    static constexpr int digits = 14;
    static constexpr int digits10 = 14;
    static constexpr int max_digits10 = 14;
    static constexpr int radix = 10;
    static constexpr int min_exponent = -98;
    static constexpr int min_exponent10 = -99;
    static constexpr int max_exponent = 100;
    static constexpr int max_exponent10 = 99;
    static constexpr bool traps = true; // TODO confirm
    static constexpr bool tinyness_before = false;

    static constexpr const ti::real& min()           noexcept { using namespace ti::literals; return 1e-99_r; }
    static constexpr const ti::real& max()           noexcept { using namespace ti::literals; return 9.9999999999999e99_r; }
    static constexpr const ti::real& lowest()        noexcept { using namespace ti::__detail; return 9.9999999999999e99_nr; }
    static constexpr const ti::real& epsilon()       noexcept { using namespace ti::literals; return 1e-13_r; }
    static constexpr const ti::real& round_error()   noexcept { using namespace ti::literals; return 0.5_r; } // TODO confirm, but this seems like a pain
    static constexpr const ti::real& infinity()      noexcept { using namespace ti::literals; return 0_r; }
    static constexpr const ti::real& quiet_NaN()     noexcept { using namespace ti::literals; return 0_r; }
    static constexpr const ti::real& signaling_NaN() noexcept { using namespace ti::literals; return 0_r; }
    static constexpr const ti::real& denorm_min()    noexcept { using namespace ti::literals; return 0_r; }
};

} // namespace std

#endif /* CE_TIREAL_HPP */
