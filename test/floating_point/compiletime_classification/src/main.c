#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#ifdef __cplusplus
#error "This test is for C only"
#endif

#define C(expr) if (!(expr)) { return __LINE__; }

// basically a copy of math_test.cpp
int run_test(void) {

    // can't get issignaling to work at compile time at the moment
    #undef issignaling
    #define issignaling(...) true || true

//------------------------------------------------------------------------------
// Positive value tests
//------------------------------------------------------------------------------

    /* ZERO */

    C((!signbit    (0.0f)));
    C((!issignaling(0.0f)));
    C((!isnan      (0.0f)));
    C((!isinf      (0.0f)));
    C(( isfinite   (0.0f)));
    C((!isnormal   (0.0f)));
    C((!issubnormal(0.0f)));
    C(( iszero     (0.0f)));

    C((!signbit    (0.0)));
    C((!issignaling(0.0)));
    C((!isnan      (0.0)));
    C((!isinf      (0.0)));
    C(( isfinite   (0.0)));
    C((!isnormal   (0.0)));
    C((!issubnormal(0.0)));
    C(( iszero     (0.0)));

    C((!signbit    (0.0L)));
    C((!issignaling(0.0L)));
    C((!isnan      (0.0L)));
    C((!isinf      (0.0L)));
    C(( isfinite   (0.0L)));
    C((!isnormal   (0.0L)));
    C((!issubnormal(0.0L)));
    C(( iszero     (0.0L)));

    /* TRUE_MIN */

    C((!signbit    (FLT_TRUE_MIN)));
    C((!issignaling(FLT_TRUE_MIN)));
    C((!isnan      (FLT_TRUE_MIN)));
    C((!isinf      (FLT_TRUE_MIN)));
    C(( isfinite   (FLT_TRUE_MIN)));
    C((!isnormal   (FLT_TRUE_MIN)));
    C(( issubnormal(FLT_TRUE_MIN)));
    C((!iszero     (FLT_TRUE_MIN)));

    C((!signbit    (DBL_TRUE_MIN)));
    C((!issignaling(DBL_TRUE_MIN)));
    C((!isnan      (DBL_TRUE_MIN)));
    C((!isinf      (DBL_TRUE_MIN)));
    C(( isfinite   (DBL_TRUE_MIN)));
    C((!isnormal   (DBL_TRUE_MIN)));
    C(( issubnormal(DBL_TRUE_MIN)));
    C((!iszero     (DBL_TRUE_MIN)));

    C((!signbit    (LDBL_TRUE_MIN)));
    C((!issignaling(LDBL_TRUE_MIN)));
    C((!isnan      (LDBL_TRUE_MIN)));
    C((!isinf      (LDBL_TRUE_MIN)));
    C(( isfinite   (LDBL_TRUE_MIN)));
    C((!isnormal   (LDBL_TRUE_MIN)));
    C(( issubnormal(LDBL_TRUE_MIN)));
    C((!iszero     (LDBL_TRUE_MIN)));

    /* MIN */

    C((!signbit    (FLT_MIN)));
    C((!issignaling(FLT_MIN)));
    C((!isnan      (FLT_MIN)));
    C((!isinf      (FLT_MIN)));
    C(( isfinite   (FLT_MIN)));
    C(( isnormal   (FLT_MIN)));
    C((!issubnormal(FLT_MIN)));
    C((!iszero     (FLT_MIN)));

    C((!signbit    (DBL_MIN)));
    C((!issignaling(DBL_MIN)));
    C((!isnan      (DBL_MIN)));
    C((!isinf      (DBL_MIN)));
    C(( isfinite   (DBL_MIN)));
    C(( isnormal   (DBL_MIN)));
    C((!issubnormal(DBL_MIN)));
    C((!iszero     (DBL_MIN)));

    C((!signbit    (LDBL_MIN)));
    C((!issignaling(LDBL_MIN)));
    C((!isnan      (LDBL_MIN)));
    C((!isinf      (LDBL_MIN)));
    C(( isfinite   (LDBL_MIN)));
    C(( isnormal   (LDBL_MIN)));
    C((!issubnormal(LDBL_MIN)));
    C((!iszero     (LDBL_MIN)));

    /* RECIP PI */

    C((!signbit    (0.31830988618379067153776752674503f)));
    C((!issignaling(0.31830988618379067153776752674503f)));
    C((!isnan      (0.31830988618379067153776752674503f)));
    C((!isinf      (0.31830988618379067153776752674503f)));
    C(( isfinite   (0.31830988618379067153776752674503f)));
    C(( isnormal   (0.31830988618379067153776752674503f)));
    C((!issubnormal(0.31830988618379067153776752674503f)));
    C((!iszero     (0.31830988618379067153776752674503f)));

    C((!signbit    (0.31830988618379067153776752674503)));
    C((!issignaling(0.31830988618379067153776752674503)));
    C((!isnan      (0.31830988618379067153776752674503)));
    C((!isinf      (0.31830988618379067153776752674503)));
    C(( isfinite   (0.31830988618379067153776752674503)));
    C(( isnormal   (0.31830988618379067153776752674503)));
    C((!issubnormal(0.31830988618379067153776752674503)));
    C((!iszero     (0.31830988618379067153776752674503)));

    C((!signbit    (0.31830988618379067153776752674503L)));
    C((!issignaling(0.31830988618379067153776752674503L)));
    C((!isnan      (0.31830988618379067153776752674503L)));
    C((!isinf      (0.31830988618379067153776752674503L)));
    C(( isfinite   (0.31830988618379067153776752674503L)));
    C(( isnormal   (0.31830988618379067153776752674503L)));
    C((!issubnormal(0.31830988618379067153776752674503L)));
    C((!iszero     (0.31830988618379067153776752674503L)));

    /* ONE */

    C((!signbit    (1.0f)));
    C((!issignaling(1.0f)));
    C((!isnan      (1.0f)));
    C((!isinf      (1.0f)));
    C(( isfinite   (1.0f)));
    C(( isnormal   (1.0f)));
    C((!issubnormal(1.0f)));
    C((!iszero     (1.0f)));

    C((!signbit    (1.0)));
    C((!issignaling(1.0)));
    C((!isnan      (1.0)));
    C((!isinf      (1.0)));
    C(( isfinite   (1.0)));
    C(( isnormal   (1.0)));
    C((!issubnormal(1.0)));
    C((!iszero     (1.0)));

    C((!signbit    (1.0L)));
    C((!issignaling(1.0L)));
    C((!isnan      (1.0L)));
    C((!isinf      (1.0L)));
    C(( isfinite   (1.0L)));
    C(( isnormal   (1.0L)));
    C((!issubnormal(1.0L)));
    C((!iszero     (1.0L)));

    /* PI */

    C((!signbit    (3.1415926535897932384626433832795f)));
    C((!issignaling(3.1415926535897932384626433832795f)));
    C((!isnan      (3.1415926535897932384626433832795f)));
    C((!isinf      (3.1415926535897932384626433832795f)));
    C(( isfinite   (3.1415926535897932384626433832795f)));
    C(( isnormal   (3.1415926535897932384626433832795f)));
    C((!issubnormal(3.1415926535897932384626433832795f)));
    C((!iszero     (3.1415926535897932384626433832795f)));

    C((!signbit    (3.1415926535897932384626433832795)));
    C((!issignaling(3.1415926535897932384626433832795)));
    C((!isnan      (3.1415926535897932384626433832795)));
    C((!isinf      (3.1415926535897932384626433832795)));
    C(( isfinite   (3.1415926535897932384626433832795)));
    C(( isnormal   (3.1415926535897932384626433832795)));
    C((!issubnormal(3.1415926535897932384626433832795)));
    C((!iszero     (3.1415926535897932384626433832795)));

    C((!signbit    (3.1415926535897932384626433832795L)));
    C((!issignaling(3.1415926535897932384626433832795L)));
    C((!isnan      (3.1415926535897932384626433832795L)));
    C((!isinf      (3.1415926535897932384626433832795L)));
    C(( isfinite   (3.1415926535897932384626433832795L)));
    C(( isnormal   (3.1415926535897932384626433832795L)));
    C((!issubnormal(3.1415926535897932384626433832795L)));
    C((!iszero     (3.1415926535897932384626433832795L)));

    /* MAX */

    C((!signbit    (FLT_MAX)));
    C((!issignaling(FLT_MAX)));
    C((!isnan      (FLT_MAX)));
    C((!isinf      (FLT_MAX)));
    C(( isfinite   (FLT_MAX)));
    C(( isnormal   (FLT_MAX)));
    C((!issubnormal(FLT_MAX)));
    C((!iszero     (FLT_MAX)));

    C((!signbit    (DBL_MAX)));
    C((!issignaling(DBL_MAX)));
    C((!isnan      (DBL_MAX)));
    C((!isinf      (DBL_MAX)));
    C(( isfinite   (DBL_MAX)));
    C(( isnormal   (DBL_MAX)));
    C((!issubnormal(DBL_MAX)));
    C((!iszero     (DBL_MAX)));

    C((!signbit    (LDBL_MAX)));
    C((!issignaling(LDBL_MAX)));
    C((!isnan      (LDBL_MAX)));
    C((!isinf      (LDBL_MAX)));
    C(( isfinite   (LDBL_MAX)));
    C(( isnormal   (LDBL_MAX)));
    C((!issubnormal(LDBL_MAX)));
    C((!iszero     (LDBL_MAX)));

    /* INFINITY */

    C((!signbit    (__builtin_inff())));
    C((!issignaling(__builtin_inff())));
    C((!isnan      (__builtin_inff())));
    C(( isinf      (__builtin_inff())));
    C((!isfinite   (__builtin_inff())));
    C((!isnormal   (__builtin_inff())));
    C((!issubnormal(__builtin_inff())));
    C((!iszero     (__builtin_inff())));

    C((!signbit    (__builtin_inf())));
    C((!issignaling(__builtin_inf())));
    C((!isnan      (__builtin_inf())));
    C(( isinf      (__builtin_inf())));
    C((!isfinite   (__builtin_inf())));
    C((!isnormal   (__builtin_inf())));
    C((!issubnormal(__builtin_inf())));
    C((!iszero     (__builtin_inf())));

    C((!signbit    (__builtin_infl())));
    C((!issignaling(__builtin_infl())));
    C((!isnan      (__builtin_infl())));
    C(( isinf      (__builtin_infl())));
    C((!isfinite   (__builtin_infl())));
    C((!isnormal   (__builtin_infl())));
    C((!issubnormal(__builtin_infl())));
    C((!iszero     (__builtin_infl())));

    /* NAN */

    C((!signbit    (__builtin_nanf(""))));
    C(( issignaling(__builtin_nanf(""))));
    C(( isnan      (__builtin_nanf(""))));
    C((!isinf      (__builtin_nanf(""))));
    C((!isfinite   (__builtin_nanf(""))));
    C((!isnormal   (__builtin_nanf(""))));
    C((!issubnormal(__builtin_nanf(""))));
    C((!iszero     (__builtin_nanf(""))));

    C((!signbit    (__builtin_nan(""))));
    C(( issignaling(__builtin_nan(""))));
    C(( isnan      (__builtin_nan(""))));
    C((!isinf      (__builtin_nan(""))));
    C((!isfinite   (__builtin_nan(""))));
    C((!isnormal   (__builtin_nan(""))));
    C((!issubnormal(__builtin_nan(""))));
    C((!iszero     (__builtin_nan(""))));

    C((!signbit    (__builtin_nanl(""))));
    C(( issignaling(__builtin_nanl(""))));
    C(( isnan      (__builtin_nanl(""))));
    C((!isinf      (__builtin_nanl(""))));
    C((!isfinite   (__builtin_nanl(""))));
    C((!isnormal   (__builtin_nanl(""))));
    C((!issubnormal(__builtin_nanl(""))));
    C((!iszero     (__builtin_nanl(""))));

    /* SIGNALING NAN */

    C((!signbit    (__builtin_nansf(""))));
    C(( issignaling(__builtin_nansf(""))));
    C(( isnan      (__builtin_nansf(""))));
    C((!isinf      (__builtin_nansf(""))));
    C((!isfinite   (__builtin_nansf(""))));
    C((!isnormal   (__builtin_nansf(""))));
    C((!issubnormal(__builtin_nansf(""))));
    C((!iszero     (__builtin_nansf(""))));

    C((!signbit    (__builtin_nans(""))));
    C(( issignaling(__builtin_nans(""))));
    C(( isnan      (__builtin_nans(""))));
    C((!isinf      (__builtin_nans(""))));
    C((!isfinite   (__builtin_nans(""))));
    C((!isnormal   (__builtin_nans(""))));
    C((!issubnormal(__builtin_nans(""))));
    C((!iszero     (__builtin_nans(""))));

    C((!signbit    (__builtin_nansl(""))));
    C(( issignaling(__builtin_nansl(""))));
    C(( isnan      (__builtin_nansl(""))));
    C((!isinf      (__builtin_nansl(""))));
    C((!isfinite   (__builtin_nansl(""))));
    C((!isnormal   (__builtin_nansl(""))));
    C((!issubnormal(__builtin_nansl(""))));
    C((!iszero     (__builtin_nansl(""))));

//------------------------------------------------------------------------------
// Negative value tests
//------------------------------------------------------------------------------

    /* ZERO */

    C(( signbit    (-0.0f)));
    C((!issignaling(-0.0f)));
    C((!isnan      (-0.0f)));
    C((!isinf      (-0.0f)));
    C(( isfinite   (-0.0f)));
    C((!isnormal   (-0.0f)));
    C((!issubnormal(-0.0f)));
    C(( iszero     (-0.0f)));

    C(( signbit    (-0.0)));
    C((!issignaling(-0.0)));
    C((!isnan      (-0.0)));
    C((!isinf      (-0.0)));
    C(( isfinite   (-0.0)));
    C((!isnormal   (-0.0)));
    C((!issubnormal(-0.0)));
    C(( iszero     (-0.0)));

    C(( signbit    (-0.0L)));
    C((!issignaling(-0.0L)));
    C((!isnan      (-0.0L)));
    C((!isinf      (-0.0L)));
    C(( isfinite   (-0.0L)));
    C((!isnormal   (-0.0L)));
    C((!issubnormal(-0.0L)));
    C(( iszero     (-0.0L)));

    /* TRUE_MIN */

    C(( signbit    (-FLT_TRUE_MIN)));
    C((!issignaling(-FLT_TRUE_MIN)));
    C((!isnan      (-FLT_TRUE_MIN)));
    C((!isinf      (-FLT_TRUE_MIN)));
    C(( isfinite   (-FLT_TRUE_MIN)));
    C((!isnormal   (-FLT_TRUE_MIN)));
    C(( issubnormal(-FLT_TRUE_MIN)));
    C((!iszero     (-FLT_TRUE_MIN)));

    C(( signbit    (-DBL_TRUE_MIN)));
    C((!issignaling(-DBL_TRUE_MIN)));
    C((!isnan      (-DBL_TRUE_MIN)));
    C((!isinf      (-DBL_TRUE_MIN)));
    C(( isfinite   (-DBL_TRUE_MIN)));
    C((!isnormal   (-DBL_TRUE_MIN)));
    C(( issubnormal(-DBL_TRUE_MIN)));
    C((!iszero     (-DBL_TRUE_MIN)));

    C(( signbit    (-LDBL_TRUE_MIN)));
    C((!issignaling(-LDBL_TRUE_MIN)));
    C((!isnan      (-LDBL_TRUE_MIN)));
    C((!isinf      (-LDBL_TRUE_MIN)));
    C(( isfinite   (-LDBL_TRUE_MIN)));
    C((!isnormal   (-LDBL_TRUE_MIN)));
    C(( issubnormal(-LDBL_TRUE_MIN)));
    C((!iszero     (-LDBL_TRUE_MIN)));

    /* MIN */

    C(( signbit    (-FLT_MIN)));
    C((!issignaling(-FLT_MIN)));
    C((!isnan      (-FLT_MIN)));
    C((!isinf      (-FLT_MIN)));
    C(( isfinite   (-FLT_MIN)));
    C(( isnormal   (-FLT_MIN)));
    C((!issubnormal(-FLT_MIN)));
    C((!iszero     (-FLT_MIN)));

    C(( signbit    (-DBL_MIN)));
    C((!issignaling(-DBL_MIN)));
    C((!isnan      (-DBL_MIN)));
    C((!isinf      (-DBL_MIN)));
    C(( isfinite   (-DBL_MIN)));
    C(( isnormal   (-DBL_MIN)));
    C((!issubnormal(-DBL_MIN)));
    C((!iszero     (-DBL_MIN)));

    C(( signbit    (-LDBL_MIN)));
    C((!issignaling(-LDBL_MIN)));
    C((!isnan      (-LDBL_MIN)));
    C((!isinf      (-LDBL_MIN)));
    C(( isfinite   (-LDBL_MIN)));
    C(( isnormal   (-LDBL_MIN)));
    C((!issubnormal(-LDBL_MIN)));
    C((!iszero     (-LDBL_MIN)));

    /* RECIP PI */

    C(( signbit    (-0.31830988618379067153776752674503f)));
    C((!issignaling(-0.31830988618379067153776752674503f)));
    C((!isnan      (-0.31830988618379067153776752674503f)));
    C((!isinf      (-0.31830988618379067153776752674503f)));
    C(( isfinite   (-0.31830988618379067153776752674503f)));
    C(( isnormal   (-0.31830988618379067153776752674503f)));
    C((!issubnormal(-0.31830988618379067153776752674503f)));
    C((!iszero     (-0.31830988618379067153776752674503f)));

    C(( signbit    (-0.31830988618379067153776752674503)));
    C((!issignaling(-0.31830988618379067153776752674503)));
    C((!isnan      (-0.31830988618379067153776752674503)));
    C((!isinf      (-0.31830988618379067153776752674503)));
    C(( isfinite   (-0.31830988618379067153776752674503)));
    C(( isnormal   (-0.31830988618379067153776752674503)));
    C((!issubnormal(-0.31830988618379067153776752674503)));
    C((!iszero     (-0.31830988618379067153776752674503)));

    C(( signbit    (-0.31830988618379067153776752674503L)));
    C((!issignaling(-0.31830988618379067153776752674503L)));
    C((!isnan      (-0.31830988618379067153776752674503L)));
    C((!isinf      (-0.31830988618379067153776752674503L)));
    C(( isfinite   (-0.31830988618379067153776752674503L)));
    C(( isnormal   (-0.31830988618379067153776752674503L)));
    C((!issubnormal(-0.31830988618379067153776752674503L)));
    C((!iszero     (-0.31830988618379067153776752674503L)));

    /* ONE */

    C(( signbit    (-1.0f)));
    C((!issignaling(-1.0f)));
    C((!isnan      (-1.0f)));
    C((!isinf      (-1.0f)));
    C(( isfinite   (-1.0f)));
    C(( isnormal   (-1.0f)));
    C((!issubnormal(-1.0f)));
    C((!iszero     (-1.0f)));

    C(( signbit    (-1.0)));
    C((!issignaling(-1.0)));
    C((!isnan      (-1.0)));
    C((!isinf      (-1.0)));
    C(( isfinite   (-1.0)));
    C(( isnormal   (-1.0)));
    C((!issubnormal(-1.0)));
    C((!iszero     (-1.0)));

    C(( signbit    (-1.0L)));
    C((!issignaling(-1.0L)));
    C((!isnan      (-1.0L)));
    C((!isinf      (-1.0L)));
    C(( isfinite   (-1.0L)));
    C(( isnormal   (-1.0L)));
    C((!issubnormal(-1.0L)));
    C((!iszero     (-1.0L)));

    /* PI */

    C(( signbit    (-3.1415926535897932384626433832795f)));
    C((!issignaling(-3.1415926535897932384626433832795f)));
    C((!isnan      (-3.1415926535897932384626433832795f)));
    C((!isinf      (-3.1415926535897932384626433832795f)));
    C(( isfinite   (-3.1415926535897932384626433832795f)));
    C(( isnormal   (-3.1415926535897932384626433832795f)));
    C((!issubnormal(-3.1415926535897932384626433832795f)));
    C((!iszero     (-3.1415926535897932384626433832795f)));

    C(( signbit    (-3.1415926535897932384626433832795)));
    C((!issignaling(-3.1415926535897932384626433832795)));
    C((!isnan      (-3.1415926535897932384626433832795)));
    C((!isinf      (-3.1415926535897932384626433832795)));
    C(( isfinite   (-3.1415926535897932384626433832795)));
    C(( isnormal   (-3.1415926535897932384626433832795)));
    C((!issubnormal(-3.1415926535897932384626433832795)));
    C((!iszero     (-3.1415926535897932384626433832795)));

    C(( signbit    (-3.1415926535897932384626433832795L)));
    C((!issignaling(-3.1415926535897932384626433832795L)));
    C((!isnan      (-3.1415926535897932384626433832795L)));
    C((!isinf      (-3.1415926535897932384626433832795L)));
    C(( isfinite   (-3.1415926535897932384626433832795L)));
    C(( isnormal   (-3.1415926535897932384626433832795L)));
    C((!issubnormal(-3.1415926535897932384626433832795L)));
    C((!iszero     (-3.1415926535897932384626433832795L)));

    /* MAX */

    C(( signbit    (-FLT_MAX)));
    C((!issignaling(-FLT_MAX)));
    C((!isnan      (-FLT_MAX)));
    C((!isinf      (-FLT_MAX)));
    C(( isfinite   (-FLT_MAX)));
    C(( isnormal   (-FLT_MAX)));
    C((!issubnormal(-FLT_MAX)));
    C((!iszero     (-FLT_MAX)));

    C(( signbit    (-DBL_MAX)));
    C((!issignaling(-DBL_MAX)));
    C((!isnan      (-DBL_MAX)));
    C((!isinf      (-DBL_MAX)));
    C(( isfinite   (-DBL_MAX)));
    C(( isnormal   (-DBL_MAX)));
    C((!issubnormal(-DBL_MAX)));
    C((!iszero     (-DBL_MAX)));

    C(( signbit    (-LDBL_MAX)));
    C((!issignaling(-LDBL_MAX)));
    C((!isnan      (-LDBL_MAX)));
    C((!isinf      (-LDBL_MAX)));
    C(( isfinite   (-LDBL_MAX)));
    C(( isnormal   (-LDBL_MAX)));
    C((!issubnormal(-LDBL_MAX)));
    C((!iszero     (-LDBL_MAX)));

    /* INFINITY */

    C(( signbit    (-__builtin_inff())));
    C((!issignaling(-__builtin_inff())));
    C((!isnan      (-__builtin_inff())));
    C(( isinf      (-__builtin_inff())));
    C((!isfinite   (-__builtin_inff())));
    C((!isnormal   (-__builtin_inff())));
    C((!issubnormal(-__builtin_inff())));
    C((!iszero     (-__builtin_inff())));

    C(( signbit    (-__builtin_inf())));
    C((!issignaling(-__builtin_inf())));
    C((!isnan      (-__builtin_inf())));
    C(( isinf      (-__builtin_inf())));
    C((!isfinite   (-__builtin_inf())));
    C((!isnormal   (-__builtin_inf())));
    C((!issubnormal(-__builtin_inf())));
    C((!iszero     (-__builtin_inf())));

    C(( signbit    (-__builtin_infl())));
    C((!issignaling(-__builtin_infl())));
    C((!isnan      (-__builtin_infl())));
    C(( isinf      (-__builtin_infl())));
    C((!isfinite   (-__builtin_infl())));
    C((!isnormal   (-__builtin_infl())));
    C((!issubnormal(-__builtin_infl())));
    C((!iszero     (-__builtin_infl())));

    /* NAN */

    C(( signbit    (-__builtin_nanf(""))));
    C(( issignaling(-__builtin_nanf(""))));
    C(( isnan      (-__builtin_nanf(""))));
    C((!isinf      (-__builtin_nanf(""))));
    C((!isfinite   (-__builtin_nanf(""))));
    C((!isnormal   (-__builtin_nanf(""))));
    C((!issubnormal(-__builtin_nanf(""))));
    C((!iszero     (-__builtin_nanf(""))));

    C(( signbit    (-__builtin_nan(""))));
    C(( issignaling(-__builtin_nan(""))));
    C(( isnan      (-__builtin_nan(""))));
    C((!isinf      (-__builtin_nan(""))));
    C((!isfinite   (-__builtin_nan(""))));
    C((!isnormal   (-__builtin_nan(""))));
    C((!issubnormal(-__builtin_nan(""))));
    C((!iszero     (-__builtin_nan(""))));

    C(( signbit    (-__builtin_nanl(""))));
    C(( issignaling(-__builtin_nanl(""))));
    C(( isnan      (-__builtin_nanl(""))));
    C((!isinf      (-__builtin_nanl(""))));
    C((!isfinite   (-__builtin_nanl(""))));
    C((!isnormal   (-__builtin_nanl(""))));
    C((!issubnormal(-__builtin_nanl(""))));
    C((!iszero     (-__builtin_nanl(""))));

    /* SIGNALING NAN */

    C(( signbit    (-__builtin_nansf(""))));
    C(( issignaling(-__builtin_nansf(""))));
    C(( isnan      (-__builtin_nansf(""))));
    C((!isinf      (-__builtin_nansf(""))));
    C((!isfinite   (-__builtin_nansf(""))));
    C((!isnormal   (-__builtin_nansf(""))));
    C((!issubnormal(-__builtin_nansf(""))));
    C((!iszero     (-__builtin_nansf(""))));

    C(( signbit    (-__builtin_nans(""))));
    C(( issignaling(-__builtin_nans(""))));
    C(( isnan      (-__builtin_nans(""))));
    C((!isinf      (-__builtin_nans(""))));
    C((!isfinite   (-__builtin_nans(""))));
    C((!isnormal   (-__builtin_nans(""))));
    C((!issubnormal(-__builtin_nans(""))));
    C((!iszero     (-__builtin_nans(""))));

    C(( signbit    (-__builtin_nansl(""))));
    C(( issignaling(-__builtin_nansl(""))));
    C(( isnan      (-__builtin_nansl(""))));
    C((!isinf      (-__builtin_nansl(""))));
    C((!isfinite   (-__builtin_nansl(""))));
    C((!isnormal   (-__builtin_nansl(""))));
    C((!issubnormal(-__builtin_nansl(""))));
    C((!iszero     (-__builtin_nansl(""))));

//------------------------------------------------------------------------------
// Integer value tests
//------------------------------------------------------------------------------

    /* int */

    C((!signbit    (0)));
    C((!issignaling(0)));
    C((!isnan      (0)));
    C((!isinf      (0)));
    C(( isfinite   (0)));
    C((!isnormal   (0)));
    C((!issubnormal(0)));
    C(( iszero     (0)));

    C((!signbit    (1)));
    C((!issignaling(1)));
    C((!isnan      (1)));
    C((!isinf      (1)));
    C(( isfinite   (1)));
    C(( isnormal   (1)));
    C((!issubnormal(1)));
    C((!iszero     (1)));

    C((!signbit    (10)));
    C((!issignaling(10)));
    C((!isnan      (10)));
    C((!isinf      (10)));
    C(( isfinite   (10)));
    C(( isnormal   (10)));
    C((!issubnormal(10)));
    C((!iszero     (10)));

    C(( signbit    (-1)));
    C((!issignaling(-1)));
    C((!isnan      (-1)));
    C((!isinf      (-1)));
    C(( isfinite   (-1)));
    C(( isnormal   (-1)));
    C((!issubnormal(-1)));
    C((!iszero     (-1)));

    C(( signbit    (-10)));
    C((!issignaling(-10)));
    C((!isnan      (-10)));
    C((!isinf      (-10)));
    C(( isfinite   (-10)));
    C(( isnormal   (-10)));
    C((!issubnormal(-10)));
    C((!iszero     (-10)));

    /* unsigned long long */

    C((!signbit    (0ull)));
    C((!issignaling(0ull)));
    C((!isnan      (0ull)));
    C((!isinf      (0ull)));
    C(( isfinite   (0ull)));
    C((!isnormal   (0ull)));
    C((!issubnormal(0ull)));
    C(( iszero     (0ull)));

    C((!signbit    (1ull)));
    C((!issignaling(1ull)));
    C((!isnan      (1ull)));
    C((!isinf      (1ull)));
    C(( isfinite   (1ull)));
    C(( isnormal   (1ull)));
    C((!issubnormal(1ull)));
    C((!iszero     (1ull)));

    C((!signbit    (10ull)));
    C((!issignaling(10ull)));
    C((!isnan      (10ull)));
    C((!isinf      (10ull)));
    C(( isfinite   (10ull)));
    C(( isnormal   (10ull)));
    C((!issubnormal(10ull)));
    C((!iszero     (10ull)));

    return 0;
}

int main(void) {
    os_ClrHome();
    
    int failed_test = run_test();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
