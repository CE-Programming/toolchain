#include <math.h>
#include <cmath>
#include <tgmath.h>
#include <ctgmath>
#include <float.h>
#include <cfloat>
#include <limits>

#define C(expr) static_assert(expr, #expr)

// can't get issignaling to work at compile time at the moment
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

C((!signbit    (std::numeric_limits<float>::denorm_min())));
C((!issignaling(std::numeric_limits<float>::denorm_min())));
C((!isnan      (std::numeric_limits<float>::denorm_min())));
C((!isinf      (std::numeric_limits<float>::denorm_min())));
C(( isfinite   (std::numeric_limits<float>::denorm_min())));
C((!isnormal   (std::numeric_limits<float>::denorm_min())));
C(( issubnormal(std::numeric_limits<float>::denorm_min())));
C((!iszero     (std::numeric_limits<float>::denorm_min())));

C((!signbit    (std::numeric_limits<double>::denorm_min())));
C((!issignaling(std::numeric_limits<double>::denorm_min())));
C((!isnan      (std::numeric_limits<double>::denorm_min())));
C((!isinf      (std::numeric_limits<double>::denorm_min())));
C(( isfinite   (std::numeric_limits<double>::denorm_min())));
C((!isnormal   (std::numeric_limits<double>::denorm_min())));
C(( issubnormal(std::numeric_limits<double>::denorm_min())));
C((!iszero     (std::numeric_limits<double>::denorm_min())));

C((!signbit    (std::numeric_limits<long double>::denorm_min())));
C((!issignaling(std::numeric_limits<long double>::denorm_min())));
C((!isnan      (std::numeric_limits<long double>::denorm_min())));
C((!isinf      (std::numeric_limits<long double>::denorm_min())));
C(( isfinite   (std::numeric_limits<long double>::denorm_min())));
C((!isnormal   (std::numeric_limits<long double>::denorm_min())));
C(( issubnormal(std::numeric_limits<long double>::denorm_min())));
C((!iszero     (std::numeric_limits<long double>::denorm_min())));

/* MIN */

C((!signbit    (std::numeric_limits<float>::min())));
C((!issignaling(std::numeric_limits<float>::min())));
C((!isnan      (std::numeric_limits<float>::min())));
C((!isinf      (std::numeric_limits<float>::min())));
C(( isfinite   (std::numeric_limits<float>::min())));
C(( isnormal   (std::numeric_limits<float>::min())));
C((!issubnormal(std::numeric_limits<float>::min())));
C((!iszero     (std::numeric_limits<float>::min())));

C((!signbit    (std::numeric_limits<double>::min())));
C((!issignaling(std::numeric_limits<double>::min())));
C((!isnan      (std::numeric_limits<double>::min())));
C((!isinf      (std::numeric_limits<double>::min())));
C(( isfinite   (std::numeric_limits<double>::min())));
C(( isnormal   (std::numeric_limits<double>::min())));
C((!issubnormal(std::numeric_limits<double>::min())));
C((!iszero     (std::numeric_limits<double>::min())));

C((!signbit    (std::numeric_limits<long double>::min())));
C((!issignaling(std::numeric_limits<long double>::min())));
C((!isnan      (std::numeric_limits<long double>::min())));
C((!isinf      (std::numeric_limits<long double>::min())));
C(( isfinite   (std::numeric_limits<long double>::min())));
C(( isnormal   (std::numeric_limits<long double>::min())));
C((!issubnormal(std::numeric_limits<long double>::min())));
C((!iszero     (std::numeric_limits<long double>::min())));

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

C((!signbit    (std::numeric_limits<float>::max())));
C((!issignaling(std::numeric_limits<float>::max())));
C((!isnan      (std::numeric_limits<float>::max())));
C((!isinf      (std::numeric_limits<float>::max())));
C(( isfinite   (std::numeric_limits<float>::max())));
C(( isnormal   (std::numeric_limits<float>::max())));
C((!issubnormal(std::numeric_limits<float>::max())));
C((!iszero     (std::numeric_limits<float>::max())));

C((!signbit    (std::numeric_limits<double>::max())));
C((!issignaling(std::numeric_limits<double>::max())));
C((!isnan      (std::numeric_limits<double>::max())));
C((!isinf      (std::numeric_limits<double>::max())));
C(( isfinite   (std::numeric_limits<double>::max())));
C(( isnormal   (std::numeric_limits<double>::max())));
C((!issubnormal(std::numeric_limits<double>::max())));
C((!iszero     (std::numeric_limits<double>::max())));

C((!signbit    (std::numeric_limits<long double>::max())));
C((!issignaling(std::numeric_limits<long double>::max())));
C((!isnan      (std::numeric_limits<long double>::max())));
C((!isinf      (std::numeric_limits<long double>::max())));
C(( isfinite   (std::numeric_limits<long double>::max())));
C(( isnormal   (std::numeric_limits<long double>::max())));
C((!issubnormal(std::numeric_limits<long double>::max())));
C((!iszero     (std::numeric_limits<long double>::max())));

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

