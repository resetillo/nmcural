#include <nmpps_asm_defs.h>

.global _nmppsNormDiff_L1_16s32s_Sfs

.global normDiff_L1_16s32s_Sfs
.global normDiff_L1_16s32f
.global scale_f64

.text




/*
	ar0 - input1 adr
	ar1 - input2 adr
	ar2 - output adr
	gr0 - len
	gr1 - scaleFactor
*/
normDiff_L1_16s32s_Sfs:
	push ar0, gr0;
	push ar2, gr2;
	push ar4, gr4;

	ar4 = ar7 + 2;
	ar7 = ar7 + 6;

	//Сложение
	call normDiff_L1_16s32f;

	//Перевод результата в double
	fpu rep 1 .packer = [ar2] with .double <= .float;
	ar5 = ar4;
	fpu rep 2 [ar5++] = .packer;


	//Растяжение результата
	ar0 = ar4;
	gr0 = gr1;
	ar1 = ar2;
	call scale_f64;

	ar7 = ar7 - 6;
	pop ar4, gr4;
	pop ar2, gr2;
	pop ar0, gr0;
	return;

/*
nmppsStatus nmppsNorm_Inf_16s32s_Sfs,  (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, int len, nmpps32s* pNorm, int scaleFactor)

*/
_nmppsNormDiff_L1_16s32s_Sfs:
	ar5 = ar7 - 2;

	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

    ar0 = [--ar5];//pSrc1
    ar1 = [--ar5];//pSrc2
    gr0 = [--ar5];//len
    ar2 = [--ar5];//pDst
    gr1 = [--ar5];//scaleFactor

	call normDiff_L1_16s32s_Sfs;

	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;

