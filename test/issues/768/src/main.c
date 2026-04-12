#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <compression.h>
#include <ti/getcsc.h>
#include <ti/screen.h>

#define CANARY_SIZE 4
#define DEST_SIZE 192
#define SENTINEL 0xCC
#define CANARY 0xA5

#define C(expr) do { if (!(expr)) { return __LINE__; } } while (0)

typedef void (*decompress_fn_t)(void *dst, const void *src);

typedef struct TestCase {
    const char *name;
    decompress_fn_t decompress;
    const uint8_t *compressed;
    const uint8_t *expected;
    size_t expected_size;
} TestCase;

typedef struct Stage {
    const char *title;
    size_t first_test;
    size_t test_count;
} Stage;

typedef struct Buffer {
    uint8_t before[CANARY_SIZE];
    uint8_t data[DEST_SIZE + CANARY_SIZE];
} Buffer;

static const uint8_t zx7_one_compressed[] = { 0xAB, 0x80, 0x00, 0x40 };
static const uint8_t zx7_two_compressed[] = { 0xAB, 0x40, 0xCD, 0x00, 0x20 };
static const uint8_t zx7_three_compressed[] = { 0xAB, 0x20, 0xCD, 0xEF, 0x00, 0x10 };
static const uint8_t zx7_zeros10_compressed[] = { 0x00, 0x88, 0x00, 0x80, 0x00, 0x40 };

static const uint8_t zx0_one_compressed[] = { 0xD5, 0xAB, 0x55, 0x60 };
static const uint8_t zx0_two_compressed[] = { 0x35, 0xAB, 0xCD, 0x55, 0x58 };
static const uint8_t zx0_three_compressed[] = { 0x75, 0xAB, 0xCD, 0xEF, 0x55, 0x58 };
static const uint8_t zx0_zeros10_compressed[] = { 0x81, 0x00, 0xD5, 0x55, 0x60 };
static const uint8_t zx7_far129_compressed[] = {
    0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x00, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x00, 0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x00, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x00, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x00, 0x29,
    0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x00, 0x31, 0x32, 0x33, 0x34,
    0x35, 0x36, 0x37, 0x38, 0x00, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x00, 0x49,
    0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x00, 0x51, 0x52, 0x53, 0x54,
    0x55, 0x56, 0x57, 0x58, 0x00, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x00, 0x69,
    0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x00, 0x71, 0x72, 0x73, 0x74,
    0x75, 0x76, 0x77, 0x78, 0x00, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x8F, 0x80, 0x08, 0x00, 0x04,
};
static const uint8_t zx0_far129_compressed[] = {
    0x00, 0x07, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21,
    0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,
    0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
    0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
    0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
    0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x75,
    0xFE, 0xD5, 0x55, 0x60,
};
static const uint8_t zx7_overlap160_compressed[] = { 0x41, 0x80, 0x9E, 0x00, 0x80, 0x00, 0x40 };
static const uint8_t zx0_overlap160_compressed[] = { 0x81, 0x41, 0x55, 0xD5, 0x55, 0x60 };

/* Generated from the bundled zx0/zx7 compressor sources used by convbin.
 * Empty input is intentionally excluded because the toolchain does not provide
 * a valid empty compressed stream for either format. */
