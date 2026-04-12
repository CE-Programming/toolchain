#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <graphx.h>
#include <ti/getcsc.h>
#include <ti/screen.h>

typedef struct DrawFailure {
    const char *name;
    uint8_t got;
    uint8_t expected;
} DrawFailure;

static bool expect_draw(DrawFailure *failure, const char *name, uint8_t expected) {
    uint8_t got = gfx_GetDraw();
    if (got != expected) {
        failure->name = name;
        failure->got = got;
        failure->expected = expected;
        return false;
    }
    return true;
}

static bool run_test(DrawFailure *failure) {
    if (!expect_draw(failure, "after begin", gfx_screen)) {
        return false;
    }

    gfx_SetDraw(gfx_buffer);
    if (!expect_draw(failure, "after set buffer", gfx_buffer)) {
        return false;
    }

    gfx_SetDraw(gfx_screen);
    if (!expect_draw(failure, "after set screen", gfx_screen)) {
        return false;
    }

    gfx_SetDraw(gfx_buffer);
    gfx_SwapDraw();
    if (!expect_draw(failure, "after swap from buffer", gfx_buffer)) {
        return false;
    }

    gfx_SetDraw(gfx_screen);
    if (!expect_draw(failure, "after set screen post swap", gfx_screen)) {
        return false;
    }

    gfx_SwapDraw();
    if (!expect_draw(failure, "after swap from screen", gfx_buffer)) {
        return false;
    }

    return true;
}

int main(void) {
    DrawFailure failure = { 0 };
    bool passed;

    gfx_Begin();
    passed = run_test(&failure);
    gfx_End();

    os_ClrHome();

    if (passed) {
        puts("All tests passed");
    } else {
        printf(
            "%s\nG:%u\nE:%u",
            failure.name,
            (unsigned int)failure.got,
            (unsigned int)failure.expected
        );
    }

    while (!os_GetCSC()) {
    }

    return 0;
}
