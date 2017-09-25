#include <nmpps_asm_defs.h>

.global _nmppsNorm_L1_16s32f
.global norm_L1_16s32f


.text

/*
	ar0 - input adr
	ar1 - output adr
	gr0 - len
*/
norm_L1_16s32f:
summator_abs16s32f:
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
    if =0 goto exit;

    gr7 = nmppsStsNoErr;//По умолчанию возвращаем 0

	ar5 = _zero_flt;
	fpu 0 rep 1 vreg6 = [ar5]; //Обнуляем результат
	gr4 = 32;


main_loop:
	gr0 -gr4;
	if >= goto M2;
	gr4 = gr0;
M2:

	push ar0, gr0;
	gr0 = gr4;
	call i16toV7;
	pop ar0, gr0;

	fpu 0 .float vreg0 = /vreg7/;
	fpu 0 .packer= vreg0 with .float .in_low <= .float;
	gr5 = VL;
	gr5 = gr5 + 1;
	gr5 = gr5 << 1;
	gr5 = gr5 - 1;
	vlen = gr5;
	fpu 0 rep vlen vreg0 = .packer;

	gr5 = gr4;
	sub_loop:
		fpu 0 .float vreg6 = vreg6 + .retrive(vreg0);
	gr5 = gr5 - 1;
	if > goto sub_loop;

	gr5 = ar0;
	gr0 = gr0 - gr4;
	if > delayed goto main_loop;
	gr5 = gr5 + gr4;
	ar0 = gr5;

save:
	fpu 0 rep 1  [ar4] = vreg6;
	gr5 = [ar4];
	[ar1] = gr5;
exit:
	ar7 = ar7 - 4;
	pop ar5, gr5;
	pop ar4, gr4;
	return;

/*
nmppsStatus nmppsNorm_L1_16s32f(const nmpps16s*  pSrc, int len, nmpps32f* pNorm)

*/
_nmppsNorm_L1_16s32f:
	ar5 = ar7 - 2;

	push ar0, gr0;
	push ar1, gr1;

    ar0 = [--ar5];//pSrc
    gr0 = [--ar5];//len
    ar1 = [--ar5];//pDst

	call summator_abs16s32f;

	pop ar1, gr1;
	pop ar0, gr0;

	return;

