
#include <nmpps_asm_defs.h>

.global _nmppsPhase_32fc
.global phase32fc

.global _pi_dbl



.text


/*
	nmppsStatus nmppsPhase_32fc(const nmpps32fc* pSrc, nmpps32f* pDst, int len)

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
_nmppsPhase_32fc:
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5];//pSrc_fc
    ar1 = [--ar5];//pDst
    gr0 = [--ar5];//len

    call phase32fc;


    pop ar1, gr1;
    pop ar0, gr0;
    return;


/*
    ar0 pSrc_fc
    ar1 pDst
    gr0 len
*/
phase32fc:
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

	//Организация цикла
    gr4 = 32;
    gr5 = 31;
    gr6 = 15;
main_loop:
    gr4 - gr0;

    if <= goto after_correct;
	    gr4 = gr0;
		gr5 = gr4 - 1;
		gr6 = gr4 >> 1; //div 2
		gr3 = 1;
		gr4 and gr3;
		if > goto after_correct;
		gr6 = gr6 - 1;
after_correct:
	push gr0;//освобождаем регистр для промежуточного использования
	push gr0;
	vlen = gr5;
	//Разделяем входные данные пополам
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .packer= vreg0 with .float <= .float .in_low;
	vlen = gr6;
	fpu 0 rep vlen vreg1 = .packer;
	fpu 0 .float vreg1 + vreg1, set mask if <;
	sir = fp0_lmask;
	gr0 = sir;
	sir = fp0_hmask;
	gr1 = sir;

	ar5 = ar2;
	fpu 0 rep vlen [ar5++] = vreg1; // X (Re)



	vlen = gr5;
	fpu 0 .packer = vreg0 with .float <= .float .in_high;
	vlen = gr6;
	ar5 = ar3;
	fpu 0 rep vlen vreg2 = .packer;
	fpu 0 .float vreg2 + vreg2, set mask if <;
	sir = fp0_lmask;
	gr2 = sir;
	sir = fp0_hmask;
	gr3 = sir;

	ar5 = ar3;
	fpu 0 rep vlen [ar5++] = vreg2; // Y (Im)

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
	call Div_32f;
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
	call arctan32f;
    pop ar1, gr1;
	pop ar0, gr0;


/*	phase =
		arctan(y/x),       при x>0
		arctan(y/x) + pi,  при x<0, y>=0
		arctan(y/x) - pi,  при x<0, y<0
*/

L1:
	vlen = gr6;
	ar5 = ar2;
	fpu 0 rep vlen vreg0 = [ar5++]; // arctan(y/x)
	ar5 = _pi_flt;
	fpu 0 rep vlen vreg1 = [ar5]; // PI

	//res = arctan(y/x) - pi,  при x<0, y<0
	gr7 = gr0 and gr2;
	sir = gr7;
	fp0_lmask = sir;
	gr7 = gr1 and gr3;
	sir = gr7;
	fp0_hmask = sir;

	fpu 0 .float vreg0 = mask ? vreg0 - vreg1 : vreg0;

	//res = arctan(y/x) + pi,  при x<0, y>=0
	gr7 = gr0 and not gr2;
	sir = gr7;
	fp0_lmask = sir;
	gr7 = gr1 and not gr3;
	sir = gr7;
	fp0_hmask = sir;
	fpu 0 .float vreg0 = mask ? vreg0 + vreg1 : vreg0;


	pop gr0;//Восстанавливаем размер
	pop gr0;

	gr3 = 1;
	gr3 and gr4;
	if =0 goto simple_save; //Размер четный, простое копирование

		//Размер нечетный, значит это последний сегмент данных
		ar5 = ar2;
		fpu 0 rep vlen [ar5++] = vreg0 ; // копирование через буффер
		gr4 - gr3;
		if =0 goto last_word_copy;
			gr5 = gr4 >> 1; // За счет деления на 2 скопируем на 1 слово меньше, которое позже перекопируем вручную
			gr5 = gr5 - 1;
			vlen = gr5;
			fpu 0 rep vlen vreg0 = [ar2++];
			fpu 0 rep vlen [ar1++] = vreg0;
		last_word_copy:
			gr5 = [ar2];
			[ar1] = gr5;
		goto norm_exit;

simple_save:
	fpu 0 rep vlen [ar1++] = vreg0 ; // result

    gr0 = gr0 - gr4;
    if > goto main_loop;

norm_exit:
    gr7 = nmppsStsNoErr;//По умолчанию возвращаем 0
exit:
    ar7 = ar7 - 130;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    return;

