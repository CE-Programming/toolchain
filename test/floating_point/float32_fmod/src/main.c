#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#define C(expr) if (!(expr)) { return __LINE__; }

float frem_libcall(float, float);

size_t run_test(void) {
    float f32_pos_pi = (float)M_PI;
    float f32_neg_pi = (float)-M_PI;
    float f32_pos_one = 1.0f;
    float f32_neg_one = -1.0f;

    float trunc_part;

    /* fmodf test */
    C((fmodf(f32_pos_pi, f32_pos_one) == modff(f32_pos_pi, &trunc_part)));
    C((trunc_part == 3.0f));
    C((fmodf(f32_neg_pi, f32_pos_one) == modff(f32_neg_pi, &trunc_part)));
    C((trunc_part == -3.0f));
    C((fmodf(f32_pos_pi, f32_neg_one) == modff(f32_pos_pi, &trunc_part)));
    C((trunc_part == 3.0f));
    C((fmodf(f32_neg_pi, f32_neg_one) == modff(f32_neg_pi, &trunc_part)));
    C((trunc_part == -3.0f));

    /* frem test */
    C((frem_libcall(f32_pos_pi, f32_pos_one) == modff(f32_pos_pi, &trunc_part)));
    C((trunc_part == 3.0f));
    C((frem_libcall(f32_neg_pi, f32_pos_one) == modff(f32_neg_pi, &trunc_part)));
    C((trunc_part == -3.0f));
    C((frem_libcall(f32_pos_pi, f32_neg_one) == modff(f32_pos_pi, &trunc_part)));
    C((trunc_part == 3.0f));
    C((frem_libcall(f32_neg_pi, f32_neg_one) == modff(f32_neg_pi, &trunc_part)));
    C((trunc_part == -3.0f));

    /* passed all */
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
    size_t fail_index = run_test();
    if (fail_index == SIZE_MAX) {
        puts("All tests passed");
    } else {
        char buf[sizeof("Failed test: 16777215")];
        boot_sprintf(buf, "Failed test: %u", fail_index);
        puts(buf);
    }

    while (!os_GetCSC());

    return 0;
}
