
/*============================================================================

This C header file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3e, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014, 2015, 2016, 2017 The Regents of the
University of California.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/


/*============================================================================
| Note:  If SoftFloat is made available as a general library for programs to
| use, it is strongly recommended that a platform-specific version of this
| header, "softfloat.h", be created that folds in "softfloat_types.h" and that
| eliminates all dependencies on compile-time macros.
*============================================================================*/


#ifndef softfloat_h
#define softfloat_h 1

#include <stdbool.h>
#include <stdint.h>

#if 1
#include <fenv.h>
#endif

#include "softfloat_types.h"

#ifndef THREAD_LOCAL
#define THREAD_LOCAL
#endif

/*----------------------------------------------------------------------------
| Software floating-point underflow tininess-detection mode.
*----------------------------------------------------------------------------*/
#if 0
extern THREAD_LOCAL uint_fast8_t softfloat_detectTininess;
#else
	#define softfloat_detectTininess softfloat_tininess_afterRounding
#endif
enum {
    softfloat_tininess_beforeRounding = 0,
    softfloat_tininess_afterRounding  = 1
};

/*----------------------------------------------------------------------------
| Software floating-point rounding mode.  (Mode "odd" is supported only if
| SoftFloat is compiled with macro 'SOFTFLOAT_ROUND_ODD' defined.)
*----------------------------------------------------------------------------*/
#if 0
extern THREAD_LOCAL uint_fast8_t softfloat_roundingMode;
#else
#define softfloat_roundingMode softfloat_round_near_even
#endif
enum {
    softfloat_round_near_even   = 0,
    softfloat_round_minMag      = 1,
    softfloat_round_min         = 2,
    softfloat_round_max         = 3,
    softfloat_round_near_maxMag = 4,
    softfloat_round_odd         = 6
};

/*----------------------------------------------------------------------------
| Software floating-point exception flags.
*----------------------------------------------------------------------------*/
#if 0
extern THREAD_LOCAL uint_fast8_t softfloat_exceptionFlags;
enum {
    softfloat_flag_inexact   =  1,
    softfloat_flag_underflow =  2,
    softfloat_flag_overflow  =  4,
    softfloat_flag_infinite  =  8,
    softfloat_flag_invalid   = 16
};
#else
#define softfloat_exceptionFlags __fe_cur_env
enum {
    softfloat_flag_inexact   = FE_INEXACT  ,
    softfloat_flag_underflow = FE_UNDERFLOW,
    softfloat_flag_overflow  = FE_OVERFLOW ,
    softfloat_flag_infinite  = FE_DIVBYZERO,
    softfloat_flag_invalid   = FE_INVALID
};
#endif

/*----------------------------------------------------------------------------
| Routine to raise any or all of the software floating-point exception flags.
*----------------------------------------------------------------------------*/
#if 0
void softfloat_raiseFlags( uint_fast8_t );
#else
static inline void softfloat_raiseFlags( uint_fast8_t flags ) {
    softfloat_exceptionFlags |= flags;
}
#endif