static const uint8_t bytes_one[] = { 0xAB };
static const uint8_t bytes_two[] = { 0xAB, 0xCD };
static const uint8_t bytes_three[] = { 0xAB, 0xCD, 0xEF };
static const uint8_t bytes_zeros10[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t bytes_far129[145];
static uint8_t bytes_overlap160[160];

static const TestCase test_cases[] = {
    { "zx7 one", zx7_Decompress, zx7_one_compressed, bytes_one, sizeof(bytes_one) },
    { "zx7 two", zx7_Decompress, zx7_two_compressed, bytes_two, sizeof(bytes_two) },
    { "zx7 three", zx7_Decompress, zx7_three_compressed, bytes_three, sizeof(bytes_three) },
    { "zx7 zeros10", zx7_Decompress, zx7_zeros10_compressed, bytes_zeros10, sizeof(bytes_zeros10) },
    { "zx0 one", zx0_Decompress, zx0_one_compressed, bytes_one, sizeof(bytes_one) },
    { "zx0 two", zx0_Decompress, zx0_two_compressed, bytes_two, sizeof(bytes_two) },
    { "zx0 three", zx0_Decompress, zx0_three_compressed, bytes_three, sizeof(bytes_three) },
    { "zx0 zeros10", zx0_Decompress, zx0_zeros10_compressed, bytes_zeros10, sizeof(bytes_zeros10) },
    { "zx7 far129", zx7_Decompress, zx7_far129_compressed, bytes_far129, sizeof(bytes_far129) },
    { "zx0 far129", zx0_Decompress, zx0_far129_compressed, bytes_far129, sizeof(bytes_far129) },
    { "zx7 overlap160", zx7_Decompress, zx7_overlap160_compressed, bytes_overlap160, sizeof(bytes_overlap160) },
    { "zx0 overlap160", zx0_Decompress, zx0_overlap160_compressed, bytes_overlap160, sizeof(bytes_overlap160) },
};

static const Stage stages[] = {
    { "1 ZX7 1/2/3-byte", 0, 3 },
    { "2 ZX7 zero-run", 3, 1 },
    { "3 ZX0 1/2/3-byte", 4, 3 },
    { "4 ZX0 zero-run", 7, 1 },
    { "5 far offset >128", 8, 2 },
    { "6 overlap repeat", 10, 2 },
};

static const uint8_t canary_bytes[CANARY_SIZE] = { CANARY, CANARY, CANARY, CANARY };

static void init_expected_payloads(void) {
    for (size_t i = 0; i < 129; i++) {
        bytes_far129[i] = (uint8_t)i;
    }
    for (size_t i = 0; i < 16; i++) {
        bytes_far129[129 + i] = (uint8_t)i;
    }
    memset(bytes_overlap160, 0x41, sizeof(bytes_overlap160));
}

static int run_one_test(const TestCase *test_case) {
    Buffer buffer;

    memset(&buffer, SENTINEL, sizeof(buffer));
    memset(buffer.before, CANARY, sizeof(buffer.before));
    memset(buffer.data + test_case->expected_size, CANARY, CANARY_SIZE);

    test_case->decompress(buffer.data, test_case->compressed);

    C(memcmp(buffer.data, test_case->expected, test_case->expected_size) == 0);
    C(memcmp(buffer.before, canary_bytes, CANARY_SIZE) == 0);
    C(memcmp(buffer.data + test_case->expected_size, canary_bytes, CANARY_SIZE) == 0);

    for (size_t i = test_case->expected_size + CANARY_SIZE; i < sizeof(buffer.data); i++) {
        C(buffer.data[i] == SENTINEL);
    }

    return 0;
}

static int run_stage(const Stage *stage, const TestCase **failed_test) {
    for (size_t i = 0; i < stage->test_count; i++) {
        const TestCase *test_case = &test_cases[stage->first_test + i];
        int result = run_one_test(test_case);
        if (result != 0) {
            *failed_test = test_case;
            return result;
        }
    }

    *failed_test = NULL;
    return 0;
}

static void wait_for_key(void) {
    while (!os_GetCSC()) {
    }
}

int main(void)
{
    init_expected_payloads();

    for (size_t i = 0; i < sizeof(stages) / sizeof(stages[0]); i++) {
        const TestCase *failed_test;
        int result = run_stage(&stages[i], &failed_test);

        os_ClrHome();
        puts(stages[i].title);
        if (result == 0) {
            puts("PASS");
            puts("dst exact");
            puts("guards intact");
        } else {
            puts("FAIL");
            puts(failed_test->name);
            printf("line %d\n", result);
        }

        wait_for_key();
        if (result != 0) {
            return 0;
        }
    }

    os_ClrHome();
    puts("All stages passed");
    wait_for_key();

    return 0;
}
