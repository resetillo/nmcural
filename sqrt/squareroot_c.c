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


/**
 * @brief Вычисление квадратного корня
 *
 * Используется итерационный алгоритм Герона
 * lim x = sqrt(a)
 * x(n+1) = 0.5*(x(n) + a/x(n))
 * @note Функция не предназначена для работы с денормализованными числами (за исключением +0/-0)
 *		 Погрешность не превышает 10E-14% от результата
 * @param arg Входное число
 * @return квадратный корень из числа
 * */
double one_sqrt(double arg){
	dblint_t X, Y;

	if (arg<0) return NAN;
	if (!isnormal(arg)) return arg;

	X.dbl = arg;
	//Рассчитаем приближенное значение X0 ~ sqrt(A) для первой итерации
	//Для этого необходимо сдвинуть экспоненту на 2 (поделить на 2)
	X.ui32[1] -= 0x3ff00000; //Вычитаем BIAS - смещение экспоненты согласно IEEE
	X.ui32[1] >>= 1;
	X.ui32[1] += 0x3ff00000;
	X.ui32[1] &= 0x7fffffff;//Избавимся от знака

	//Рассчитаем приближенное значение Y0 ~ 1/X0 для первой итерации
	//Для этого надо изменить "знак" экспоненты,
	//суть есть преобразовать экспоненту в доп.код
	Y.ui32[0] = X.ui32[0];
	Y.ui32[1] = ~X.ui32[1] - 0x80200000;
	//Уточним значение
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//Первая итерация
	//X1 = 0.5*(X0 + A*Y0)
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	//Уточним значение Y1 = 1/X1
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//Вторая итерация
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//3я итерация
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//4я итерация
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	//Для 52-битной мантиссы формата double точности 4х итераций должно хватить

	return X.dbl;
}


typedef union {
	float flt;
	int i32;
	unsigned int ui32;
} fltint_t;


/**
 * @brief Вычисление квадратного корня
 *
 * Используется итерационный алгоритм Герона
 * lim x = sqrt(a)
 * x(n+1) = 0.5*(x(n) + a/x(n))
 * @note Функция не предназначена для работы с денормализованными числами (за исключением +0/-0)
 *		 Погрешность не превышает ???% от результата
 * @param arg Входное число
 * @return квадратный корень из числа
 * */
float one_sqrtf(float arg){
	fltint_t X, Y;

	if (arg<0) return NAN;
	if (!isnormal(arg)) return arg;

	X.flt = arg;
	//Рассчитаем приближенное значение X0 ~ sqrt(A) для первой итерации
	//Для этого необходимо сдвинуть экспоненту на 2 (поделить на 2)
	X.ui32 -= 0x3f800000; //Вычитаем BIAS - смещение экспоненты согласно IEEE
	X.ui32 >>= 1;
	X.ui32 += 0x3f800000;
	X.ui32 &= 0x7fffffff;//Избавимся от знака

	//Рассчитаем приближенное значение Y0 ~ 1/X0 для первой итерации
	//Для этого надо изменить "знак" экспоненты,
	//суть есть преобразовать экспоненту в доп.код
	Y.ui32 = ~X.ui32 - 0x81000000;
	//Уточним значение
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//Первая итерация
	//X1 = 0.5*(X0 + A*Y0)
	X.flt = 0.5*(X.flt + arg*Y.flt);
	//Уточним значение Y1 = 1/X1
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//Вторая итерация
	X.flt = 0.5*(X.flt + arg*Y.flt);
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//3я итерация
	X.flt = 0.5*(X.flt + arg*Y.flt);
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//4я итерация
	X.flt = 0.5*(X.flt + arg*Y.flt);
	//Для 52-битной мантиссы формата double точности 4х итераций должно хватить

	return X.flt;
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


nmppsStatus c_nmppsSqrt_32f (const nmpps32f*  pSrc, nmpps32f*  pDst,    int len){
    nmppsStatus ret = nmppsStsNoErr;
    int i = 0;
    if (pSrc == NULL || pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;
    for (i=0;i<len;i++) {
        pDst[i] = one_sqrtf(pSrc[i]);
        if (pSrc[i] < 0) ret = nmppsStsSqrtNegArg;
    }
    return ret;
}




