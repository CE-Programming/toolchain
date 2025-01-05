#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef union reg24
{
    struct
    {
        uint8_t low;
        uint8_t high;
        uint8_t upper;
    };
    uint16_t pair;
    uint24_t full;
} reg24_t;

typedef union reg48
{
    struct
    {
        uint24_t low;
        uint24_t high;
    };
    uint48_t full;
    uint64_t z_ext;
    int64_t s_ext;
} reg48_t;

typedef struct regs
{
    reg24_t af;
    reg48_t dehl;
    reg48_t iybc;
} regs_t;

typedef void (*test_func_t)(regs_t *);

#define TESTFUNC(ROUTINE)                       \
void test_##ROUTINE(regs_t *regs)               \
{                                               \
    asm volatile("ld\thl,(iy + %[af])\n\t"      \
                 "push\tiy, hl\n\t"             \
                 "pop\taf\n\t"                  \
                 "ld\thl, (iy + %[hl])\n\t"     \
                 "ld\tde, (iy + %[de])\n\t"     \
                 "ld\tbc, (iy + %[bc])\n\t"     \
                 "ld\tiy, (iy + %[iy])\n\t"     \
                 "extern\t__" #ROUTINE "\n\t"   \
                 "call\t__" #ROUTINE "\n\t"     \
                 "ex\t(sp), iy\n\t"             \
                 "ld\t(iy + %[hl]), hl\n\t"     \
                 "ld\t(iy + %[de]), de\n\t"     \
                 "ld\t(iy + %[bc]), bc\n\t"     \
                 "push\taf\n\t"                 \
                 "pop\thl, de\n\t"              \
                 "ld\t(iy + %[af]), hl\n\t"     \
                 "ld\t(iy + %[iy]), de\n\t"     \
    :                                           \
    : "iyl" (regs),                             \
      [af] "J" (offsetof(regs_t, af.full)),     \
      [hl] "J" (offsetof(regs_t, dehl.low)),    \
      [de] "J" (offsetof(regs_t, dehl.high)),   \
      [bc] "J" (offsetof(regs_t, iybc.low)),    \
      [iy] "J" (offsetof(regs_t, iybc.high))    \
    : "cc", "a", "c", "e", "l");                \
}

TESTFUNC(i48add)
TESTFUNC(i48and)
TESTFUNC(i48bitrev)
TESTFUNC(i48bswap)
TESTFUNC(i48cmps)
TESTFUNC(i48cmpu)
TESTFUNC(i48cmpzero)
TESTFUNC(i48ctlz)
TESTFUNC(i48divs)
TESTFUNC(i48divu)
TESTFUNC(i48dvrmu)
TESTFUNC(i48mulu)
TESTFUNC(i48neg)
TESTFUNC(i48not)
TESTFUNC(i48or)
TESTFUNC(i48popcnt)
TESTFUNC(i48rems)
TESTFUNC(i48remu)
TESTFUNC(i48shl)
TESTFUNC(i48shrs)
TESTFUNC(i48shru)
TESTFUNC(i48sub)
TESTFUNC(i48xor)

void ref_i48add(regs_t *regs)
{
    regs->dehl.z_ext += regs->iybc.z_ext;
}

void ref_i48and(regs_t *regs)
{
    regs->dehl.z_ext &= regs->iybc.z_ext;
}

void ref_i48bitrev(regs_t *regs)
{
    regs->dehl.z_ext = __builtin_bitreverse64(regs->dehl.z_ext) >> 16;
}

void ref_i48bswap(regs_t *regs)
{
    regs->dehl.z_ext = __builtin_bswap64(regs->dehl.z_ext) >> 16;
}

void ref_i48cmps(regs_t *regs)
{
    int64_t result = regs->dehl.s_ext - regs->iybc.s_ext;
    regs->af.low = ((result < INT48_MIN || result > INT48_MAX) << 2) | ((result >> 47 & 1) << 7);
}

void ref_i48cmpu(regs_t *regs)
{
    regs->af.low = (regs->dehl.z_ext < regs->iybc.z_ext) | ((regs->dehl.z_ext == regs->iybc.z_ext) << 6);
}

