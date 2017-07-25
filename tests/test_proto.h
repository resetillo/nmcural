
#ifndef __NMPPS_PROTO_TESTS_H__
#define __NMPPS_PROTO_TESTS_H__

int test_copysign();
int test_vec_handler32();



typedef union {
	double dbl;
	long long i64;
	unsigned long long ui64;
	int i32[2];
	unsigned int ui32[2];
} dblint_t;

typedef union {
	float flt;
	int i32;
	unsigned int ui32;
} fltint_t;

#endif /* __NMPPS_PROTO_TESTS_H__ */

