#include <nmpps_asm_defs.h>

.global _nmppsDiv_32fc
.global Div_32fc

.text
/**
@function nmppsDiv_32fc
	nmppsStatus nmppsDiv_32fc (const nmpps32fc* pSrc1, const nmpps32fc* pSrc2, nmpps32fc* pDst,    int len)

	pDst = pSrc1/pSrc2 = ((pSrc1.re*pSrc2.re + pSrc1.im*pSrc2.im) + i(pSrc2.re*pSrc1.im - pSrc1.re*pSrc2.im)) / (pSrc2.re^2 + pSrc2.im^2)

*/
_nmppsDiv_32fc:

    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;

    ar0 = [--ar5]; // Divided vector
    ar1 = [--ar5]; // Divisor vector
    ar2 = [--ar5]; // Output vector
	gr0 = [--ar5]; // Lenght

	call Div_32fc;

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
Div_32fc:

    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;


	ar3 = ar7 + 2; //Технологический массив на 64 слова
	ar4 = ar7 + 66;
	ar7 = ar7 + 130;

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


    gr4 = 32;
    gr3 = 15;
loop:

	gr0 - gr4;
	if >= goto after_correct;

		gr4 = gr0;

		gr3 = gr0 - 1;
		gr3 = gr3 >> 1;

after_correct:

	gr5 = gr4 - 1;
	vlen = gr5;

	ar5 = ar0;
	fpu 0 rep vlen vreg6 = [ar5++];//src1
	ar5 = ar1;
	fpu 0 rep vlen vreg7 = [ar5++];//src2

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	vlen = gr3;
	fpu 0 rep vlen vreg0 = .packer;//src1.re

	fpu 0 .packer = vreg6 with .float <= .float .in_high;
	fpu 0 rep vlen vreg1 = .packer;//src1.im

	fpu 0 .packer = vreg7 with .float <= .float .in_low;
	fpu 0 rep vlen vreg2 = .packer;//src2.re

	fpu 0 .packer = vreg7 with .float <= .float .in_high;
	fpu 0 rep vlen vreg3 = .packer;//src2.im


	fpu 0 .float vreg7 = vreg0*vreg2;//re1*re2
	fpu 0 .float vreg6 = vreg1*vreg3;//im1*im2
	fpu 0 .float vreg4 = vreg6 + vreg7;//re1*re2 + im1*im2

	//ar5 = ar3;
	//fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka real part

	fpu 0 .float vreg7 = vreg1*vreg2;//re2*im1
	fpu 0 .float vreg6 = vreg0*vreg3;//re1*im2
	fpu 0 .float vreg5 = vreg7 - vreg6;//re2*im1 - re1*im2

	//ar5 = ar3 + 2;
	//fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka im part

	vlen = gr5;
	fpu 0 .packer = vreg4 with .float .in_low <= .float;
	fpu 0 rep vlen vreg6 = .packer;
	fpu 0 .packer = vreg5 with .float .in_high <= .float;
	fpu 0 rep vlen vreg7 = .packer;

	fpu 0 .float vreg7 = vreg6 + vreg7;
	ar5 = ar3;
	fpu 0 rep vlen [ar5++] = vreg7;//save divided



	fpu 0 .float vreg7 = vreg2*vreg2;//re2^2
	fpu 0 .float vreg6 = vreg3*vreg3;//im2^2
	fpu 0 .float vreg7 = vreg6 + vreg7;//re2^2 + im2^2

	/*ar5 = ar4;
	fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka real part divisor
	ar5 = ar4 + 2;
	fpu 0 rep vlen [ar5++gr5] = vreg7;//save aka im part divisor
	*/

	fpu 0 .packer = vreg7 with .float .in_low <= .float;
	fpu 0 rep vlen vreg5 = .packer;
	fpu 0 .packer = vreg7 with .float .in_high <= .float;
	fpu 0 rep vlen vreg6 = .packer;
	fpu 0 .float vreg7 = vreg5 + vreg6;
	ar5 = ar4;
	fpu 0 rep vlen [ar5++] = vreg7;//save divisor

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
	call Div_32f;
	pop ar1, gr1;
	pop ar0, gr0;


	gr5 = gr4 << 1;//mul 2
	ar5 = ar0;
	ar0 = ar5 + gr5;
	ar5 = ar1;
	ar1 = ar5 + gr5;

	gr0 = gr0 - gr4;
    if > goto loop;



exit:
	ar7 = ar7 - 130;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
	return;











