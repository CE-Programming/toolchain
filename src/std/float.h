#ifndef _FLOAT_H
#define _FLOAT_H

#define _FENV_P_ONLY
#include <fenv.h>

#define  FLT_RADIX        __FLT_RADIX__

#if __STDC_VERSION__ >= 199901L
#define  FLT_EVAL_METHOD  __FLT_EVAL_METHOD__

#define      DECIMAL_DIG      __DECIMAL_DIG__
#endif

#if __STDC_VERSION__ >= 201112L
#define  FLT_DECIMAL_DIG  __FLT_DECIMAL_DIG__
#define  DBL_DECIMAL_DIG  __DBL_DECIMAL_DIG__
#define LDBL_DECIMAL_DIG __LDBL_DECIMAL_DIG__

#define  FLT_HAS_SUBNORM  __FLT_HAS_DENORM__
#define  DBL_HAS_SUBNORM  __DBL_HAS_DENORM__
#define LDBL_HAS_SUBNORM __LDBL_HAS_DENORM__

#define  FLT_TRUE_MIN     __FLT_DENORM_MIN__
#define  DBL_TRUE_MIN     __DBL_DENORM_MIN__
#define LDBL_TRUE_MIN    __LDBL_DENORM_MIN__
#endif

#define  FLT_MIN          __FLT_MIN__
#define  DBL_MIN          __DBL_MIN__
#define LDBL_MIN         __LDBL_MIN__

#define  FLT_MAX          __FLT_MAX__
#define  DBL_MAX          __DBL_MAX__
#define LDBL_MAX         __LDBL_MAX__

#define  FLT_EPSILON      __FLT_EPSILON__
#define  DBL_EPSILON      __DBL_EPSILON__
#define LDBL_EPSILON     __LDBL_EPSILON__

#define  FLT_DIG          __FLT_DIG__
#define  DBL_DIG          __DBL_DIG__
#define LDBL_DIG         __LDBL_DIG__

#define  FLT_MANT_DIG     __FLT_MANT_DIG__
#define  DBL_MANT_DIG     __DBL_MANT_DIG__
#define LDBL_MANT_DIG    __LDBL_MANT_DIG__

#define  FLT_MIN_EXP      __FLT_MIN_EXP__
#define  DBL_MIN_EXP      __DBL_MIN_EXP__
#define LDBL_MIN_EXP     __LDBL_MIN_EXP__

#define  FLT_MIN_10_EXP   __FLT_MIN_10_EXP__
#define  DBL_MIN_10_EXP   __DBL_MIN_10_EXP__
#define LDBL_MIN_10_EXP  __LDBL_MIN_10_EXP__

#define  FLT_MAX_EXP      __FLT_MAX_EXP__
#define  DBL_MAX_EXP      __DBL_MAX_EXP__
#define LDBL_MAX_EXP     __LDBL_MAX_EXP__

#define  FLT_MAX_10_EXP   __FLT_MAX_10_EXP__
#define  DBL_MAX_10_EXP   __DBL_MAX_10_EXP__
#define LDBL_MAX_10_EXP  __LDBL_MAX_10_EXP__

#define  FLT_ROUNDS      ((__fe_cur_env ^ 1) & 3)

#endif