/*----------------------------------------------------------------------------
| Integer-to-floating-point conversion routines.
*----------------------------------------------------------------------------*/
float16_t __ui32_to_f16( uint32_t );
float32_t __ui32_to_f32( uint32_t );
float64_t __ui32_to_f64( uint32_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t __ui32_to_extF80( uint32_t );
float128_t __ui32_to_f128( uint32_t );
#endif
void __ui32_to_extF80M( uint32_t, extFloat80_t * );
void __ui32_to_f128M( uint32_t, float128_t * );
float16_t __ui64_to_f16( uint64_t );
float32_t __ui64_to_f32( uint64_t );
float64_t __ui64_to_f64( uint64_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t __ui64_to_extF80( uint64_t );
float128_t __ui64_to_f128( uint64_t );
#endif
void __ui64_to_extF80M( uint64_t, extFloat80_t * );
void __ui64_to_f128M( uint64_t, float128_t * );
float16_t __i32_to_f16( int32_t );
float32_t __i32_to_f32( int32_t );
float64_t __i32_to_f64( int32_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t __i32_to_extF80( int32_t );
float128_t __i32_to_f128( int32_t );
#endif
void __i32_to_extF80M( int32_t, extFloat80_t * );
void __i32_to_f128M( int32_t, float128_t * );
float16_t __i64_to_f16( int64_t );
float32_t __i64_to_f32( int64_t );
float64_t __i64_to_f64( int64_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t __i64_to_extF80( int64_t );
float128_t __i64_to_f128( int64_t );
#endif
void __i64_to_extF80M( int64_t, extFloat80_t * );
void __i64_to_f128M( int64_t, float128_t * );

/*----------------------------------------------------------------------------
| 16-bit (half-precision) floating-point operations.
*----------------------------------------------------------------------------*/
uint_fast32_t __f16_to_ui32( float16_t, uint_fast8_t, bool );
uint_fast64_t __f16_to_ui64( float16_t, uint_fast8_t, bool );
int_fast32_t __f16_to_i32( float16_t, uint_fast8_t, bool );
int_fast64_t __f16_to_i64( float16_t, uint_fast8_t, bool );
uint_fast32_t __f16_to_ui32_r_minMag( float16_t, bool );
uint_fast64_t __f16_to_ui64_r_minMag( float16_t, bool );
int_fast32_t __f16_to_i32_r_minMag( float16_t, bool );
int_fast64_t __f16_to_i64_r_minMag( float16_t, bool );
float32_t __f16_to_f32( float16_t );
float64_t __f16_to_f64( float16_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t __f16_to_extF80( float16_t );
float128_t __f16_to_f128( float16_t );
#endif
void __f16_to_extF80M( float16_t, extFloat80_t * );
void __f16_to_f128M( float16_t, float128_t * );
float16_t __f16_roundToInt( float16_t, uint_fast8_t, bool );
float16_t __f16_add( float16_t, float16_t );
float16_t __f16_sub( float16_t, float16_t );
float16_t __f16_mul( float16_t, float16_t );
float16_t __f16_mulAdd( float16_t, float16_t, float16_t );
float16_t __f16_div( float16_t, float16_t );
float16_t __f16_rem( float16_t, float16_t );
float16_t __f16_sqrt( float16_t );
bool __f16_eq( float16_t, float16_t );
bool __f16_le( float16_t, float16_t );
bool __f16_lt( float16_t, float16_t );
bool __f16_eq_signaling( float16_t, float16_t );
bool __f16_le_quiet( float16_t, float16_t );
bool __f16_lt_quiet( float16_t, float16_t );
bool __f16_isSignalingNaN( float16_t );

/*----------------------------------------------------------------------------
| 32-bit (single-precision) floating-point operations.
*----------------------------------------------------------------------------*/
uint_fast32_t __f32_to_ui32( float32_t, uint_fast8_t, bool );
uint_fast64_t __f32_to_ui64( float32_t, uint_fast8_t, bool );
int_fast32_t __f32_to_i32( float32_t, uint_fast8_t, bool );
int_fast64_t __f32_to_i64( float32_t, uint_fast8_t, bool );
uint_fast32_t __f32_to_ui32_r_minMag( float32_t, bool );
uint_fast64_t __f32_to_ui64_r_minMag( float32_t, bool );
int_fast32_t __f32_to_i32_r_minMag( float32_t, bool );
int_fast64_t __f32_to_i64_r_minMag( float32_t, bool );
float16_t __f32_to_f16( float32_t );
float64_t __f32_to_f64( float32_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t __f32_to_extF80( float32_t );
float128_t __f32_to_f128( float32_t );
#endif
void __f32_to_extF80M( float32_t, extFloat80_t * );
void __f32_to_f128M( float32_t, float128_t * );
float32_t __f32_roundToInt( float32_t, uint_fast8_t, bool );
float32_t __f32_add( float32_t, float32_t );
float32_t __f32_sub( float32_t, float32_t );
float32_t __f32_mul( float32_t, float32_t );
float32_t __f32_mulAdd( float32_t, float32_t, float32_t );
float32_t __f32_div( float32_t, float32_t );
float32_t __f32_rem( float32_t, float32_t );
float32_t __f32_sqrt( float32_t );
bool __f32_eq( float32_t, float32_t );
bool __f32_le( float32_t, float32_t );
bool __f32_lt( float32_t, float32_t );
bool __f32_eq_signaling( float32_t, float32_t );
bool __f32_le_quiet( float32_t, float32_t );
bool __f32_lt_quiet( float32_t, float32_t );
bool __f32_isSignalingNaN( float32_t );

/*----------------------------------------------------------------------------
| 64-bit (double-precision) floating-point operations.
*----------------------------------------------------------------------------*/
uint_fast32_t __f64_to_ui32( float64_t, uint_fast8_t, bool );
uint_fast64_t __f64_to_ui64( float64_t, uint_fast8_t, bool );
int_fast32_t __f64_to_i32( float64_t, uint_fast8_t, bool );
int_fast64_t __f64_to_i64( float64_t, uint_fast8_t, bool );
uint_fast32_t __f64_to_ui32_r_minMag( float64_t, bool );
uint_fast64_t __f64_to_ui64_r_minMag( float64_t, bool );
int_fast32_t __f64_to_i32_r_minMag( float64_t, bool );
int_fast64_t __f64_to_i64_r_minMag( float64_t, bool );
float16_t __f64_to_f16( float64_t );
float32_t __f64_to_f32( float64_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t __f64_to_extF80( float64_t );
float128_t __f64_to_f128( float64_t );
#endif
void __f64_to_extF80M( float64_t, extFloat80_t * );
void __f64_to_f128M( float64_t, float128_t * );
float64_t __f64_roundToInt( float64_t, uint_fast8_t, bool );
#if 0
float64_t __f64_add( float64_t, float64_t );
float64_t __f64_sub( float64_t, float64_t );
#endif
#if 0
float64_t __f64_mul( float64_t, const float64_t* );
float64_t __f64_div( float64_t, const float64_t* );
float64_t __f64_rem( float64_t, const float64_t* );
#else
float64_t __f64_mul( bool, float64_t, float64_t *__restrict );
float64_t __f64_div( bool, float64_t, float64_t *__restrict );
float64_t __f64_rem( bool, float64_t, float64_t *__restrict );
#endif
float64_t __f64_mulAdd( float64_t, float64_t, float64_t );
// float64_t __f64_sqrt( float64_t );
bool __f64_eq( float64_t, float64_t );
bool __f64_le( float64_t, float64_t );
bool __f64_lt( float64_t, float64_t );
bool __f64_eq_signaling( float64_t, float64_t );
bool __f64_le_quiet( float64_t, float64_t );
bool __f64_lt_quiet( float64_t, float64_t );
bool __f64_isSignalingNaN( float64_t );

/*----------------------------------------------------------------------------
| Rounding precision for 80-bit extended double-precision floating-point.
| Valid values are 32, 64, and 80.
*----------------------------------------------------------------------------*/
#if 0
extern THREAD_LOCAL uint_fast8_t extF80_roundingPrecision;
#else
#define extF80_roundingPrecision 80
#endif

/*----------------------------------------------------------------------------
| 80-bit extended double-precision floating-point operations.
*----------------------------------------------------------------------------*/
#ifdef SOFTFLOAT_FAST_INT64
uint_fast32_t __extF80_to_ui32( extFloat80_t, uint_fast8_t, bool );
uint_fast64_t __extF80_to_ui64( extFloat80_t, uint_fast8_t, bool );
int_fast32_t __extF80_to_i32( extFloat80_t, uint_fast8_t, bool );
int_fast64_t __extF80_to_i64( extFloat80_t, uint_fast8_t, bool );
uint_fast32_t __extF80_to_ui32_r_minMag( extFloat80_t, bool );
uint_fast64_t __extF80_to_ui64_r_minMag( extFloat80_t, bool );
int_fast32_t __extF80_to_i32_r_minMag( extFloat80_t, bool );
int_fast64_t __extF80_to_i64_r_minMag( extFloat80_t, bool );
float16_t __extF80_to_f16( extFloat80_t );
float32_t __extF80_to_f32( extFloat80_t );
float64_t __extF80_to_f64( extFloat80_t );
float128_t __extF80_to_f128( extFloat80_t );
extFloat80_t __extF80_roundToInt( extFloat80_t, uint_fast8_t, bool );
extFloat80_t __extF80_add( extFloat80_t, extFloat80_t );
extFloat80_t __extF80_sub( extFloat80_t, extFloat80_t );
extFloat80_t __extF80_mul( extFloat80_t, extFloat80_t );
extFloat80_t __extF80_div( extFloat80_t, extFloat80_t );
extFloat80_t __extF80_rem( extFloat80_t, extFloat80_t );
extFloat80_t __extF80_sqrt( extFloat80_t );
bool __extF80_eq( extFloat80_t, extFloat80_t );
bool __extF80_le( extFloat80_t, extFloat80_t );
bool __extF80_lt( extFloat80_t, extFloat80_t );
bool __extF80_eq_signaling( extFloat80_t, extFloat80_t );
bool __extF80_le_quiet( extFloat80_t, extFloat80_t );
bool __extF80_lt_quiet( extFloat80_t, extFloat80_t );
bool __extF80_isSignalingNaN( extFloat80_t );
#endif
uint_fast32_t __extF80M_to_ui32( const extFloat80_t *, uint_fast8_t, bool );
uint_fast64_t __extF80M_to_ui64( const extFloat80_t *, uint_fast8_t, bool );
int_fast32_t __extF80M_to_i32( const extFloat80_t *, uint_fast8_t, bool );
int_fast64_t __extF80M_to_i64( const extFloat80_t *, uint_fast8_t, bool );
uint_fast32_t __extF80M_to_ui32_r_minMag( const extFloat80_t *, bool );
uint_fast64_t __extF80M_to_ui64_r_minMag( const extFloat80_t *, bool );
int_fast32_t __extF80M_to_i32_r_minMag( const extFloat80_t *, bool );
int_fast64_t __extF80M_to_i64_r_minMag( const extFloat80_t *, bool );
float16_t __extF80M_to_f16( const extFloat80_t * );
float32_t __extF80M_to_f32( const extFloat80_t * );
float64_t __extF80M_to_f64( const extFloat80_t * );
void __extF80M_to_f128M( const extFloat80_t *, float128_t * );
void
 __extF80M_roundToInt(
     const extFloat80_t *, uint_fast8_t, bool, extFloat80_t * );
void __extF80M_add( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void __extF80M_sub( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void __extF80M_mul( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void __extF80M_div( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void __extF80M_rem( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void __extF80M_sqrt( const extFloat80_t *, extFloat80_t * );
bool __extF80M_eq( const extFloat80_t *, const extFloat80_t * );
bool __extF80M_le( const extFloat80_t *, const extFloat80_t * );
bool __extF80M_lt( const extFloat80_t *, const extFloat80_t * );
bool __extF80M_eq_signaling( const extFloat80_t *, const extFloat80_t * );
bool __extF80M_le_quiet( const extFloat80_t *, const extFloat80_t * );
bool __extF80M_lt_quiet( const extFloat80_t *, const extFloat80_t * );
bool __extF80M_isSignalingNaN( const extFloat80_t * );

/*----------------------------------------------------------------------------
| 128-bit (quadruple-precision) floating-point operations.
*----------------------------------------------------------------------------*/
#ifdef SOFTFLOAT_FAST_INT64
uint_fast32_t __f128_to_ui32( float128_t, uint_fast8_t, bool );
uint_fast64_t __f128_to_ui64( float128_t, uint_fast8_t, bool );
int_fast32_t __f128_to_i32( float128_t, uint_fast8_t, bool );
int_fast64_t __f128_to_i64( float128_t, uint_fast8_t, bool );
uint_fast32_t __f128_to_ui32_r_minMag( float128_t, bool );
uint_fast64_t __f128_to_ui64_r_minMag( float128_t, bool );
int_fast32_t __f128_to_i32_r_minMag( float128_t, bool );
int_fast64_t __f128_to_i64_r_minMag( float128_t, bool );
float16_t __f128_to_f16( float128_t );
float32_t __f128_to_f32( float128_t );
float64_t __f128_to_f64( float128_t );
extFloat80_t __f128_to_extF80( float128_t );
float128_t __f128_roundToInt( float128_t, uint_fast8_t, bool );
float128_t __f128_add( float128_t, float128_t );
float128_t __f128_sub( float128_t, float128_t );
float128_t __f128_mul( float128_t, float128_t );
float128_t __f128_mulAdd( float128_t, float128_t, float128_t );
float128_t __f128_div( float128_t, float128_t );
float128_t __f128_rem( float128_t, float128_t );
float128_t __f128_sqrt( float128_t );
bool __f128_eq( float128_t, float128_t );
bool __f128_le( float128_t, float128_t );
bool __f128_lt( float128_t, float128_t );
bool __f128_eq_signaling( float128_t, float128_t );
bool __f128_le_quiet( float128_t, float128_t );
bool __f128_lt_quiet( float128_t, float128_t );
bool __f128_isSignalingNaN( float128_t );
#endif
uint_fast32_t __f128M_to_ui32( const float128_t *, uint_fast8_t, bool );
uint_fast64_t __f128M_to_ui64( const float128_t *, uint_fast8_t, bool );
int_fast32_t __f128M_to_i32( const float128_t *, uint_fast8_t, bool );
int_fast64_t __f128M_to_i64( const float128_t *, uint_fast8_t, bool );
uint_fast32_t __f128M_to_ui32_r_minMag( const float128_t *, bool );
uint_fast64_t __f128M_to_ui64_r_minMag( const float128_t *, bool );
int_fast32_t __f128M_to_i32_r_minMag( const float128_t *, bool );
int_fast64_t __f128M_to_i64_r_minMag( const float128_t *, bool );
float16_t __f128M_to_f16( const float128_t * );
float32_t __f128M_to_f32( const float128_t * );
float64_t __f128M_to_f64( const float128_t * );
void __f128M_to_extF80M( const float128_t *, extFloat80_t * );
void __f128M_roundToInt( const float128_t *, uint_fast8_t, bool, float128_t * );
void __f128M_add( const float128_t *, const float128_t *, float128_t * );
void __f128M_sub( const float128_t *, const float128_t *, float128_t * );
void __f128M_mul( const float128_t *, const float128_t *, float128_t * );
void
 __f128M_mulAdd(
     const float128_t *, const float128_t *, const float128_t *, float128_t *
 );
void __f128M_div( const float128_t *, const float128_t *, float128_t * );
void __f128M_rem( const float128_t *, const float128_t *, float128_t * );
void __f128M_sqrt( const float128_t *, float128_t * );
bool __f128M_eq( const float128_t *, const float128_t * );
bool __f128M_le( const float128_t *, const float128_t * );
bool __f128M_lt( const float128_t *, const float128_t * );
bool __f128M_eq_signaling( const float128_t *, const float128_t * );
bool __f128M_le_quiet( const float128_t *, const float128_t * );
bool __f128M_lt_quiet( const float128_t *, const float128_t * );
bool __f128M_isSignalingNaN( const float128_t * );

#endif

