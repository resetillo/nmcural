
#ifndef __NMPPS_PROTO_TESTS_H__
#define __NMPPS_PROTO_TESTS_H__


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


#define DivTestEnable 1
#define AtanTestEnable 1
#define SqrtTestEnable 1
#define NormalizeTestEnable 1
#define NormTestEnable 1

#if NormTestEnable
	#define NormInfTestEnable 1
	#define NormL1TestEnable 1
	#define NormL2TestEnable 1

    #define NormDiffInfTestEnable 1
    #define NormDiffL1TestEnable 1
    #define NormDiffL2TestEnable 1
#endif



#endif /* __NMPPS_PROTO_TESTS_H__ */

