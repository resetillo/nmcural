#include <nmpps_asm_defs.h>

.global _nmppsWinBlackman_32f
.global wBlackman_32f

.text

/*
	nmppsStatus nmppsWinBlackman_32f(const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f alpha)

	pDst[n] = pSrc[n]*w(n)
	w(n) = (alpha + 1)/2 - 0.5cos(2pi*n/(len-1)) - 0.5*alpha*cos(4pi*n/(len-1)) =
	= alpha(1-cos^2(2pi*n/(len-1))) + 0.5(1 - cos(2pi*n/(len-1)))
*/

_nmppsWinBlackman_32f:
    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5]; // input adr
    ar1 = [--ar5]; // output adr
    gr0 = [--ar5]; // len
	gr1 = [--ar5]; // alpha

	call wBlackman_32f;

    pop ar1, gr1;
    pop ar0, gr0;
    return;


/*

	ar0 - input adr,
	ar1 - output adr,
	gr0 - len,
	gr1 - alpha

	write window to output adr
*/
wBlackman_32f:


   // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

    ar2 = ar7 + 2;
    ar3 = ar7 + 4;
    ar4 = ar7 + 6;
    ar7 = ar7 + 70;

    gr5 = 3;
	gr0 - gr5;
    if < delayed goto exit;
    gr7 = nmppsStsSizeErr;

    gr5 = ar0;
    gr5;
    if =0 delayed goto exit;
    gr7 = nmppsStsNullPtrErr;

    gr5 = ar1;
    gr5;
    if =0 delayed goto  exit;

    gr5 = gr0 -1;
    [ar2] = gr5;
    ar5 = ar2 + 1;
    [ar5] = gr5;

    fpu rep 1 .packer = [ar2] with .float <= .fixed_32;
    fpu rep 1 [ar2] = .packer;// len - 1 in float


	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
    /*
    ar0 Divided vector
    ar1 Divisor vector
    ar2 Output vector
	gr0 Lenght
	*/
	ar0 = _dbl_pi_flt;
	ar1 = ar2;
	//ar2 = ar2;
	gr0 = 2;
	call Div_32f;//[ar2] = 2pi/(len-1)
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;


    gr5 = gr1;
    [ar3] = gr5;
    ar5 = ar3 + 1;
    [ar5] = gr5; // [ar3] = alpha

	gr4 = 64;

	gr5 = 31;
	vlen = gr5;

	ar5 = _num_vector;
	fpu 2 rep vlen vreg4 = [ar5++]; // fp2vr4 aka  n

	gr0 - gr4;
	if < goto re_init;

		fpu 2 rep vlen vreg0 = [ar2];// fp2vr0 aka 2pi/(len-1)
		ar5 = _one_flt;
		fpu 2 rep vlen vreg1 = [ar5];// one

		ar5 = _half_flt;
		fpu 2 rep vlen vreg2 = [ar5];// fp2vr2 aka  0.5
		fpu 2 rep vlen vreg3 = [ar3];// fp2vr3 aka  alpha

		ar5 = _num64_flt;
		fpu 2 rep vlen vreg5 = [ar5]; // fp2vr5 aka  64

loop:
	gr0 - gr4;
	if >= goto after_correct;
	re_init:
		gr4 = gr0;
		ar5 = ar4;
		fpu 2 rep vlen [ar5++] = vreg4;
		fpu 2 rep vlen vreg4 = [ar5++]; // fp2vr4 aka  n

		gr5 = gr0 - 1;
		gr5 = gr5 >> 1;
		vlen = gr5;

		ar5 = ar4;
		fpu 2 rep vlen vreg4 = [ar5++]; // fp2vr4 aka  n

		fpu 2 rep vlen vreg0 = [ar2];// fp2vr0 aka 2pi/(len-1)
		ar5 = _one_flt;
		fpu 2 rep vlen vreg1 = [ar5];// one

		ar5 = _half_flt;
		fpu 2 rep vlen vreg2 = [ar5];// fp2vr2 aka  0.5
		fpu 2 rep vlen vreg3 = [ar3];// fp2vr3 aka  alpha

		ar5 = _num64_flt;
		fpu 2 rep vlen vreg5 = [ar5]; // fp2vr5 aka  64
after_correct:
	fpu 2 .float vreg7 = vreg4*vreg0;// n*2pi/(len-1)
	ar5 = ar4;
	fpu 2 rep 32 [ar5++] = vreg7;

	push gr4;
	push gr4;//len
	push ar4;//pDst
	push ar4;//pDst
	call _nmppsCosinus_32f;
	ar7 = ar7 - 4;

	ar5 = ar4;
	fpu 2 rep vlen vreg6 = [ar5++]; // cos(t)
	fpu 2 .float vreg7 = vreg1 - vreg6;
	fpu 2 .float vreg7 = vreg7 * vreg2;// 0.5(1 - cos(t))
	fpu 2 .float vreg6 = vreg6 * vreg6;
	fpu 2 .float vreg6 = vreg1 - vreg6;
	fpu 2 .float vreg6 = vreg6*vreg3; // alpha*(1-cos(t)^2)
	fpu 2 .float vreg7 = vreg6 + vreg7;// alpha*(1-cos(t)^2) + 0.5(1 - cos(t))

	//multiply
	fpu 2 rep vlen vreg6 = [ar0++];
	fpu 2 .float  vreg7 = vreg6*vreg7;

	//save
	gr5 = 1;
	gr4 and gr5;
	if =0 goto simple_save;
		ar5 = ar4;
		fpu 2 rep vlen [ar5++] = vreg7;
		gr4 - gr5;
		if =0 goto save_last_word;
			gr5 = VL;
			gr5--;
			VL = gr5;
			fpu 2 rep vlen vreg7 = [ar4++];
			fpu 2 rep vlen [ar1++] = vreg7;

		save_last_word:
		gr5 = [ar4];
		[ar1] = gr5;
		goto pre_exit;

	simple_save:
	fpu 2 rep vlen [ar1++] = vreg7;
	fpu 2 .float vreg4 = vreg4 + vreg5;// prepare n for next iteration

	gr0 = gr0 - gr4;
	if > goto loop;

pre_exit:
	gr7 = nmppsStsNoErr;
exit:
    ar7 = ar7 - 70;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
return;





