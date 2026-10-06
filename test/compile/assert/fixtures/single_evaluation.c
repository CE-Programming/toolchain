#include <assert.h>

/* Optimization must remove this call. A missing or repeated evaluation keeps
 * it reachable and makes the compiler fail, without inspecting assembly/IR. */
void bad_assert_evaluation(void)
    __attribute__((__error__("assert evaluated its condition incorrectly")));

#ifdef __cplusplus
extern "C"
#endif
int assert_single_eval(void) {
    int evaluations = 0;
    assert(++evaluations);
#ifdef NDEBUG
    if (evaluations != 0)
#else
    if (evaluations != 1)
#endif
        bad_assert_evaluation();
    return evaluations;
}
