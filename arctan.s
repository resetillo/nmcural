.global _nmppsArctan_64f

.global _tanTable
.global _angTable

.global _one_dbl
.global _zero_dbl
.global _half_pi_dbl
.global _nan_dbl

.global __macro_change_infinity



.text

_nmppsArctan_64f:
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    gr7 = 0;//По умолчанию возвращаем 0
    ar2 = [--ar5];//pSrc
    ar3 = [--ar5];//pDst
    gr1 = [--ar5];//len

    gr1;
    if <= goto err_size;
    gr0 = ar2;
    gr0;
    if =0 goto err_ptr;
    gr0 = ar3;
    gr0;
    if =0 goto err_ptr;

main_loop:
    gr3 = 32;
    gr2 = gr1;
    gr2 - gr3;
    if <= goto after_correct;
    gr2 = 32;
after_correct:
    gr0 = true;
    gr3 = gr2 + gr0; //gr2 -1
    vlen = gr3;//Загрузим длину
    //0
    ar0 = _zero_dbl;
    fpu 0  rep  vlen  vreg0 = [ar0];
	//1
    ar0 = _one_dbl;
    fpu 0  rep  vlen  vreg1 = [ar0];

	//X = 1
	fpu 1  vreg1 = fpu 0 vreg1;
	//Входное значение Y
    ar0 = ar2;
    fpu 1  rep  vlen  vreg5 = [ar0++];//Оригинальный Y для восстановления знака результата
    fpu 1  .double vreg2 = /vreg5/;//Модуль Y для расчетов
    
    //sum_angle = 0
    fpu 0  vreg7 = vreg0;//Выходной вектор
    
    //ЦИКЛ
    gr0 = 52;//52;
    ar0 = _tanTable;//Таблица тангенсов
    ar1 = _angTable;//Таблица углов
arctan_cycle:
    fpu 0  rep vlen vreg2 = [ar0];
    ar0+=2; //адрес double
    fpu 0  rep vlen vreg3 = [ar1];
    ar1+=2; //адрес double


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
	gr0 = gr0 - 1;
	if > goto arctan_cycle;

	//Обработаем NAN и INF
	fpu 0 vreg5 = fpu 1 vreg5;//Оригинальный вектор
    fpu 0 .double vreg5 - vreg5, set mask if <>0;
    fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //Для nan & inf восстановим изначальные значения

	//Бесконечности обработаем используя функцию замены на значение
	/*	ar0 - input vector
		ar1 - changing value
		gr0 - length of vector
		vreg7 - out vector*/
	ar0 = ar3;
    fpu 0 rep vlen [ar0++] = vreg7;
    ar0 = ar3;
    ar1 = _half_pi_dbl; //arctan(inf) = pi/2
    gr0 = gr2;
	call __macro_change_infinity;

    //Восстановим исходный знак
    fpu 0 vreg6 = fpu 1 vreg5;
    fpu 0 .double vreg6 + vreg6, set mask if <;
    fpu 0 .double vreg7 = mask ? -vreg7 : vreg7;
    fpu 0 rep vlen [ar3++] = vreg7;


    gr0 = 32;
    gr1 = gr1 - gr0;
    if > delayed goto main_loop;
    //Коррекция адреса входного вектора
    gr2 = gr2 << 1; //Смещение в double
    ar2 = ar2 + gr2;

    goto exit;
    
err_size:
    delayed goto exit;
    gr7 = -6;
    nul;
err_ptr:
    delayed goto exit;
    gr7 = -8;
    nul;
 
exit:
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;

