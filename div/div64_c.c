#include "nmpps.h"
#include "stdlib.h"
#include "math.h"

typedef union {
	double dbl;
	long long i64;
	unsigned long long ui64;
	int i32[2];
	unsigned int ui32[2];
} dblint_t;

double one_divide(double a, double b) {
	dblint_t ipb;
	double ret;

	if (isnan(a) || isnan(b)) {
		return copysign(NAN, a*b);
	}
	if (fabs(b)==0) {
		if (fabs(a) == 0) {
			return copysign(NAN, a*b);
		}
		return copysign(INFINITY, a*b);
	}
	if (isinf(b)) {
		if (isinf(a) == 0) {
			return copysign(NAN, a*b);
		}
		return copysign(0, a*b); //Любое число, деленное на бесконечность - равно 0
	}
	if (isinf(a)) {
		return copysign(INFINITY, a*b);
	}

	ipb.dbl = b;

	//Рассчитаем приближенное значение B0 ~ 1/B0 для первой итерации
	//Для этого надо изменить "знак" экспоненты,
	//суть есть преобразовать экспоненту в доп.код
	ipb.ui32[1] = ~ipb.ui32[1] - 0x80200000;
	//Уточним значение
	ipb.dbl = (2.0 - ipb.dbl*b)*ipb.dbl;
	ipb.dbl = (2.0 - ipb.dbl*b)*ipb.dbl;
	ipb.dbl = (2.0 - ipb.dbl*b)*ipb.dbl;
	ipb.dbl = (2.0 - ipb.dbl*b)*ipb.dbl;
	ipb.dbl = (2.0 - ipb.dbl*b)*ipb.dbl;
	ipb.dbl = (2.0 - ipb.dbl*b)*ipb.dbl;


	ret = ipb.dbl*a;

	return ret;

}


nmppsStatus c_nmppsDiv_64f(const nmpps64f*  pDivided, const nmpps64f*  pDivisor, nmpps64f*  pDst,    int len){

    nmppsStatus ret = nmppsStsNoErr;
    int i = 0;
    if (pDivided == NULL || pDivisor == NULL || pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;
    for (i=0;i<len;i++) {
        pDst[i] = one_divide(pDivided[i], pDivisor[i]);
        if (fabs(pDivisor[i]) == 0.0L) ret = nmppsStsDivByZeroErr;
    }
    return ret;
}












