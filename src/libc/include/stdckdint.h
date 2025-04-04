#ifndef _STDCKDINT_H
#define _STDCKDINT_H

#define __STDC_VERSION_STDCKDINT_H__ 202311L

#define ckd_add(R, A, B) __builtin_add_overflow((A), (B), (R))
#define ckd_sub(R, A, B) __builtin_sub_overflow((A), (B), (R))
#define ckd_mul(R, A, B) __builtin_mul_overflow((A), (B), (R))

#endif /* _STDCKDINT_H */
