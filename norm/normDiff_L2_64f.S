#include <nmpps_asm_defs.h>

.global _nmppsNormDiff_L2_64f

.global normDiff_L2_64f


.text

/*
	ar0 - input adr a.k. VEC1
	ar1 - input adr a.k. VEC2
	ar2 - output adr = sqrt(SUM((VEC1-VEC2)^2))
	gr0 - len


*/
normDiff_L2_64f:
	push ar4, gr4;
	push ar5, gr5;

	ar4 = ar7 + 2;
	ar7 = ar7 + 6;

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

	ar5 = _zero_dbl;
	fpu 0 rep 1 vreg6 = [ar5]; //Обнуляем результат
	gr4 = 32;


main_loop:
	gr0 -gr4;
	if >= goto M2;
	gr4 = gr0;
M2:

	gr5 = gr4 - 1;
	vlen = gr5;

	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen vreg1 = [ar1++];
	fpu 0 .double vreg0 = vreg0 - vreg1;
	fpu 0 .double vreg0 = vreg0*vreg0;

	gr5 = gr4;
	sub_loop:
		fpu 0 .double vreg6 = vreg6 + .retrive(vreg0);
	gr5 = gr5 - 1;
	if > goto sub_loop;

	gr0 = gr0 - gr4;
	if > goto main_loop;

save:

	fpu 0 rep 1  [ar4] = vreg6;


	/*
		ar0 input adr
		ar1 output adr
		gr0 lenght
    */
    ar0 = ar4;
    ar1 = ar2;
    gr0 = 1;
	call _square_root64f;

exit:
	ar7 = ar7 - 6;
	pop ar5, gr5;
	pop ar4, gr4;
	return;

/*
nmppsStatus nmppsNormDiff_L2_64f(const nmpps64f*  pSrc1, const nmpps64f*  pSrc2, int len, nmpps64f* pNorm)

*/
_nmppsNormDiff_L2_64f:
	ar5 = ar7 - 2;

	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

    ar0 = [--ar5];//pSrc1
    ar1 = [--ar5];//pSrc2
    gr0 = [--ar5];//len
    ar2 = [--ar5];//pDst

	call normDiff_L2_64f;

	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;

