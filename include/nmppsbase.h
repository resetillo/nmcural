//  2017 Module. Basic Types and Macro Definitions


#ifndef __NMPPSBASE_H__
#define __NMPPSBASE_H__

#define NMPPS_PI    ( 3.14159265358979323846 )  /* ANSI C does not support M_PI */
#define NMPPS_2PI   ( 6.28318530717958647692 )  /* 2*pi                         */
#define NMPPS_PI2   ( 1.57079632679489661923 )  /* pi/2                         */
#define NMPPS_PI4   ( 0.78539816339744830961 )  /* pi/4                         */
#define NMPPS_PI180 ( 0.01745329251994329577 )  /* pi/180                       */
#define NMPPS_RPI   ( 0.31830988618379067154 )  /* 1/pi                         */
#define NMPPS_SQRT2 ( 1.41421356237309504880 )  /* sqrt(2)                      */
#define NMPPS_SQRT3 ( 1.73205080756887729353 )  /* sqrt(3)                      */
#define NMPPS_LN2   ( 0.69314718055994530942 )  /* ln(2)                        */
#define NMPPS_LN3   ( 1.09861228866810969139 )  /* ln(3)                        */
#define NMPPS_E     ( 2.71828182845904523536 )  /* e                            */
#define NMPPS_RE    ( 0.36787944117144232159 )  /* 1/e                          */
#define NMPPS_EPS23 ( 1.19209289e-07f )
#define NMPPS_EPS52 ( 2.2204460492503131e-016 )

#define NMPPS_MAX_8U     ( 0xFF )
#define NMPPS_MAX_16U    ( 0xFFFF )
#define NMPPS_MAX_32U    ( 0xFFFFFFFF )
#define NMPPS_MIN_8U     ( 0 )
#define NMPPS_MIN_16U    ( 0 )
#define NMPPS_MIN_32U    ( 0 )
#define NMPPS_MIN_8S     (-128 )
#define NMPPS_MAX_8S     ( 127 )
#define NMPPS_MIN_16S    (-32768 )
#define NMPPS_MAX_16S    ( 32767 )
#define NMPPS_MIN_32S    (-2147483647 - 1 )
#define NMPPS_MAX_32S    ( 2147483647 )
#define NMPPS_MIN_64U    ( 0 )

#if defined( _WIN32 ) || defined ( _WIN64 )
  #define NMPPS_MAX_64S  ( 9223372036854775807i64 )
  #define NMPPS_MIN_64S  (-9223372036854775807i64 - 1 )
  #define NMPPS_MAX_64U  ( 0xffffffffffffffffL ) /* 18446744073709551615 */
#else
  #define NMPPS_MAX_64S  ( 9223372036854775807LL )
  #define NMPPS_MIN_64S  (-9223372036854775807LL - 1 )
  #define NMPPS_MAX_64U  ( 0xffffffffffffffffLL ) /* 18446744073709551615 */
#endif

#define NMPPS_MINABS_32F ( 1.175494351e-38f )
#define NMPPS_MAXABS_32F ( 3.402823466e+38f )
#define NMPPS_EPS_32F    ( 1.192092890e-07f )
#define NMPPS_MINABS_64F ( 2.2250738585072014e-308 )
#define NMPPS_MAXABS_64F ( 1.7976931348623158e+308 )
#define NMPPS_EPS_64F    ( 2.2204460492503131e-016 )

#define NMPPS_MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define NMPPS_MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )

#define NMPPS_ABS( a ) ( ((a) < 0) ? (-(a)) : (a) )

typedef long long __INT64;
typedef long long __UINT64;

typedef unsigned char  nmpps8u;
typedef unsigned short nmpps16u;
typedef unsigned int   nmpps32u;
typedef signed char    nmpps8s;
typedef signed short   nmpps16s;
typedef signed int     nmpps32s;
typedef float          nmpps32f;
typedef __INT64        nmpps64s;
typedef __UINT64       nmpps64u;
typedef double         nmpps64f;
typedef nmpps16s       nmpps16f;

typedef struct {
    nmpps8s  re;
    nmpps8s  im;
} nmpps8sc;

typedef struct {
    nmpps16s  re;
    nmpps16s  im;
} nmpps16sc;

typedef struct {
    nmpps16u  re;
    nmpps16u  im;
} nmpps16uc;

typedef struct {
    nmpps32s  re;
    nmpps32s  im;
} nmpps32sc;

typedef struct {
    nmpps32f  re;
    nmpps32f  im;
} nmpps32fc;

typedef struct {
    nmpps64s  re;
    nmpps64s  im;
} nmpps64sc;

typedef struct {
    nmpps64f  re;
    nmpps64f  im;
} nmpps64fc;

/*typedef enum {
   nmppsUndef = -1,
   nmpps1u    =  0,
   nmpps8u    =  1,
   nmpps8uc   =  2,
   nmpps8s    =  3,
   nmpps8sc   =  4,
   nmpps16u   =  5,
   nmpps16uc  =  6,
   nmpps16s   =  7,
   nmpps16sc  =  8,
   nmpps32u   =  9,
   nmpps32uc  = 10,
   nmpps32s   = 11,
   nmpps32sc  = 12,
   nmpps32f   = 13,
   nmpps32fc  = 14,
   nmpps64u   = 15,
   nmpps64uc  = 16,
   nmpps64s   = 17,
   nmpps64sc  = 18,
   nmpps64f   = 19,
   nmpps64fc  = 20
} nmppsDataType;*/

typedef enum { 
    nmppsFalse = 0, 
    nmppsTrue = 1 
} nmppsBool;


#endif /* __NMPPSBASE_H__ */

