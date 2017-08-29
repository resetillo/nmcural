
#include <nmpps_asm_defs.h>

.global _nmppsPhase_64fc
.global phase64fc

.global _pi_dbl



.text


/*
	nmppsStatus nmppsPhase_64fc(const nmpps64fc* pSrc, nmpps64f* pDst, int len)

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
_nmppsPhase_64fc:
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5];//pSrc_fc
    ar1 = [--ar5];//pDst
    gr0 = [--ar5];//len

    call phase64fc;


    pop ar1, gr1;
    pop ar0, gr0;
    return;


/*
    ar0 pSrc_fc
    ar1 pDst
    gr0 len
*/
phase64fc:
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

    ar2 = ar7 + 2;
    ar3 = ar7 + 66;
    ar7 = ar7 + 130;

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
    if =0 goto exit;

    gr7 = nmppsStsNoErr;//По умолчанию возвращаем 0

	//Организация цикла
    gr4 = 32;
main_loop:
    gr4 - gr0;

    if <= goto after_correct;
    gr4 = gr0;
after_correct:
	gr5 = gr4 - 1;
	vlen = gr5;
	//Разделяем входные данные пополам
	gr5 = 4; /*FIX_ME may be incorrect increment*/
	ar5 = ar0;
	fpu 0 rep vlen vreg0 = [ar5++gr5];
	ar5 = ar2;
	fpu 0 rep vlen [ar5++] = vreg0; // X (Re)
	fpu 0 .double vreg0 + vreg0, set mask if <;
	sir = fp0_dmask;
	gr2 = sir;

	ar5 = ar0 + 2;
	fpu 0 rep vlen vreg0 = [ar5++gr5];
	ar0 = ar5 - 2; //Изменение адреса для следующей итерации
	ar5 = ar3;
	fpu 0 rep vlen [ar5++] = vreg0; // Y (Im)
	fpu 0 .double vreg0 + vreg0, set mask if <;
	sir = fp0_dmask;
	gr3 = sir;


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
	ar0 = ar3;//Y
	ar1 = ar2;//X
	//ar2 = ar2;
	gr0 = gr4;
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
	gr0 = gr4;
	call arctan64f;
    pop ar1, gr1;
	pop ar0, gr0;


/*	phase =
		arctan(y/x),       при x>0
		arctan(y/x) + pi,  при x<0, y>=0
		arctan(y/x) - pi,  при x<0, y<0
*/
	gr5 = gr4 - 1;
	vlen = gr5;
	ar5 = ar2;
	fpu 0 rep vlen vreg0 = [ar5++]; // arctan(y/x)
	ar5 = _pi_dbl;
	fpu 0 rep vlen vreg1 = [ar5]; // PI
	gr5 = gr2 and gr3;
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg0 = mask ? vreg0 - vreg1 : vreg0;
	gr5 = gr2 and not gr3;
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg0 = mask ? vreg0 + vreg1 : vreg0;

	fpu 0 rep vlen [ar1++] = vreg0 ; // arctan(y/x)

    gr0 = gr0 - gr4;
    if > goto main_loop;

 
exit:
    ar7 = ar7 - 130;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    return;

