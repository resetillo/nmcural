#include "nmpps.h"
#include "stdlib.h"
#include "math.h"
#include "tests/test_math.h"


/**
 * @brief ����������� ������ ��� ��������
 *
 * � ������ pDst ������������ �������� pDataSrc, �� �� ������ ��� � pSignSrc
 *
 * @param pSignSrc ������, �� �������� ���������� �����
 * @param pDataSrc ������, �� �������� ���������� ��������
 * @param pDst ������ c �������� �����������
 *
 * @ret #nmppsStsNoErr ������������� ���������
 * @ret #nmppsStsSizeErr ��������������� ����� �������
 * @ret #nmppsStsNullPtrErr ������������ ���������
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
 * @brief ����������� NAN �� ������� � ������
 *
 * � ������ pDst ������������ �������� �� pNANSrc, ���� ��� NAN
 *
 * @param pNANSrc ������, �� �������� ���������� NAN
 * @param pDst ������ c �������� �����������
 *
 * @ret #nmppsStsNoErr ������������� ���������
 * @ret #nmppsStsSizeErr ��������������� ����� �������
 * @ret #nmppsStsNullPtrErr ������������ ���������
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
 * @brief ����������� INF �� ������� � ������
 *
 * � ������ pDst ������������ �������� �� pINFSrc, ���� ��� INF
 *
 * @param pINFSrc ������, �� �������� ���������� NAN
 * @param pDst ������ c �������� �����������
 *
 * @ret #nmppsStsNoErr ������������� ���������
 * @ret #nmppsStsSizeErr ��������������� ����� �������
 * @ret #nmppsStsNullPtrErr ������������ ���������
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
		//��������� �������� �������
		GET_HIGH_WORD(w, data_arg);
		SET_HIGH_WORD(ret, w|0x80000000);
	}
	else {
		//����� �������� �������
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
		//��������� �������� �������
		GET_FLOAT_WORD(w, data_arg);
		SET_FLOAT_WORD(ret, w|0x80000000);
	}
	else {
		//����� �������� �������
		GET_FLOAT_WORD(w, data_arg);
		SET_FLOAT_WORD(ret, w&0x7FFFFFFF);
	}
	return ret;
}

