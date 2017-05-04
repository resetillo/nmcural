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
 * @brief ���������� ����������� �����
 *
 * ������������ ������������ �������� ������
 * lim x = sqrt(a)
 * x(n+1) = 0.5*(x(n) + a/x(n))
 * @note ������� �� ������������� ��� ������ � ������������������ ������� (�� ����������� +0/-0)
 *		 ����������� �� ��������� 10E-14% �� ����������
 * @param arg ������� �����
 * @return ���������� ������ �� �����
 * */
double one_sqrt(double arg){
	dblint_t X, Y;

	if (arg<0) return NAN;
	if (!isnormal(arg)) return arg;

	X.dbl = arg;
	//���������� ������������ �������� X0 ~ sqrt(A) ��� ������ ��������
	//��� ����� ���������� �������� ���������� �� 2 (�������� �� 2)
	X.ui32[1] -= 0x3ff00000; //�������� BIAS - �������� ���������� �������� IEEE
	X.ui32[1] >>= 1;
	X.ui32[1] += 0x3ff00000;
	X.ui32[1] &= 0x7fffffff;//��������� �� �����

	//���������� ������������ �������� Y0 ~ 1/X0 ��� ������ ��������
	//��� ����� ���� �������� "����" ����������,
	//���� ���� ������������� ���������� � ���.���
	Y.ui32[0] = X.ui32[0];
	Y.ui32[1] = ~X.ui32[1] - 0x80200000;
	//������� ��������
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//������ ��������
	//X1 = 0.5*(X0 + A*Y0)
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	//������� �������� Y1 = 1/X1
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//������ ��������
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//3� ��������
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;
	Y.dbl = (2.0 - X.dbl*Y.dbl)*Y.dbl;

	//4� ��������
	X.dbl = 0.5*(X.dbl + arg*Y.dbl);
	//��� 52-������ �������� ������� double �������� 4� �������� ������ �������

	return X.dbl;
}


typedef union {
	float flt;
	int i32;
	unsigned int ui32;
} fltint_t;


/**
 * @brief ���������� ����������� �����
 *
 * ������������ ������������ �������� ������
 * lim x = sqrt(a)
 * x(n+1) = 0.5*(x(n) + a/x(n))
 * @note ������� �� ������������� ��� ������ � ������������������ ������� (�� ����������� +0/-0)
 *		 ����������� �� ��������� ???% �� ����������
 * @param arg ������� �����
 * @return ���������� ������ �� �����
 * */
float one_sqrtf(float arg){
	fltint_t X, Y;

	if (arg<0) return NAN;
	if (!isnormal(arg)) return arg;

	X.flt = arg;
	//���������� ������������ �������� X0 ~ sqrt(A) ��� ������ ��������
	//��� ����� ���������� �������� ���������� �� 2 (�������� �� 2)
	X.ui32 -= 0x3f800000; //�������� BIAS - �������� ���������� �������� IEEE
	X.ui32 >>= 1;
	X.ui32 += 0x3f800000;
	X.ui32 &= 0x7fffffff;//��������� �� �����

	//���������� ������������ �������� Y0 ~ 1/X0 ��� ������ ��������
	//��� ����� ���� �������� "����" ����������,
	//���� ���� ������������� ���������� � ���.���
	Y.ui32 = ~X.ui32 - 0x81000000;
	//������� ��������
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//������ ��������
	//X1 = 0.5*(X0 + A*Y0)
	X.flt = 0.5*(X.flt + arg*Y.flt);
	//������� �������� Y1 = 1/X1
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//������ ��������
	X.flt = 0.5*(X.flt + arg*Y.flt);
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//3� ��������
	X.flt = 0.5*(X.flt + arg*Y.flt);
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;
	Y.flt = (2.0 - X.flt*Y.flt)*Y.flt;

	//4� ��������
	X.flt = 0.5*(X.flt + arg*Y.flt);
	//��� 52-������ �������� ������� double �������� 4� �������� ������ �������

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




