
#include <nmpps_asm_defs.h>

.global _nmppsArctan_64f
.global arctan64f

.global _tanTable
.global _angTable

.global _one_dbl
.global _zero_dbl
.global _half_pi_dbl
.global _nan_dbl



.text

_nmppsArctan_64f:
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5];//pSrc
    ar1 = [--ar5];//pDst
    gr0 = [--ar5];//len

    call arctan64f;


    pop ar1, gr1;
    pop ar0, gr0;
    return;


/*
    ar0 pSrc
    ar1 pDst
    gr0 len
*/
arctan64f:
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

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


    gr4 = 32;
    gr4 - gr0;

    if > goto main_loop;

    gr6 = 31;
    vlen = gr6;

    ar5 = _zero_dbl;
    fpu 0  rep  vlen  vreg0 = [ar5]; //0
    ar5 = _one_dbl;
    fpu 0  rep  vlen  vreg1 = [ar5]; //1
    ar5 =  _bigest_dbl;
    fpu 1  rep  vlen  vreg6 = [ar5]; //BIGGEST DOUBLE
    ar5 =  _half_pi_dbl;
    fpu 1  rep  vlen  vreg7 = [ar5]; //Pi / 2



main_loop:
    //gr4 = 32;
    gr4 - gr0;
    if <= goto after_correct;

    gr6 = gr0 - 1;
    vlen = gr6;

    ar5 = _zero_dbl;
    fpu 0  rep  vlen  vreg0 = [ar5]; //0
    ar5 = _one_dbl;
    fpu 0  rep  vlen  vreg1 = [ar5]; //1
    ar5 =  _bigest_dbl;
    fpu 1  rep  vlen  vreg6 = [ar5]; //BIGGEST DOUBLE
    ar5 =  _half_pi_dbl;
    fpu 1  rep  vlen  vreg7 = [ar5]; //Pi / 2

	after_correct:

	//X = 1
	fpu 1  vreg1 = fpu 0 vreg1;
	//Входное значение Y
    fpu 1  rep  vlen  vreg5 = [ar0++];//Оригинальный Y для восстановления знака результата
    fpu 1  .double vreg2 = /vreg5/;//Модуль Y для расчетов
    

	call arctan_calculation_cycle;

	//Обработаем NAN и INF
	fpu 0 vreg5 = fpu 1 vreg5;//Оригинальный вектор
    fpu 0 .double vreg5 - vreg5, set mask if <>0;
    fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //Для nan & inf восстановим изначальные значения

	//Бесконечности обработаем используя функцию замены на значение
	fpu 0 vreg6 = fpu 1 vreg6;//Наибольшее число
    fpu 0 .double vreg5 = /vreg5/;
    fpu 0 .double vreg5 - vreg6, set mask if >;
	fpu 0 vreg6 = fpu 1 vreg7;//PI / 2
    fpu 0 .double vreg7 = mask ? vreg6 : vreg7;



    //Восстановим исходный знак
	fpu 0 vreg5 = fpu 1 vreg5;//Оригинальный вектор
    fpu 0 .double vreg5 + vreg5, set mask if <;
    fpu 0 .double vreg7 = mask ? -vreg7 : vreg7;
    fpu 0 rep vlen [ar1++] = vreg7;


    gr0 = gr0 - gr4;
    if > goto main_loop;


exit:
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    return;

/*
	Используется внутри функций, рассчитывающих арктангенс
	fpu 0 vreg0 - zero_dbl
	fpu 0 vreg1 - one
	fpu 1 vreg1 - /X/
	fpu 1 vreg2 - /Y/

	fpu 0 vreg7 - out data
	also used:
		ar4, gr5, ar6
		fpu 0 vreg2
		fpu 0 vreg3
		fpu 0 vreg4
		fpu 0 vreg5
		fpu 0 vreg6
		fpu 1 vreg3
		fpu 1 vreg4
*/

arctan_calculation_cycle:
    //sum_angle = 0
    fpu 0  vreg7 = vreg0;//Выходной вектор
    
    //ЦИКЛ
    gr5 = 52;//52;
    ar4 = _tanTable;//Таблица тангенсов
    ar6 = _angTable;//Таблица углов
	arctan_cycle:
	    fpu 0  rep vlen vreg2 = [ar4];
	    ar4+=2; //адрес double
	    fpu 0  rep vlen vreg3 = [ar6];
	    ar6+=2; //адрес double


	    //s = copysign(1, y)
	    fpu 0  vreg6 = fpu 1 vreg2;
	    fpu 0  vreg4 = fpu 0 vreg1;
	    fpu 0  .double vreg6 + vreg6, set mask if <;
	    fpu 0  .double vreg4 = mask ? - vreg4 : vreg4;

	    //Xnew = x + s*y*t;
	    fpu 0  vreg5 = fpu 1 vreg1;//x

	    #fpu 0  vreg6 = fpu 1 vreg2;//y
	    fpu 0  .double vreg6 = vreg6 * vreg4;//y*s
	    fpu 0  .double vreg6 = vreg6 * vreg2 + vreg5;//y*s*t + x
	    fpu 1  vreg3 = fpu 0 vreg6;//Xnew

	    //Ynew = y - s*x*t;
	    #fpu 0  vreg5 = fpu 1 vreg1;//x
	    fpu 0  vreg6 = fpu 1 vreg2;//y
	    fpu 0  .double vreg5 = vreg5 * vreg4;//x*s
	    fpu 0  .double vreg5 = -vreg5 * vreg2 + vreg6;//-x*s*t + y
	    fpu 1  vreg4 = fpu 0 vreg5;//Ynew

	     //sum_angle = sum_angle + s*a;
	    fpu 0  .double vreg7 = vreg4 * vreg3 + vreg7;//s*a


		//x =  Xnew;
		fpu 1 vreg1 = fpu 1  vreg3;
		//y =  Ynew;
		fpu 1 vreg2 = fpu 1 vreg4;
		gr5 = gr5 - 1;
		if > goto arctan_cycle;
return;