void ref_i48cmpzero(regs_t *regs)
{
    regs->af.low = ((regs->dehl.s_ext < 0) << 7) | ((regs->dehl.s_ext == 0) << 6);
}

void ref_i48ctlz(regs_t *regs)
{
    regs->af.high = __builtin_clzll(regs->dehl.z_ext) - 16;
}

void ref_i48divs(regs_t *regs)
{
    regs->dehl.s_ext /= regs->iybc.s_ext;
}

void ref_i48divu(regs_t *regs)
{
    regs->dehl.z_ext /= regs->iybc.z_ext;
}

void ref_i48dvrmu(regs_t *regs)
{
    uint64_t quotient = regs->dehl.z_ext / (uint64_t)regs->iybc.z_ext;
    uint64_t remainder = regs->dehl.z_ext % (uint64_t)regs->iybc.z_ext;
    regs->dehl.z_ext = quotient;
    regs->iybc.z_ext = remainder;
}

void ref_i48mulu(regs_t *regs)
{
    regs->dehl.z_ext = (uint64_t)regs->dehl.z_ext * (uint64_t)regs->iybc.z_ext;
}

void ref_i48neg(regs_t *regs)
{
    regs->dehl.z_ext = -regs->dehl.z_ext;
}

void ref_i48not(regs_t *regs)
{
    regs->dehl.z_ext = ~regs->dehl.z_ext;
}

void ref_i48or(regs_t *regs)
{
    regs->dehl.z_ext |= regs->iybc.z_ext;
}

void ref_i48popcnt(regs_t *regs)
{
    regs->af.high = __builtin_popcountll(regs->dehl.z_ext);
}

void ref_i48rems(regs_t *regs)
{
    regs->dehl.s_ext %= regs->iybc.s_ext;
}

void ref_i48remu(regs_t *regs)
{
    regs->dehl.z_ext %= regs->iybc.z_ext;
}

void ref_i48shl(regs_t *regs)
{
    regs->dehl.z_ext <<= regs->iybc.low & 0xFF;
}

void ref_i48shrs(regs_t *regs)
{
    regs->dehl.s_ext >>= regs->iybc.low & 0xFF;
}

void ref_i48shru(regs_t *regs)
{
    regs->dehl.z_ext >>= regs->iybc.low & 0xFF;
}

void ref_i48sub(regs_t *regs)
{
    regs->dehl.z_ext -= regs->iybc.z_ext;
}

void ref_i48xor(regs_t *regs)
{
    regs->dehl.z_ext ^= regs->iybc.z_ext;
}

void gen_regs_unsigned(regs_t *regs) {
    memset(regs, 0, sizeof(regs_t));
    regs->af.full = random();
    regs->dehl.low = random();
    regs->dehl.high = random();
    regs->iybc.low = random();
    regs->iybc.high = random();
}

void gen_regs_signed(regs_t *regs) {
    gen_regs_unsigned(regs);
    regs->dehl.s_ext = (int48_t)regs->dehl.full;
    regs->iybc.s_ext = (int48_t)regs->iybc.full;
}

void gen_regs_unsigned_shift(regs_t *regs) {
    memset(regs, 0, sizeof(regs_t));
    regs->af.full = random();
    regs->dehl.low = random();
    regs->dehl.high = random();
    regs->iybc.low = (random() % 48) | random() << 8;
    regs->iybc.high = random();
}

void gen_regs_signed_shift(regs_t *regs) {
    gen_regs_unsigned_shift(regs);
    regs->dehl.s_ext = (int48_t)regs->dehl.full;
}

void gen_regs_unsigned_near(regs_t *regs) {
    gen_regs_unsigned(regs);
    regs->iybc.z_ext = (uint48_t)(regs->dehl.z_ext + (regs->iybc.z_ext % 3) - 1);
}

void gen_regs_signed_near(regs_t *regs) {
    gen_regs_unsigned_near(regs);
    regs->dehl.s_ext = (int48_t)regs->dehl.full;
    regs->iybc.s_ext = (int48_t)regs->iybc.full;
}

void gen_regs_signed_near_zero(regs_t *regs) {
    gen_regs_signed(regs);
    regs->dehl.s_ext %= 2;
}

