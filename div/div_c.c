//#include "nmpps.h"
//#include "stdlib.h"
//#include "math.h"
#include "stdio.h"


/**
 * @brief Г‚Г»Г·ГЁГ±Г«ГҐГ­ГЁГҐ ГЄГўГ Г¤Г°Г ГІГ­Г®ГЈГ® ГЄГ®Г°Г­Гї
 *
 * Г€Г±ГЇГ®Г«ГјГ§ГіГҐГІГ±Гї ГЁГІГҐГ°Г Г¶ГЁГ®Г­Г­Г»Г© Г Г«ГЈГ®Г°ГЁГІГ¬ ГѓГҐГ°Г®Г­Г 
 * lim x = sqrt(a)
 * x(n+1) = 0.5*(x(n) + a/x(n))
 * @note Г”ГіГ­ГЄГ¶ГЁГї Г­ГҐ ГЇГ°ГҐГ¤Г­Г Г§Г­Г Г·ГҐГ­Г  Г¤Г«Гї Г°Г ГЎГ®ГІГ» Г± Г¤ГҐГ­Г®Г°Г¬Г Г«ГЁГ§Г®ГўГ Г­Г­Г»Г¬ГЁ Г·ГЁГ±Г«Г Г¬ГЁ (Г§Г  ГЁГ±ГЄГ«ГѕГ·ГҐГ­ГЁГҐГ¬ +0/-0)
 *		 ГЏГ®ГЈГ°ГҐГёГ­Г®Г±ГІГј Г­ГҐ ГЇГ°ГҐГўГ»ГёГ ГҐГІ 10E-14% Г®ГІ Г°ГҐГ§ГіГ«ГјГІГ ГІГ 
 * @param arg Г‚ГµГ®Г¤Г­Г®ГҐ Г·ГЁГ±Г«Г®
 * @return ГЄГўГ Г¤Г°Г ГІГ­Г»Г© ГЄГ®Г°ГҐГ­Гј ГЁГ§ Г·ГЁГ±Г«Г 
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

	// РџРѕРёСЃРє РјР°РєСЃРёРјР°Р»СЊРЅРѕРіРѕ РЅРµРїСЂРµРІС‹С€Р°СЋС‰РµРіРѕ
	if (arg < 1.0) {
		flag = 1;
		step = 2.0;
	} else {
		flag = 0;
		step = 0.5;
	}

	// РЎР°Рј РїРѕРёСЃРє
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

	// Р�С‚РµСЂР°С†РёСЏ
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

int __main(){
	double f = 3.1416;
	double g;
	g = obr(f);
	//return g;
	return 100;
}


