#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <alloca.h>

#define C(expr) if (!(expr)) { return __LINE__; }

int run_tests(void) {
    const unsigned char src[7] = {
        0, 1, 2, 3, 4, 5, 6
    };
    const unsigned char pattern[7] = {
        0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6
    };
    unsigned char dst[7];

    // swab does nothing if count is 0 or negative

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[2], &dst[2], 0);
    C(memcmp(dst, pattern, sizeof(dst)) == 0);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[2], &dst[2], -1);
    C(memcmp(dst, pattern, sizeof(dst)) == 0);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[2], &dst[2], INT_MIN);
    C(memcmp(dst, pattern, sizeof(dst)) == 0);

    // test non-zero amounts

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[2], &dst[2], 1);
    C(dst[0] == 0xF0);
    C(dst[1] == 0xF1);
    // dst[2] is undefined
    C(dst[3] == 0xF3);
    C(dst[4] == 0xF4);
    C(dst[5] == 0xF5);
    C(dst[6] == 0xF6);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[2], &dst[2], 2);
    C(dst[0] == 0xF0);
    C(dst[1] == 0xF1);
    C(dst[2] == 3);
    C(dst[3] == 2);
    C(dst[4] == 0xF4);
    C(dst[5] == 0xF5);
    C(dst[6] == 0xF6);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[2], &dst[2], 3);
    C(dst[0] == 0xF0);
    C(dst[1] == 0xF1);
    C(dst[2] == 3);
    C(dst[3] == 2);
    // dst[4] is undefined
    C(dst[5] == 0xF5);
    C(dst[6] == 0xF6);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[1], &dst[1], 4);
    C(dst[0] == 0xF0);
    C(dst[1] == 2);
    C(dst[2] == 1);
    C(dst[3] == 4);
    C(dst[4] == 3);
    C(dst[5] == 0xF5);
    C(dst[6] == 0xF6);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[1], &dst[1], 4);
    C(dst[0] == 0xF0);
    C(dst[1] == 2);
    C(dst[2] == 1);
    C(dst[3] == 4);
    C(dst[4] == 3);
    C(dst[5] == 0xF5);
    C(dst[6] == 0xF6);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[2], &dst[2], 4);
    C(dst[0] == 0xF0);
    C(dst[1] == 0xF1);
    C(dst[2] == 3);
    C(dst[3] == 2);
    C(dst[4] == 5);
    C(dst[5] == 4);
    C(dst[6] == 0xF6);

    memcpy(dst, pattern, sizeof(dst));
    swab(&src[1], &dst[1], 5);
    C(dst[0] == 0xF0);
    C(dst[1] == 2);
    C(dst[2] == 1);
    C(dst[3] == 4);
    C(dst[4] == 3);
    // dst[5] is undefined
    C(dst[6] == 0xF6);

    /* large test */ {
        unsigned char * large_src = alloca(256);
        unsigned char * large_dst = alloca(256);

        // setup src
        for (int i = 0; i < 256; i++) {
            large_src[i] = (unsigned char)i;
        }

        // setup canary
        large_dst[255] = 42;
        swab(large_src, large_dst, 255);

        // large_dst[254] is undefined
        for (int i = 0; i < 254; i++) {
            if (i % 2 == 0) {
                C(large_src[i] == large_dst[i + 1]);
            } else {
                C(large_src[i] == large_dst[i - 1]);
            }
        }

        // test that the canary was not overwritten
        C(large_dst[255] == 42);
        swab(large_src, large_dst, 256);
        for (int i = 0; i < 256; i++) {
            if (i % 2 == 0) {
                C(large_src[i] == large_dst[i + 1]);
            } else {
                C(large_src[i] == large_dst[i - 1]);
            }
        }

        // swab is an involute function
        swab(large_dst, large_src, 256);
        for (int i = 0; i < 256; i++) {
            C(large_src[i] == (unsigned char)i);
        }
    }

    return 0;
}
