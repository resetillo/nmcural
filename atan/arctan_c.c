#include "nmpps.h"
#include "tests/test_math.h"



extern nmpps64f tanTable[52];
extern nmpps64f angTable[52];

extern nmpps32f tanTableF[23];
extern nmpps32f angTableF[23];


/*
#include "math.h"
void init_atan(){
	int i;
	double angle = 3.1415926535897932384626433832795L /  2.0L;
	for (i =0; i<52;i++){
		angle = angle / 2.0L;
		angTable[i] = angle;
		tanTable[i] = tan(angle);
	}
}
*/

nmpps64f arctan2(nmpps64f x, nmpps64f y){
    nmpps64f sum_angle = 0;
    nmpps64f Xnew = x;
    nmpps64f Ynew = y;
    int i = 0;
    nmpps64f a, t, s;
    for(i=0; i < sizeof(tanTable)/sizeof(nmpps64f); i++){
        a = angTable[i];
        t = tanTable[i];
        s = copysign(1, y);
        Xnew = x + s*y*t;
        Ynew = y - s*x*t;
        sum_angle = sum_angle + s*a;
    
                
        x =  Xnew;
        y =  Ynew;      
    }
    return sum_angle;
}




nmpps32f arctan2f(nmpps32f x, nmpps32f y){
    nmpps32f sum_angle = 0;
    nmpps32f Xnew = x;
    nmpps32f Ynew = y;
    int i = 0;
    nmpps32f a, t, s;
    for(i=0; i < sizeof(tanTableF)/sizeof(nmpps32f); i++){
        a = angTableF[i];
        t = tanTableF[i];
        s = copysignf(1, y);
        Xnew = x + s*y*t;
        Ynew = y - s*x*t;
        sum_angle = sum_angle + s*a;
    
                
        x =  Xnew;
        y =  Ynew;      
    }
    return sum_angle;
}


/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsArctan
//
//  Purpose: compute arctangent value for all elements of the source vector
//
//  Return:
//   stsNoErr           Ok
//   stsNullPtrErr      Some of pointers to input or output data are NULL
//   stsSizeErr      The length of the arrays is less or equal zero
//
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                a length of the array
//
*/
nmppsStatus c_nmppsArctan_64f(const nmpps64f* pSrc, nmpps64f* pDst,    int len){
    int i = 0;
    nmpps64f tmp;
    if (pSrc == NULL || pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;

    for(i=0; i < len; i++){
        tmp = fabs(pSrc[i]);
        pDst[i] = arctan2(1.0, tmp);
        //����������� ����
        pDst[i] = copysign(pDst[i], pSrc[i]);
    }
    
    return nmppsStsNoErr;
}

nmppsStatus nmppsArctan_32f(const nmpps32f* pSrc, nmpps32f* pDst,    int len){
    int i = 0;
    nmpps32f tmp;
    if (pSrc == NULL || pDst == NULL) return nmppsStsNullPtrErr;
    if (len<=0) return nmppsStsSizeErr;

    for(i=0; i < len; i++){
        tmp = fabsf(pSrc[i]);
        pDst[i] = arctan2(1.0, tmp);
        //����������� ����
        pDst[i] = copysignf(pDst[i], pSrc[i]);
    }
    
    return nmppsStsNoErr;
}



