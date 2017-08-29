
#include <nmpps_asm_defs.h>

.global _nmppsPhase_64f
.global phase64f

.global _pi_dbl



.text


/*
	nmppsStatus nmppsPhase_64f(const nmpps64f* pSrcRe, const nmpps64f* pSrcIm, nmpps64f* pDst, int len)

	По сути используется алгоритм CORDIC arctan(y/x),при x = re, y=im
	Причем,
	phase =
		arctan(y/x),       при x>0
		arctan(y/x) + pi,  при x<0, y>=0
		arctan(y/x) - pi,  при x<0, y<0
		pi/2,              при x=0, y>0
		-pi/2,             при x=0, y<0
		nan,               при x=0, y=0
    Возвращаемые значения  (-pi; pi]

*/
_nmppsPhase_64f:
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;

    ar0 = [--ar5];//pSrcRe
    ar1 = [--ar5];//pSrcIm
    ar2 = [--ar5];//pDst
    gr0 = [--ar5];//len

    call phase64f;


    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;


/*
    ar0 pSrcRe
    ar1 pSrcIm
    ar2 pDst
    gr0 len
*/
phase64f:
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

	//Контроль параметров
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


	// Y div X
	/*
	    ar0 Divided vector
	    ar1 Divisor vector
	    ar2 Output vector
		gr0 Lenght
	*/
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	ar3 = ar0;
	ar0 = ar1;
	ar1 = ar3;
	call Div_64f;
	pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;

    //arctan (Y/X)
	/*
	    ar0 pSrc
	    ar1 pDst
	    gr0 len
	*/
	push ar0, gr0;
	push ar1, gr1;
	ar0 = ar2;
	ar1 = ar2;
	call arctan64f;
    pop ar1, gr1;
	pop ar0, gr0;


/*	phase =
		arctan(y/x),       при x>0
		arctan(y/x) + pi,  при x<0, y>=0
		arctan(y/x) - pi,  при x<0, y<0
*/


	ar5 = _pi_dbl;
	fpu 0 rep 32 vreg3 = [ar5]; // PI
	gr5 = 31;
	vlen = gr5;
	gr4 = 32;

loop:
	gr0 - gr4;
	if >= goto after_correct;
	gr4 = gr0;
	gr5 = gr4 - 1;
	vlen = gr5;
	ar5 = _pi_dbl;
	fpu 0 rep vlen vreg3 = [ar5]; // PI
after_correct:

	ar5 = ar2;
	fpu 0 rep vlen vreg0 = [ar5++]; // arctan(y/x)

	fpu 0 rep vlen vreg1 = [ar0++]; // x
	fpu 0 .double vreg1 + vreg1, set mask if <;
	sir = fp0_dmask;
	gr2 = sir;

	fpu 0 rep vlen vreg2 = [ar1++]; // y
	fpu 0 .double vreg2 + vreg2, set mask if <;
	sir = fp0_dmask;
	gr3 = sir;

	gr5 = gr2 and gr3;
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg0 = mask ? vreg0 - vreg3 : vreg0;
	gr5 = gr2 and not gr3;
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg0 = mask ? vreg0 + vreg3 : vreg0;

	fpu 0 rep vlen [ar2++] = vreg0 ; // Сохранение итогового результата

	gr0 = gr0 - gr4;
	if > goto loop;
 
exit:
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    return;

