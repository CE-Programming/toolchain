#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <graphx.h>
#include <ti/getcsc.h>
#include <ti/screen.h>

typedef struct ClipCase {
    const char *name;
    gfx_region_t input;
    bool visible;
    gfx_region_t output;
} ClipCase;

typedef struct TestFailure {
    const char *name;
    gfx_region_t got;
    gfx_region_t expected;
    bool got_visible;
    bool expected_visible;
} TestFailure;

static const ClipCase default_cases[] = {
    { "default no clip",         {  10,  20,  30,  40 }, true,  {  10,  20,  30,  40 } },
    { "default one side",        {  -5,  20,  30,  40 }, true,  {   0,  20,  30,  40 } },
    { "default multi side",      {  -5,  -6, 400, 300 }, true,  {   0,   0, 320, 240 } },
    { "default outside",         { 330,  10, 340,  20 }, false, {   0,   0,   0,   0 } },
    { "default zero width",      {   5,   5,   5,  10 }, false, {   0,   0,   0,   0 } },
    { "default zero height",     {   5,   5,  10,   5 }, false, {   0,   0,   0,   0 } },
};

static const ClipCase custom_cases[] = {
    { "custom no clip",          {  60,  70, 100, 150 }, true,  {  60,  70, 100, 150 } },
    { "custom one side",         {  40,  70, 100, 150 }, true,  {  50,  70, 100, 150 } },
    { "custom multi side",       {   0,   0, 300, 300 }, true,  {  50,  60, 200, 180 } },
    { "custom outside",          {   0,  70,  40, 150 }, false, {   0,   0,   0,   0 } },
    { "custom zero width clip",  {   0,  70,  50, 150 }, false, {   0,   0,   0,   0 } },
    { "custom zero height clip", {  70,   0, 150,  60 }, false, {   0,   0,   0,   0 } },
};

static bool region_equal(const gfx_region_t *lhs, const gfx_region_t *rhs) {
    return lhs->xmin == rhs->xmin &&
           lhs->ymin == rhs->ymin &&
           lhs->xmax == rhs->xmax &&
           lhs->ymax == rhs->ymax;
}

static bool run_cases(const ClipCase *cases, size_t count, TestFailure *failure) {
    for (size_t i = 0; i < count; i++) {
        gfx_region_t region = cases[i].input;
        bool visible = gfx_GetClipRegion(&region);

        if (visible != cases[i].visible) {
            failure->name = cases[i].name;
            failure->got = region;
            failure->expected = cases[i].output;
            failure->got_visible = visible;
            failure->expected_visible = cases[i].visible;
            return false;
        }

        if (visible && !region_equal(&region, &cases[i].output)) {
            failure->name = cases[i].name;
            failure->got = region;
            failure->expected = cases[i].output;
            failure->got_visible = visible;
            failure->expected_visible = cases[i].visible;
            return false;
        }
    }

    return true;
}

int main(void) {
    TestFailure failure = { 0 };
    bool passed;

    gfx_Begin();

    passed = run_cases(default_cases, sizeof(default_cases) / sizeof(default_cases[0]), &failure);
    if (passed) {
        gfx_SetClipRegion(50, 60, 200, 180);
        passed = run_cases(custom_cases, sizeof(custom_cases) / sizeof(custom_cases[0]), &failure);
    }

    gfx_End();

    os_ClrHome();

    if (passed) {
        puts("All tests passed");
    } else {
        printf(
            "%s\nV:%u/%u\nG:%d,%d,%d,%d\nE:%d,%d,%d,%d",
            failure.name,
            (unsigned int)failure.got_visible,
            (unsigned int)failure.expected_visible,
            failure.got.xmin,
            failure.got.ymin,
            failure.got.xmax,
            failure.got.ymax,
            failure.expected.xmin,
            failure.expected.ymin,
            failure.expected.xmax,
            failure.expected.ymax
        );
    }

    while (!os_GetCSC()) {
    }

    return 0;
}
