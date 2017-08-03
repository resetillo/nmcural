
#include <nmpps_asm_defs.h>

.global _nmppsNormDiff_L1_32f
.global normDiff_L1_32f

.global _zero_flt


.text

/*
	ar0 - input1 adr
	ar1 - input2 adr
	ar2 - output adr
	gr0 - len
*/
normDiff_L1_32f:
	push ar4, gr4;
	push ar5, gr5;

	ar4 = ar7 + 2;
	ar7 = ar7 + 4;

	gr0;
    if <= delayed goto exit;
    gr7 = nmppsStsSizeErr;

    gr5 = ar0;
    gr5;
    if =0 delayed goto exit;
    gr7 = nmppsStsNullPtrErr;

    gr5 = ar1;
    gr5;
    if =0 delayed goto exit;

    gr5 = ar2;
    gr5;
    if =0 goto exit;

    gr7 = nmppsStsNoErr;//По умолчанию возвращаем 0

	ar5 = _zero_flt;
	fpu 0 rep 1 vreg7 = [ar5]; //Обнуляем результат
	gr4 = 32;


main_loop:
	gr0 -gr4;
	if >= goto M1;
	gr4 = gr0;
M1:
	fpu rep 16 .packer= [ar0++] with .float .in_low <= .float;
	fpu 0 rep 32 vreg0 = .packer;
	fpu rep 16 .packer= [ar1++] with .float .in_low <= .float;
	fpu 0 rep 32 vreg1 = .packer;


	fpu 0 .float vreg0 = vreg0 - vreg1;
	fpu 0 .float vreg0 = /vreg0/;

	gr5 = gr4;
	sub_loop:
		fpu 0 .float vreg7 = vreg7 + .retrive(vreg0);
	    gr5 = gr5 - 1;
	if > goto sub_loop;

	gr0 = gr0 - gr4;
	if > goto main_loop;

save:
	fpu 0 rep 1  [ar4] = vreg7;
	gr5 = [ar4];
	[ar2] = gr5;
exit:
	ar7 = ar7 - 4;
	pop ar5, gr5;
	pop ar4, gr4;
	return;




/*
nmppsStatus nmppsNormDiff_L1_32f(const nmpps32f*  pSrc1, const nmpps32f*  pSrc2, int len, nmpps32f* pNorm)

*/
_nmppsNormDiff_L1_32f:
	ar5 = ar7 - 2;

	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

    ar0 = [--ar5];//pSrc1
    ar1 = [--ar5];//pSrc2
    gr0 = [--ar5];//len
    ar2 = [--ar5];//pDst

	call normDiff_L1_32f;

	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;
























