
#ifndef __NMPPS_MATH_TESTS_H__
#define __NMPPS_MATH_TESTS_H__

typedef unsigned char u_int8_t;
typedef unsigned short int u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned int __uint32_t;
typedef int __int32_t;
typedef int int32_t;


#define _PI 3.1415926535897932384626433832795
#define K1_360  0.0027777777777777777777777777777778
#define PIDEL180    0.017453292519943295769236907684886

#define DEG_TO_RAD(rad,deg)       \
do{                               \
  (rad) = (deg) * (_PI / 180);    \
}while(0)


typedef union
{
  double value;
  struct
  {
    u_int32_t lsw;
    u_int32_t msw;
  } parts;
} ieee_double_shape_type;

typedef union
{
  float value;
  u_int32_t word;
} ieee_float_shape_type;

/*[макрос для определения размера массива в словах]*/
#define _GET_SIZE_WORD(mas_point, size)\
        size = sizeof((mas_point)) / 4; \
        
/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)          \
do {                \
  ieee_double_shape_type gh_u;          \
  gh_u.value = (d);           \
  (i) = gh_u.parts.msw;           \
} while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)         \
do {                \
  ieee_double_shape_type iw_u;          \
  iw_u.parts.msw = (ix0);         \
  iw_u.parts.lsw = (ix1);         \
  (d) = iw_u.value;           \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)         \
do {                \
  ieee_double_shape_type sl_u;          \
  sl_u.value = (d);           \
  sl_u.parts.lsw = (v);           \
  (d) = sl_u.value;           \
} while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)         \
do {                \
  ieee_double_shape_type gl_u;          \
  gl_u.value = (d);           \
  (i) = gl_u.parts.lsw;           \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)          \
do {                \
  ieee_double_shape_type sh_u;          \
  sh_u.value = (d);           \
  sh_u.parts.msw = (v);           \
  (d) = sh_u.value;           \
} while (0)

#define EXTRACT_WORDS(ix0,ix1,d)        \
do {                \
  ieee_double_shape_type ew_u;          \
  ew_u.value = (d);           \
  (ix0) = ew_u.parts.msw;         \
  (ix1) = ew_u.parts.lsw;         \
} while (0)


/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i,d)         \
do {                \
  ieee_float_shape_type gf_u;         \
  gf_u.value = (d);           \
  (i) = gf_u.word;            \
} while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)         \
do {                \
  ieee_float_shape_type sf_u;         \
  sf_u.word = (i);            \
  (d) = sf_u.value;           \
} while (0)

#define FLT_UWORD_MAX 0x7fffffff
#define FLT_UWORD_IS_FINITE(x) ((x)<0x7f800000L) 
#define FLT_UWORD_IS_ZERO(x) ((x)==0)
#define FLT_UWORD_IS_SUBNORMAL(x) ((x)<0x00800000L)
#define FLT_UWORD_MIN 0x00000001
#define FLT_UWORD_EXP_MIN 0x43160000
#define FLT_UWORD_LOG_MIN 0x42cff1b5
#define FLT_SMALLEST_EXP -22
#define FLT_UWORD_EXP_MAX 0x43000000
#define FLT_UWORD_IS_NAN(x) ((x)>0x7f800000L)
#define FLT_UWORD_IS_INFINITE(x) ((x)==0x7f800000L)
#define FLT_LARGEST_EXP (FLT_UWORD_MAX>>23)
#define FLT_UWORD_LOG_2MAX 0x42b437e0
#define FLT_UWORD_LOG_MAX 0x42b2d4fc

double fabs(const double x);
float fabsf(const float x);
double copysign(const double data_arg, const double sign_arg);
float copysignf(const float data_arg, const float sign_arg);

#ifndef NULL
	#define NULL ((void *)0)
#endif

#endif /* __NMPPS_MATH_TESTS_H__ */

