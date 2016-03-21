#include <math.h>
#include <string.h>

static double zero(void) { return 0.0; }
static double one (void) { return 1.0; }
static double inf (void) { return one() / zero(); }

int isinf(double n) {
    static double pinf = 0.0;
    static double ninf = 0.0;

    if (pinf == 0.0) {
	pinf = inf();
	ninf = -pinf;
    }
    return memcmp(&n, &pinf, sizeof n) == 0 || memcmp(&n, &ninf, sizeof n) == 0;
}