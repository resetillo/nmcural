#include <nmpps_asm_defs.h>

.global _nmppsWinBlackmanOpt_32f
.global _nmppsWinBlackmanOpt_32fc


.text

/*
	gr0 - len
	gr7 - out (alpha)

	alpha = -0.5 /(1 + cos(2pi/(len - 1)))
*/
BlackmanAlphaOptCalc:
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar4, gr4;
	push ar5, gr5;
	ar4 = ar7 + 2;
	ar7 = ar7 + 4;


	gr5 = gr0 - 1;
	[ar4] = gr5;
	ar5 = ar4 + 1;
	[ar5] = gr5;

	fpu rep 1 .packer = [ar4] with .float <= .fixed_32;
	fpu rep 1  [ar4] = .packer;

	/*
    ar0 Divided vector
    ar1 Divisor vector
    ar2 Output vector
	gr0 Lenght
	*/
	ar0 = _dbl_pi_flt;
	ar1 = ar4;
	ar2 = ar4;
	gr0 = 2;
	call Div_32f; // [ar4] = 2pi/(len - 1)

	gr0 = 2;
	push gr0;
	push gr0;//len
	push ar4;//pDst
	push ar4;//pSrc
	call _nmppsCosinus_32f;  // [ar4] = cos(2pi/(len - 1))
	ar7 = ar7 - 4;

	fpu 0 rep 1 vreg0 = [ar4];
	ar5 = _one_flt;
	fpu 0 rep 1 vreg1 = [ar5];
	fpu 0 .float vreg0 = vreg0 + vreg1;
	fpu 0 rep 1 [ar4] = vreg0; // [ar4] = 1 + cos(2pi/(len - 1))

	ar0 = _half_flt;
	ar1 = ar4;
	ar2 = ar4;
	gr0 = 2;
	call Div_32f; // [ar4] = 0.5 / (1 + cos(2pi/(len - 1)))


	fpu 0 rep 1 vreg1 = [ar4];
	ar5 = _zero_flt;
	fpu 0 rep 1 vreg0 = [ar5];
	fpu 0 .float vreg0 = vreg0 - vreg1; // -0.5 / (1 + cos(2pi/(len - 1)))
	fpu 0 rep 1 [ar4] = vreg0;

	gr7 = [ar4];

	ar7 = ar7 - 4;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;



/*
	nmppsStatus nmppsWinBlackmanOpt_32f(const nmpps32f*  pSrc, nmpps32f*  pDst, int len)

*/

_nmppsWinBlackmanOpt_32f:
    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5]; // input adr
    ar1 = [--ar5]; // output adr
    gr0 = [--ar5]; // len

	call wBlackmanOpt_32f;

    pop ar1, gr1;
    pop ar0, gr0;
    return;

/*

	ar0 - input adr,
	ar1 - output adr,
	gr0 - len

*/
wBlackmanOpt_32f:
	push ar5, gr5;
	gr5 = 3;
	gr0 - gr5;
	if <= delayed goto exitf;
	gr7 = nmppsStsSizeErr;
	nul;
	/*
	gr0 - len
	gr7 - out (alpha)
	*/
	call BlackmanAlphaOptCalc;
	gr1 = gr7;

	call wBlackman_32f;
exitf:
	pop ar5, gr5;
	return;

/*
	nmppsStatus nmppsWinBlackmanOpt_32fc(const nmpps32fc*  pSrc, nmpps32fc*  pDst, int len)

*/

_nmppsWinBlackmanOpt_32fc:
    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5]; // input adr
    ar1 = [--ar5]; // output adr
    gr0 = [--ar5]; // len

	call wBlackmanOpt_32fc;

    pop ar1, gr1;
    pop ar0, gr0;
    return;

/*

	ar0 - input adr,
	ar1 - output adr,
	gr0 - len

*/
wBlackmanOpt_32fc:
	push ar5, gr5;
	gr5 = 3;
	gr0 - gr5;
	if <= delayed goto exitfc;
	gr7 = nmppsStsSizeErr;
	nul;

	/*
	gr0 - len
	gr7 - out (alpha)
	*/
	call BlackmanAlphaOptCalc;
	gr1 = gr7;
	call wBlackman_32fc;
exitfc:
	pop ar5, gr5;
	return;



