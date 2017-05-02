#include "nmpps.h"
#include "stdlib.h"
#include "math.h"
#include "tests\test_math.h"


/**
 * @brief Копирование знаков для векторов
 *
 * В вектор pDst записываются значения pDataSrc, но со знаком как у pSignSrc
 *
 * @param pSignSrc вектор, из которого копируются знаки
 * @param pDataSrc вектор, из которого копируются значения
 * @param pDst вектор c выходным результатом
 *
 * @ret #nmppsStsNoErr Положительный результат
 * @ret #nmppsStsSizeErr Неположительная длина вектора
 * @ret #nmppsStsNullPtrErr Некорректный указатель
 *
 * */
nmppsStatus  nmppsCopySign_64f(const nmpps64f* pSignSrc, const  nmpps64f* pDataSrc, nmpps64f* pDst, int len){
	int i;
    if (pSignSrc == NULL || pDataSrc == NULL ||  pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;
	for (i=0; i < len;i++){
		 pDst[i] = copysign(pDataSrc[i], pSignSrc[i]);
	}
    return nmppsStsNoErr;
}


/**
 * @brief Копирование NAN из вектора в вектор
 *
 * В вектор pDst записываются значения из pNANSrc, если это NAN
 *
 * @param pNANSrc вектор, из которого копируются NAN
 * @param pDst вектор c выходным результатом
 *
 * @ret #nmppsStsNoErr Положительный результат
 * @ret #nmppsStsSizeErr Неположительная длина вектора
 * @ret #nmppsStsNullPtrErr Некорректный указатель
 *
 * */
nmppsStatus  nmppsCopyNAN_64f(const nmpps64f* pNANSrc, nmpps64f* pDst, int len){
	int i, hi, low;
    if (pNANSrc == NULL || pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;
	for (i=0; i < len;i++){
		GET_HIGH_WORD(hi,pNANSrc[i]);
		if (hi & 0x7FF00000){
			GET_LOW_WORD(low,pNANSrc[i]);
			if (hi - 0x7FF00000 > 0 || low > 0){
				pDst[i] =  pNANSrc[i];
			}
		}
	}
    return nmppsStsNoErr;
}


/**
 * @brief Копирование INF из вектора в вектор
 *
 * В вектор pDst записываются значения из pINFSrc, если это INF
 *
 * @param pINFSrc вектор, из которого копируются NAN
 * @param pDst вектор c выходным результатом
 *
 * @ret #nmppsStsNoErr Положительный результат
 * @ret #nmppsStsSizeErr Неположительная длина вектора
 * @ret #nmppsStsNullPtrErr Некорректный указатель
 *
 * */
nmppsStatus  nmppsCopyINF_64f(const nmpps64f* pINFSrc, nmpps64f* pDst, int len){
	int i, hi, low;
    if (pINFSrc == NULL || pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;
	for (i=0; i < len;i++){
		GET_HIGH_WORD(hi,pINFSrc[i]);
		if (hi & 0x7FF00000){
			GET_LOW_WORD(low,pINFSrc[i]);
			if (hi - 0x7FF00000 == 0 && low == 0){
				pDst[i] =  pINFSrc[i];
			}
		}
	}
    return nmppsStsNoErr;
}

double fabs(const double x){
	double ret = x;
	int tmp;
	GET_HIGH_WORD(tmp,ret);
	tmp &=  0x7FFFFFFF;
	SET_HIGH_WORD(ret,tmp);
	return ret;
}

float fabsf(const float x){
	float ret = x;
	int tmp;
	GET_FLOAT_WORD(tmp, ret);
	tmp &=  0x7FFFFFFF;
	SET_FLOAT_WORD(ret,tmp);
	return ret;
}

double copysign(const double data_arg, const double sign_arg){
	int s, w;
	double ret = data_arg;
	GET_HIGH_WORD(s, sign_arg);
	s &=  0x80000000;
	if (s){
		//Установка старшего разряда
		GET_HIGH_WORD(w, data_arg);
		SET_HIGH_WORD(ret, w|0x80000000);
	}
	else {
		//Сброс старшего разряда
		GET_HIGH_WORD(w, data_arg);
		SET_HIGH_WORD(ret, w&0x7FFFFFFF);
	}
	return ret;
}


float copysignf(const float data_arg, const float sign_arg){
	int s, w;
	float ret = data_arg;
	GET_FLOAT_WORD(s, sign_arg);
	s &=  0x80000000;
	if (s){
		//Установка старшего разряда
		GET_FLOAT_WORD(w, data_arg);
		SET_FLOAT_WORD(ret, w|0x80000000);
	}
	else {
		//Сброс старшего разряда
		GET_FLOAT_WORD(w, data_arg);
		SET_FLOAT_WORD(ret, w&0x7FFFFFFF);
	}
	return ret;
}

