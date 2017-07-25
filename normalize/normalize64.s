
.global _nmppsNormalize_64f
.global _nmppsNormalize_64fc

.global nmppsDivC_64f_body


.text


/**
	nmppsStatus = nmppsNormalize_64f(const nmpps64f*  pSrc, nmpps64f* pDst,     int len,  nmpps64f  vSub, nmpps64f vDiv)

	 pDst[n] = (pSrc[n] - vSub) / vDiv;

*/

_nmppsNormalize_64f:


    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

	ar2 = [--ar5]; //pSrc
	ar0 = [--ar5]; //pDst
	gr1 = [--ar5]; //len
	ar5= ar5 - 1;
	gr5 = [--ar5]; //vSub
	gr4 = [--ar5];
	gr3 = [--ar5]; //vDiv
	gr2 = [--ar5]; //vDiv


	ar3 = ar7 + 2;//vSub
	//ar4 = ar7 + 4;//vDiv
	ar7 = ar7 + 6;

	[ar3] = gr4;
	[ar3 + 1] = gr5;
	[ar4] = gr2;
	[ar4 + 1] = gr3;

	gr1;
    if <= delayed goto exit;
    gr7 = -6;

    gr0 = ar0;
    gr0;
    if =0 delayed goto exit;
    gr7 = -8;

    gr0 = ar2;
    gr0;
    if =0 goto exit;

	gr7 = 0; //Значение по умолчанию

	##################################
	##Вычитание
	##################################
	ar6 = ar0;
	gr0 = gr1;//Копируем длину
	gr5 = 32;
	gr0 - gr5;
	if <= goto loop_sub;
		fpu 0 rep 32 vreg1 = [ar3];//Загрузка vSub
		gr5 = 31;
		vlen = gr5;
loop_sub:
	gr5 = 32;
	gr0 -gr5;
	if > goto after_correct;
		gr5 = gr0 - 1;
		vlen = gr5;
		fpu 0 rep vlen vreg1 = [ar3];//Загрузка vSub
after_correct:
	fpu 0 rep vlen vreg2 = [ar2++];//Загрузка Src
	fpu 0 .double vreg2 = vreg2 - vreg1;
	fpu 0 rep vlen [ar0++] = vreg2;//Выгрузка

	gr5 = 32;
	gr0 = gr0 - gr5;
	if > goto loop_sub;

	##################################
	##Деление
	##################################
/*
	ar1 Divided vector
    gr2,gr3 Divisor (low, hi)
    ar0 Output vector
	gr1 Lenght

*/
	ar0 = ar6;
	ar1 = ar6;
	call nmppsDivC_64f_body;

exit:
	ar7 = ar7 - 6;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;




    /**
	nmppsStatus = nmppsNormalize_64fc(const nmpps64fc*  pSrc, nmpps64fc* pDst,     int len,  nmpps64fc  vSub, nmpps64f vDiv)

	 pDst[n] = (pSrc[n] - vSub) / vDiv;

*/

_nmppsNormalize_64fc:


    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

	ar2 = [--ar5]; //pSrc
	ar0 = [--ar5]; //pDst
	gr1 = [--ar5]; //len
	ar3 = [--ar5]; //vSub
	gr3 = [--ar5]; //vDiv
	gr2 = [--ar5]; //vDiv

	ar4 = ar7 + 2; //Служебный массив
	ar7 = ar7 + 66;

	//Проверки входных аргументов
	gr1;
    if <= delayed goto exitfc;
    gr7 = -6;

    gr0 = ar0;
    gr0;
    if =0 delayed goto exitfc;
    gr7 = -8;

    gr0 = ar2;
    gr0;
    if =0 goto exitfc;

	gr7 = 0; //Значение по умолчанию

	gr1 = gr1 << 1; //Длина в 2 раза больше, т.к. это комплексные числа

	##################################
	##Вычитание
	##################################
	ar6 = ar0;
	gr0 = gr1;//Копируем длину
	gr5 = 32;
	gr0 - gr5;
	if <= goto loop_subfc;
		//Подготовка вектора
		ar5 = ar3;
		fpu 0 rep 2 vreg1 = [ar5++];//Загрузка vSub
		ar5 = ar4;

		//16 пар двойных слов
		.rept 16
		fpu 0 rep 2 [ar5++] = vreg1;
		.endr

		ar5 = ar4;
		fpu 0 rep 32 vreg1 = [ar5++];//Загрузка vSub

		gr5 = 31;
		vlen = gr5;
loop_subfc:
	gr5 = 32;
	gr0 -gr5;
	if > goto after_correctfc;
		ar5 = ar3;
		fpu 0 rep 2 vreg1 = [ar5++];//Загрузка vSub
		gr5 = gr0;
		ar5 = ar4;
		gr4 = 2;
		loop_last_len_fc:

			fpu 0 rep 2 [ar5++] = vreg1;
			gr5 = gr5 - gr4;
			if > goto loop_last_len_fc;

		gr5 = gr0 - 1;
		vlen = gr5;

		ar5 = ar4;
		fpu 0 rep vlen vreg1 = [ar5++];//Загрузка остаточной vSub
after_correctfc:
	fpu 0 rep vlen vreg2 = [ar2++];//Загрузка Src
	fpu 0 .double vreg2 = vreg2 - vreg1;
	fpu 0 rep vlen [ar0++] = vreg2;//Выгрузка

	gr5 = 32;
	gr0 = gr0 - gr5;
	if > goto loop_subfc;

	##################################
	##Деление
	##################################
/*
	ar1 Divided vector
    gr2,gr3 Divisor (low, hi)
    ar0 Output vector
	gr1 Lenght

*/
	ar0 = ar6;
	ar1 = ar6;
	call nmppsDivC_64f_body;

exitfc:
	ar7 = ar7 - 66;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