void gen_regs_unsigned_near_zero(regs_t *regs) {
    gen_regs_signed_near_zero(regs);
    regs->dehl.z_ext = regs->dehl.full;
    regs->iybc.z_ext = regs->iybc.full;
}

void gen_regs_signed_near_int_max(regs_t *regs) {
    gen_regs_signed(regs);
    regs->dehl.s_ext = (int64_t)INT24_MAX + (regs->dehl.s_ext % 2);
}

void gen_regs_unsigned_leading_zeros(regs_t *regs) {
    gen_regs_unsigned(regs);
    regs->dehl.z_ext >>= regs->iybc.z_ext % 49;
}

void print_regs(regs_t *regs) {
    printf("A=%02X DE=%06X HL=%06X\n"
           "F=%02X IY=%06X BC=%06X\n",
        regs->af.high,
        regs->dehl.high,
        regs->dehl.low,
        regs->af.low,
        regs->iybc.high,
        regs->iybc.low);
}

bool verify(regs_t *regs, regs_t *test_regs, regs_t *ref_regs) {
    if (test_regs->af.pair == ref_regs->af.pair &&
        test_regs->dehl.low == ref_regs->dehl.low &&
        test_regs->dehl.high == ref_regs->dehl.high &&
        test_regs->iybc.low == ref_regs->iybc.low &&
        test_regs->iybc.high == ref_regs->iybc.high)
    {
        return true;
    }
    printf("Input:\n");
    print_regs(regs);
    printf("Output:\n");
    print_regs(test_regs);
    printf("Expected:\n");
    print_regs(ref_regs);
    return false;
}

bool do_test(test_func_t gen, test_func_t test, test_func_t ref, uint8_t flags)
{
    regs_t regs, test_regs, ref_regs;
    for (unsigned i = 0; i < 500; i++)
    {
        gen(&regs);
        test_regs = regs; test(&test_regs);
        ref_regs = regs; ref(&ref_regs);
        ref_regs.af.low = (ref_regs.af.low & flags) | (test_regs.af.low & ~flags);
        // Allow inverting both sign and overflow
        if (flags == 0x84 && (ref_regs.af.low ^ test_regs.af.low) == 0x84) {
            ref_regs.af.low = test_regs.af.low;
        }
        if (!verify(&regs, &test_regs, &ref_regs))
        {
            return false;
        }
    }
    return true;
}

#define TEST(GEN, ROUTINE, FLAGS)                                       \
    if (!do_test(gen_regs_##GEN, test_##ROUTINE, ref_##ROUTINE, FLAGS)) \
    {                                                                   \
        printf("Failed " #ROUTINE);                                     \
        break;                                                          \
    }

int main(void)
{
    os_ClrHome();

    do
    {
        TEST(unsigned, i48add, 0)
        TEST(unsigned, i48and, 0)
        TEST(unsigned, i48bitrev, 0)
        TEST(unsigned, i48bswap, 0)
        TEST(signed, i48cmps, 0x84)
        TEST(signed_near, i48cmps, 0x84)
        TEST(unsigned, i48cmpu, 0x41)
        TEST(unsigned_near, i48cmpu, 0x41)
        TEST(signed, i48cmpzero, 0xC0)
        TEST(signed_near_zero, i48cmpzero, 0xC0)
        TEST(signed_near_int_max, i48cmpzero, 0xC0)
        TEST(unsigned_leading_zeros, i48ctlz, 0)
        TEST(signed, i48divs, 0)
        TEST(unsigned, i48divu, 0)
        TEST(unsigned, i48dvrmu, 0)
        TEST(unsigned, i48mulu, 0)
        TEST(unsigned, i48neg, 0)
        TEST(unsigned_near_zero, i48neg, 0)
        TEST(unsigned, i48not, 0)
        TEST(unsigned, i48or, 0)
        TEST(unsigned, i48popcnt, 0)
        TEST(signed, i48rems, 0)
        TEST(unsigned, i48remu, 0)
        TEST(unsigned_shift, i48shl, 0)
        TEST(signed_shift, i48shrs, 0)
        TEST(unsigned_shift, i48shru, 0)
        TEST(unsigned, i48sub, 0)
        TEST(unsigned, i48xor, 0)

        printf("All tests passed");
    } while(false);

    while (!os_GetCSC());

    return 0;
}
