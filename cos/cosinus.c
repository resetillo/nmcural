
#include "math.h"
#include "nmpps.h"

nmppsStatus nmppsCosinus_32f(const nmpps32f* pSrc, nmpps32f* pDst, int len){
	float dtmp;

	if (len < 1) return nmppsStsSizeErr;
	if (pSrc == NULL || pDst == NULL) return nmppsStsNullPtrErr;

	while (len-- > 0) {
		dtmp = *pSrc++;
		dtmp = cos(dtmp);
		*pDst++ = dtmp;
	}
	return nmppsStsNoErr;
}
