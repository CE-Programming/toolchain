#pragma once

#define C(expr) if (!(expr)) { return __LINE__; }

#ifdef __cplusplus
extern "C" {
#endif

int test_1_c(void);

int test_2_cpp(void);

int test_3_asm(void);

int test_4_c(void);

int test_5_cpp(void);

#ifdef __cplusplus
}
#endif
