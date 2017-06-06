//#include "nmpps.h"
//#include "stdlib.h"
//#include "math.h"
#include "stdio.h"


/**
 * @brief Âû÷èñëåíèå êâàäðàòíîãî êîðíÿ
 *
 * Èñïîëüçóåòñÿ èòåðàöèîííûé àëãîðèòì Ãåðîíà
 * lim x = sqrt(a)
 * x(n+1) = 0.5*(x(n) + a/x(n))
 * @note Ôóíêöèÿ íå ïðåäíàçíà÷åíà äëÿ ðàáîòû ñ äåíîðìàëèçîâàííûìè ÷èñëàìè (çà èñêëþ÷åíèåì +0/-0)
 *		 Ïîãðåøíîñòü íå ïðåâûøàåò 10E-14% îò ðåçóëüòàòà
 * @param arg Âõîäíîå ÷èñëî
 * @return êâàäðàòíûé êîðåíü èç ÷èñëà
 * */
double obr(double arg){
	//dblint_t X, Y;
	//return arg;
	//printf('start');
	int flag;
 	double step;
	int t;

	if (arg<0) {
		return -1;  // NAN
	}
	t = 1;
	    
	// step = None

	// Поиск максимального непревышающего
	if (arg < 1.0) {
		flag = 1;
		step = 2.0;
	} else {
		flag = 0;
		step = 0.5;
	}

	// Сам поиск
	printf("Result: %lf\n", t);
	while (1) {
		printf("Resultee: %lf\n", t);
		double new = t * step;
		printf("Resultee2: %lf\n", new);
		double x = new * arg;
		printf("Resultee3: %lf\n", x);
		if ((flag) && (x > 1)) {
		    break;
		} else if ((!flag) && (x < arg)) {
		    t = new;
		    break;
		}
		t = new;
	}

	// Итерация
	double ret = 0;
	double chunk = arg;
	double last_chunk = 2*arg;
	double mul_result = 1.0;
	while (last_chunk - chunk > 0) {
		double mul = arg * chunk;
		if (mul > mul_result) {
		    ;
		} else {
		    mul_result -= mul;
		    ret += chunk;
		}

		last_chunk = chunk;
		chunk = chunk / 2.0;
	}

	printf("Return %lf\n", ret);

	return ret;
}


/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsSqrt
//  Purpose:    compute square root value for every element of the source vector
//   pSrc                 pointer to the source vector
//   pDst                 pointer to the destination vector
//   pSrcDst              pointer to the source/destination vector
//   len                  length of the vector(s), number of items
//   scaleFactor          scale factor value
//  Return:
//   nmppsStsNullPtrErr        pointer to vector is NULL
//   nmppsStsSizeErr           length of the vector is less or equal zero
//   nmppsStsSqrtNegArg        negative value in real sequence
//   nmppsStsNoErr             otherwise
*/
/*
nmppsStatus c_nmppsSqrt_64f (const nmpps64f*  pSrc, nmpps64f*  pDst,    int len){
    nmppsStatus ret = nmppsStsNoErr;
    int i = 0;
    if (pSrc == NULL || pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;
    for (i=0;i<len;i++) {
        pDst[i] = one_sqrt(pSrc[i]);
        if (pSrc[i] < 0) ret = nmppsStsSqrtNegArg;
    }
    return ret;
}
*/

int main(){
	double f = 3.1416;
	double g;
	g = obr(f);
	//return g;
	return 100;
}