C(( signbit    (-std::numeric_limits<float>::denorm_min())));
C((!issignaling(-std::numeric_limits<float>::denorm_min())));
C((!isnan      (-std::numeric_limits<float>::denorm_min())));
C((!isinf      (-std::numeric_limits<float>::denorm_min())));
C(( isfinite   (-std::numeric_limits<float>::denorm_min())));
C((!isnormal   (-std::numeric_limits<float>::denorm_min())));
C(( issubnormal(-std::numeric_limits<float>::denorm_min())));
C((!iszero     (-std::numeric_limits<float>::denorm_min())));

C(( signbit    (-std::numeric_limits<double>::denorm_min())));
C((!issignaling(-std::numeric_limits<double>::denorm_min())));
C((!isnan      (-std::numeric_limits<double>::denorm_min())));
C((!isinf      (-std::numeric_limits<double>::denorm_min())));
C(( isfinite   (-std::numeric_limits<double>::denorm_min())));
C((!isnormal   (-std::numeric_limits<double>::denorm_min())));
C(( issubnormal(-std::numeric_limits<double>::denorm_min())));
C((!iszero     (-std::numeric_limits<double>::denorm_min())));

C(( signbit    (-std::numeric_limits<long double>::denorm_min())));
C((!issignaling(-std::numeric_limits<long double>::denorm_min())));
C((!isnan      (-std::numeric_limits<long double>::denorm_min())));
C((!isinf      (-std::numeric_limits<long double>::denorm_min())));
C(( isfinite   (-std::numeric_limits<long double>::denorm_min())));
C((!isnormal   (-std::numeric_limits<long double>::denorm_min())));
C(( issubnormal(-std::numeric_limits<long double>::denorm_min())));
C((!iszero     (-std::numeric_limits<long double>::denorm_min())));

/* MIN */

C(( signbit    (-std::numeric_limits<float>::min())));
C((!issignaling(-std::numeric_limits<float>::min())));
C((!isnan      (-std::numeric_limits<float>::min())));
C((!isinf      (-std::numeric_limits<float>::min())));
C(( isfinite   (-std::numeric_limits<float>::min())));
C(( isnormal   (-std::numeric_limits<float>::min())));
C((!issubnormal(-std::numeric_limits<float>::min())));
C((!iszero     (-std::numeric_limits<float>::min())));

C(( signbit    (-std::numeric_limits<double>::min())));
C((!issignaling(-std::numeric_limits<double>::min())));
C((!isnan      (-std::numeric_limits<double>::min())));
C((!isinf      (-std::numeric_limits<double>::min())));
C(( isfinite   (-std::numeric_limits<double>::min())));
C(( isnormal   (-std::numeric_limits<double>::min())));
C((!issubnormal(-std::numeric_limits<double>::min())));
C((!iszero     (-std::numeric_limits<double>::min())));

C(( signbit    (-std::numeric_limits<long double>::min())));
C((!issignaling(-std::numeric_limits<long double>::min())));
C((!isnan      (-std::numeric_limits<long double>::min())));
C((!isinf      (-std::numeric_limits<long double>::min())));
C(( isfinite   (-std::numeric_limits<long double>::min())));
C(( isnormal   (-std::numeric_limits<long double>::min())));
C((!issubnormal(-std::numeric_limits<long double>::min())));
C((!iszero     (-std::numeric_limits<long double>::min())));

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

C(( signbit    (-std::numeric_limits<float>::max())));
C((!issignaling(-std::numeric_limits<float>::max())));
C((!isnan      (-std::numeric_limits<float>::max())));
C((!isinf      (-std::numeric_limits<float>::max())));
C(( isfinite   (-std::numeric_limits<float>::max())));
C(( isnormal   (-std::numeric_limits<float>::max())));
C((!issubnormal(-std::numeric_limits<float>::max())));
C((!iszero     (-std::numeric_limits<float>::max())));

C(( signbit    (-std::numeric_limits<double>::max())));
C((!issignaling(-std::numeric_limits<double>::max())));
C((!isnan      (-std::numeric_limits<double>::max())));
C((!isinf      (-std::numeric_limits<double>::max())));
C(( isfinite   (-std::numeric_limits<double>::max())));
C(( isnormal   (-std::numeric_limits<double>::max())));
C((!issubnormal(-std::numeric_limits<double>::max())));
C((!iszero     (-std::numeric_limits<double>::max())));

C(( signbit    (-std::numeric_limits<long double>::max())));
C((!issignaling(-std::numeric_limits<long double>::max())));
C((!isnan      (-std::numeric_limits<long double>::max())));
C((!isinf      (-std::numeric_limits<long double>::max())));
C(( isfinite   (-std::numeric_limits<long double>::max())));
C(( isnormal   (-std::numeric_limits<long double>::max())));
C((!issubnormal(-std::numeric_limits<long double>::max())));
C((!iszero     (-std::numeric_limits<long double>::max())));

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

#undef C
