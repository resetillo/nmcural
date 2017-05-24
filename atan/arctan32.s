.global _arctan32f

.global _tanTableF
.global _angTableF

.global _one_flt
.global _zero_flt
.global _half_pi_flt
.global _nan_flt

.global __macro_change_infinityF32



.text

_arctan32f:
    //ar4  input data
	//gr2  lenght

    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    ar2 = ar7+2; //Промежуточный буфер
    ar7 = ar7 + 66;

    gr3 = 1;
    gr2 and gr3;
    if =0 delayed goto after_correct;
    gr1 = gr2 >> 1; //Перевод в двойные слова
    nul;

    gr1 = gr1 + 1; //Нечетная длина вектора, на 1 двойное слово больше

after_correct:
    gr3 = gr1 - 1; //vlen дб на 1 меньше
    if >= goto load_vlen;
    gr3 = 0;// vlen не может быть меньше 0
load_vlen:
    vlen = gr3;//Загрузим длину
    //0
    ar3 = _zero_flt;
    fpu 0  rep  vlen  vreg0 = [ar3];
	//1
    ar3 = _one_flt;
    fpu 0  rep  vlen  vreg1 = [ar3];

	//X = 1
	fpu 1  vreg1 = fpu 0 vreg1;
	//Входное значение Y
    ar3 = ar4;
    fpu 1  rep  vlen  vreg5 = [ar3++];//Оригинальный Y для восстановления знака результата
    fpu 1  .float vreg2 = /vreg5/;//Модуль Y для расчетов

    //sum_angle = 0
    fpu 0  vreg7 = vreg0;//Выходной вектор

    //ЦИКЛ
    gr0 = 23;//23 - длина мантиссы
    ar0 = _tanTableF;//Таблица тангенсов
    ar1 = _angTableF;//Таблица углов
arctan_cycle:
    fpu 0  rep vlen vreg2 = [ar0];
    ar0+=2; //загружаем по 2
    fpu 0  rep vlen vreg3 = [ar1];
    ar1+=2; //загружаем по 2


    //s = copysign(1, y)
    fpu 0  vreg6 = fpu 1 vreg2;
    fpu 0  vreg4 = fpu 0 vreg1;
    fpu 0  .float vreg6 + vreg6, set mask if <;
    fpu 0  .float vreg4 = mask ? - vreg4 : vreg4;

    //Xnew = x + s*y*t;
    fpu 0  vreg5 = fpu 1 vreg1;//x

    #fpu 0  vreg6 = fpu 1 vreg2;//y
    fpu 0  .float vreg6 = vreg6 * vreg4;//y*s
    fpu 0  .float vreg6 = vreg6 * vreg2 + vreg5;//y*s*t + x
    fpu 1  vreg3 = fpu 0 vreg6;//Xnew

    //Ynew = y - s*x*t;
    #fpu 0  vreg5 = fpu 1 vreg1;//x
    fpu 0  vreg6 = fpu 1 vreg2;//y
    fpu 0  .float vreg5 = vreg5 * vreg4;//x*s
    fpu 0  .float vreg5 = -vreg5 * vreg2 + vreg6;//-x*s*t + y
    fpu 1  vreg4 = fpu 0 vreg5;//Ynew

     //sum_angle = sum_angle + s*a;
    fpu 0  .float vreg7 = vreg4 * vreg3 + vreg7;//s*a


	//x =  Xnew;
	fpu 1 vreg1 = fpu 1  vreg3;
	//y =  Ynew;
	fpu 1 vreg2 = fpu 1 vreg4;
	gr0 = gr0 - 1;
	if > goto arctan_cycle;

	//Обработаем NAN и INF
	fpu 0 vreg5 = fpu 1 vreg5;//Оригинальный вектор
    fpu 0 .float vreg5 - vreg5, set mask if <>0;
    fpu 0 .float vreg7 = mask ? vreg5 : vreg7; //Для nan & inf восстановим изначальные значения

	//Бесконечности обработаем используя функцию замены на значение
	/*	ar0 - input vector
		ar1 - changing value
		vlen - length of vector
		vreg7 - out vector*/
	ar3 = ar2;
    fpu 0 rep vlen [ar3++] = vreg7;
    ar0 = ar2;
    ar1 = _half_pi_flt; //arctan(inf) = pi/2
	call __macro_change_infinityF32;

    //Восстановим исходный знак
    fpu 0 vreg6 = fpu 1 vreg5;
    fpu 0 .float vreg6 + vreg6, set mask if <;
    fpu 0 .float vreg7 = mask ? -vreg7 : vreg7;
    //fpu 0 rep vlen [ar3++] = vreg7;


exit:
    ar7 = ar7 - 66;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;

