#include <nmpps_asm_defs.h>

.global _nmppsWinBlackmanStd_32f
.global _nmppsWinBlackmanStd_32fc

.text

BlackmanAlphaStd:
	.float  -0.16

/*
	nmppsStatus nmppsWinBlackmanStd_32f(const nmpps32f*  pSrc, nmpps32f*  pDst, int len)

*/

_nmppsWinBlackmanStd_32f:
    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5]; // input adr
    ar1 = [--ar5]; // output adr
    gr0 = [--ar5]; // len

	call wBlackmanStd_32f;

    pop ar1, gr1;
    pop ar0, gr0;
    return;

/*

	ar0 - input adr,
	ar1 - output adr,
	gr0 - len

*/
wBlackmanStd_32f:
	push ar5, gr5;
	ar5 = BlackmanAlphaStd;
	gr1 = [ar5];
	call wBlackman_32f;
	pop ar5, gr5;
	return;

/*
	nmppsStatus nmppsWinBlackmanStd_32fc(const nmpps32fc*  pSrc, nmpps32fc*  pDst, int len)

*/

_nmppsWinBlackmanStd_32fc:
    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5]; // input adr
    ar1 = [--ar5]; // output adr
    gr0 = [--ar5]; // len

	call wBlackmanStd_32fc;

    pop ar1, gr1;
    pop ar0, gr0;
    return;

/*

	ar0 - input adr,
	ar1 - output adr,
	gr0 - len

*/
wBlackmanStd_32fc:
	push ar5, gr5;
	ar5 = BlackmanAlphaStd;
	gr1 = [ar5];
	call wBlackman_32fc;
	pop ar5, gr5;
	return;



