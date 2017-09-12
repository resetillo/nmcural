#include <nmpps_asm_defs.h>

.global _nmppsNorm_L1_16s32s_Sfs

.global norm_L1_16s32s_Sfs
.global norm_L1_16s32f
.global scale_f64

/*
	ar0 - input adr
	ar1 - output adr
	gr0 - len
	gr1 - scaleFactor
*/
norm_L1_16s32s_Sfs:
	push ar0, gr0;

	ar4 = ar7 + 2;
	ar7 = ar7 + 6;

	//Сложение
	call norm_L1_16s32f;

	//Перевод результата в double
	fpu rep 1 .packer = [ar1] with .double <= .float;
	ar5 = ar4;
	fpu rep 2 [ar5++] = .packer;


	//Растяжение результата
	ar0 = ar4;
	gr0 = gr1;
	call scale_f64;

	ar7 = ar7 - 6;
	pop ar0, gr0;
	return;

/*
nmppsStatus nmppsNorm_Inf_16s32s_Sfs,  (const nmpps16s*  pSrc, int len, nmpps32s* pNorm, int scaleFactor)

*/
_nmppsNorm_L1_16s32s_Sfs:
	ar5 = ar7 - 2;

	push ar0, gr0;
	push ar1, gr1;

    ar0 = [--ar5];//pSrc
    gr0 = [--ar5];//len
    ar1 = [--ar5];//pDst
    gr1 = [--ar5];//scaleFactor

	call norm_L1_16s32s_Sfs;

	pop ar1, gr1;
	pop ar0, gr0;

	return;

