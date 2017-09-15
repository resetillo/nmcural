#include <nmpps_asm_defs.h>

.global _nmppsDiv_64fc
.global Div_64fc

.text
/**
@function nmppsDiv_64fc
	nmppsStatus nmppsDiv_64fc (const nmpps64fc* pSrc1, const nmpps64fc* pSrc2, nmpps64fc* pDst,    int len)

	pDst = pSrc1/pSrc2 = ((pSrc1.re*pSrc2.re + pSrc1.im*pSrc2.im) + i(pSrc2.re*pSrc1.im - pSrc1.re*pSrc2.im)) / (pSrc2.re^2 + pSrc2.im^2)

*/
_nmppsDiv_64fc:

    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;

    ar0 = [--ar5]; // Divided vector
    ar1 = [--ar5]; // Divisor vector
    ar2 = [--ar5]; // Output vector
	gr0 = [--ar5]; // Lenght

	call Div_64fc;

    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;

/*
    ar0 Divided vector
    ar1 Divisor vector
    ar2 Output vector
	gr0 Lenght
*/
Div_64fc:

    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;


	ar3 = ar7 + 2; //Технологический массив на 64 слова
	ar4 = ar7 + 130;
	ar7 = ar7 + 258;

	gr0;
    if <= delayed goto exit;
    gr7 = nmppsStsSizeErr;

    gr1 = ar2;
    gr1;
    if =0 delayed goto exit;
    gr7 = nmppsStsNullPtrErr;

    gr1 = ar0;
    gr1;
    if =0 delayed goto exit;
    gr1 = ar1;
    gr1;
    if =0 goto exit;

	gr7 = 0; //Значение по умолчанию


	//gr0 = gr0 << 1;
    gr4 = 32;
loop:

	gr0 - gr4;
	if >= delayed goto after_correct;
	gr5 = gr4 - 1;
	vlen = gr5;

	gr4 = gr0;
	gr5 = gr4 - 1;
	vlen = gr5;

after_correct:

	gr5 = 4;
	ar5 = ar0;
	fpu 0 rep vlen vreg0 = [ar5++gr5];//src1.re
	ar5 = ar0 + 2;
	fpu 0 rep vlen vreg1 = [ar5++gr5];//src1.im
	ar5 = ar1;
	fpu 0 rep vlen vreg2 = [ar5++gr5];//src2.re
	ar5 = ar1 + 2;
	fpu 0 rep vlen vreg3 = [ar5++gr5];//src2.im

	fpu 0 .double vreg7 = vreg0*vreg2;//re1*re2
	fpu 0 .double vreg6 = vreg1*vreg3;//im1*im2
	fpu 0 .double vreg7 = vreg6 + vreg7;//re1*re2 + im1*im2

	ar5 = ar3;
	fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka real part

	fpu 0 .double vreg7 = vreg1*vreg2;//re2*im1
	fpu 0 .double vreg6 = vreg0*vreg3;//re1*im2
	fpu 0 .double vreg7 = vreg7 - vreg6;//re2*im1 - re1*im2

	ar5 = ar3 + 2;
	fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka im part

	fpu 0 .double vreg7 = vreg2*vreg2;//re2^2
	fpu 0 .double vreg6 = vreg3*vreg3;//im2^2
	fpu 0 .double vreg7 = vreg6 + vreg7;//re2^2 + im2^2

	ar5 = ar4;
	fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka real part divisor
	ar5 = ar4 + 2;
	fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka im part divisor

	push ar0, gr0;
	push ar1, gr1;
	//divided and save
	ar0 = ar3;
	ar1 = ar4;
	gr0 = gr4<<1;
	/*
    ar0 Divided vector
    ar1 Divisor vector
    ar2 Output vector
	gr0 Lenght
	*/
	call Div_64f;
	pop ar1, gr1;
	pop ar0, gr0;


	gr5 = gr4 << 2;//mul 4
	ar5 = ar0;
	ar0 = ar5 + gr5;
	ar5 = ar1;
	ar1 = ar5 + gr5;

	gr0 = gr0 - gr4;
    if > goto loop;



exit:
	ar7 = ar7 - 258;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
	return;











