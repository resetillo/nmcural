#include "nmpps.h"

int change_nan(double *pSrc, double *pDst, double NANchange,  int len);
int change_infinity(double *pSrc, double *pDst, double INFchange,  int len);

int main(){
	int res = 0;
	/*double vec[32] = {1.0/0.0, 0.0/0.0, 0.09,0.04,1600,0.16,36,6400,
						 0.64,2500,0.25,100,0.0001,4096,8192,16384,
						 32768,65536,131072,262144,524288,1048576,2097152,4194304
						 -1,-2,-4,-8,-16,-32,-64,-1.0/0.0, -0.0/0.0};
	double result[32];*/
	//res = nmppsSqrt_64f(vec, result, 32);
	//res = nmppsArctan_64f(vec, result, 32);
	//TMP_SQRT(vec, result, 32);
	//res = change_nan(vec,  result, 0.7777,  32);
	//res = change_infinity(vec,  result, 0.3333,  32);
	res = test_srqt();
	// res = test_srqtf();
	 res += test_atan();
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
