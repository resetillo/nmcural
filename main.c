#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"

int change_nan(double *pSrc, double *pDst, double NANchange,  int len);
int change_infinity(double *pSrc, double *pDst, double INFchange,  int len);

float one_sqrtf(float arg);


int main(){
	int res = 0;
	/*float vec[32] = {1.0/0.0, 0.0/0.0, 0.09,0.04,1600,0.16,36,6400,
						 0.64,2500,0.25,100,0.0001,4096,8192,16384,
						 32768,65536,131072,262144,524288,1048576,2097152,4194304
						 -1,-2,-4,-8,-16,-32,-64,-1.0/0.0, -0.0/0.0};
	float result[32];
	int itmp;
	float dtmp;
	dtmp = one_sqrtf(vec[3]);
	GET_FLOAT_WORD(itmp,dtmp);
	int* ptr1 = (int*) vec;
	int* ptr2 = (int*) result;
	//res = nmppsSqrt_32f(vec, result, 32);*/
	//res = nmppsArctan_64f(vec, result, 32);
	//TMP_SQRT(vec, result, 32);
	//res = change_nan(vec,  result, 0.7777,  32);
	//res = change_infinity(vec,  result, 0.3333,  32);
	//res = test_sqrt();
	 res = test_sqrtf();
	// res += test_atan();
	// res = test_atanf();
	// res = test_copysign();
	if (res){
		printf("ERROR TEST is %i", res);
	}
	else {
		printf("TEST SUCCEFUL");
	}
	return res;
}
