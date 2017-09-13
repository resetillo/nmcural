#include <nmpps_asm_defs.h>

.global _nmppsWinKaiser_32fc
.global wKaiser_32fc



.text

/*
	nmppsStatus nmppsWinKaiser_32f(const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f beta)

	pDst[n] = pSrc[n]*w(n)
	w(n) = I0(beta*sqrt(1-((n - (L-1)/2)/((L-1)/2))^2)) / I0(beta), 0 <= n <= L - 1
*/

_nmppsWinKaiser_32fc:
    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5]; // input adr
    ar1 = [--ar5]; // output adr
    gr0 = [--ar5]; // len
	gr1 = [--ar5]; // beta

	call wKaiser_32fc;

	//loop for multiply input vector and window

    pop ar1, gr1;
    pop ar0, gr0;
    return;

/*

	ar0 - input adr,
	ar1 - output adr,
	gr0 - len,
	gr1 - beta

	write window to output adr
*/

wKaiser_32fc:

   // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

    ar2 = ar7 + 2;
    ar3 = ar7 + 4;
    ar7 = ar7 + 68;

    gr5 = 1;
	gr0 - gr5;
    if <= delayed goto exit;
    gr7 = nmppsStsSizeErr;

    gr5 = ar0;
    gr5;
    if =0 delayed goto exit;
    gr7 = nmppsStsNullPtrErr;

    gr5 = ar1;
    gr5;
    if =0 delayed goto  exit;



    //beta
    [ar2] = gr1;
    ar5 = ar2 + 1;
    [ar5] = gr1;

    fpu 2 rep 32 vreg0 = [ar2]; // fp2vr0 aka beta
/*
	ar0 - input
	vr7 - output
	gr0 - len [1-64]
*/
	push ar0, gr0;
	ar0 = ar2;
	gr0 = 2;
	call bessel_I0_32f;
    fpu 0 rep 1 [ar2] = vreg7;
	pop  ar0, gr0;
/*
    ar0 Divided vector
    ar1 Divisor vector
    ar2 Output vector
	gr0 Lenght
*/

	push ar0, gr0;
	push ar1;
	push ar2;
	ar0 = _one_flt;
	ar1 = ar2; // I0(beta)
	gr0 = 2;
	call Div_32f;
	pop ar2;
	pop ar1;
	pop ar0, gr0;

    fpu 2 rep 32 vreg1 = [ar2]; // fp2vr1 aka 1/I0(beta)

    gr5 = gr0 - 1;
    [ar2] = gr5;
    ar5 = ar2 + 1;
    [ar5] = gr5;

    //sir = 0;
    //fp_exp = sir;
    fpu rep 1 .packer = [ar2] with .float <= .fixed_32;
    fpu rep 1 [ar2] = .packer;

    fpu 2 rep 32 vreg2 = [ar2];
    ar5 = _half_flt;
    fpu 2 rep 32 vreg3 = [ar5];
    fpu 2 .float vreg2 = vreg2*vreg3; // fp2vr2 aka (L-1)/2

/*
    ar0 Divided vector
    ar1 Divisor vector
    ar2 Output vector
	gr0 Lenght
*/

	push ar0, gr0;
	push ar1;
	push ar2;
	ar0 = _two_flt;
	ar1 = ar2; // L - 1
	gr0 = 2;
	call Div_32f;
	pop ar2;
	pop ar1;
	pop ar0, gr0;
    fpu 2 rep 32 vreg3 = [ar2]; // fp2vr3 aka 1 div (L-1)/2
    ar5 = _one_flt;
    fpu 2 rep 32 vreg4 = [ar5]; // fp2vr4 aka 1
    ar5 = _num_vector;
    fpu 2 rep 32 vreg5 = [ar5++]; // fp2vr5 aka n
    ar5 = _num64_flt;
    fpu 2 rep 32 vreg6 = [ar5]; // fp2vr6 aka 64.0f

    gr4 = 64;

main_loop:
	gr0 - gr4;
	if >= goto M1;
	gr4 = gr0;
	M1:
	fpu 2 .float vreg7 = vreg5 - vreg2; // n - (L-1)/2
	fpu 2 .float vreg7 = vreg7 * vreg3; // (n - (L-1)/2) div (L-1)/2
	fpu 2 .float vreg7 = vreg7 * vreg7;
	fpu 2 .float vreg7 = vreg4 - vreg7; // 1 - t*t
	ar5 = ar3;
    fpu 2 rep 32 [ar5++] = vreg7;

    /*
	ar0 input adr
	ar1 output adr
	gr0 lenght
	*/
	push ar0, gr0;
	push ar1, gr1;
	ar0 = ar3;
	ar1 = ar3;
	gr0 = gr4;
	call _square_root32f;
	pop ar1, gr1;
	pop ar0, gr0;

	ar5 = ar3;
    fpu 2 rep 32  vreg7 = [ar5++];
	fpu 2 .float vreg7 = vreg7 * vreg0; //beta*sqrt(1 - t*t)
	ar5 = ar3;
    fpu 2 rep 32 [ar5++] = vreg7;

/*
	ar0 - input
	vr7 - output
	gr0 - len [1-64]
*/
	push ar0, gr0;
	ar0 = ar3;
	gr0 = 64;
	call bessel_I0_32f;
	pop  ar0, gr0;
    fpu 2 vreg7 = fpu 0 vreg7; //I0(beta*sqrt(1 - t*t))
	fpu 2 .float vreg7 = vreg7 * vreg1; //I0(beta*sqrt(1 - t*t))/I0(beta) aka window

	ar5 = ar3;
	fpu 2 rep 32 [ar5++] = vreg7;
/*
	multiply vector with real values and vector with complex values

	ar0 - vector with real values
	ar1 - vector with complex values
	ar2 - output vector
	gr0 - len
*/

	push ar0, gr0;
	push ar1;
	push ar2;
	gr0 = gr4;
	ar2 = ar1;
	ar1 = ar0;
	ar0 = ar3;
	call mulV32_r_fc;
	pop ar2;
	pop ar1;
	pop ar0, gr0;


	//***********
	gr0 = gr0 - gr4; // minus 64
	if <= goto pre_exit;

	gr5 = gr4<<1;
	ar5 = ar0;
	ar0 = ar5 + gr5;
	ar5 = ar1;
	ar1 = ar5 + gr5;

	fpu 2 .float vreg5 = vreg5 + vreg6; // prepare n for next iteration
	goto main_loop;

pre_exit:
	gr7 = nmppsStsNoErr;
exit:
    ar7 = ar7 - 68;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
return;
















