


.global _nmppsNormalize_32f
.global _nmppsNormalize_32fc

.global nmppsDivC_32f_body


.text


/**
	nmppsStatus = nmppsNormalize_32f(const nmpps32f*  pSrc, nmpps32f* pDst,     int len,  nmpps32f  vSub, nmpps32f vDiv)

	 pDst[n] = (pSrc[n] - vSub) / vDiv;

*/

_nmppsNormalize_32f:


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
	gr3 = [--ar5]; //vSub
	gr2 = [--ar5]; //vDiv


	ar3 = ar7 + 2;//vSub
	ar4 = ar7 +4;
	ar7 = ar7 + 68;

	[ar3] = gr3;
	[ar3 + 1] = gr3;

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
	gr5 = 64;
	gr0 - gr5;
	if <= goto loop_sub;
		fpu 0 rep 32 vreg1 = [ar3];//Загрузка vSub
		gr4 = 31;
		vlen = gr4;
loop_sub:
	gr0 -gr5;
	if > goto after_correct;
		gr3 = gr0 >> 1;
		gr4 = 1;
		gr4 and gr0;
		if <>0 goto M1;
		gr3 = gr3 - 1; //Размер четный, уменьшим значение для определения VL
		M1:
		vlen = gr3;
		fpu 0 rep vlen vreg1 = [ar3];//Загрузка vSub
after_correct:
	fpu 0 rep vlen vreg2 = [ar2++];//Загрузка Src
	fpu 0 .float vreg2 = vreg2 - vreg1;


	//Выгрузка
	gr0 - gr5;
	if > goto upload_f;
	gr4 = 1;
	gr0 and gr4;
	if =0 goto upload_f;
		//Размер нечетный выгружать надо через буфер
		ar5 = ar4;
		fpu 0 rep vlen [ar5++] = vreg2;
		gr0 - gr4;
		if =0 goto upload_last_word;
			gr4 = VL;
			gr4 = gr4 - 1;
			vlen = gr4;

			ar5 = ar4;
			fpu 0 rep vlen vreg2 = [ar5++];

			fpu 0 rep vlen [ar0++] = vreg2;

		upload_last_word:
			gr4 = gr0 - 1;
			ar5 = ar4 + gr4;
			gr4 = [ar5];
			[ar0++] = gr4;
	goto Divide_f;

	upload_f: //Обычная выгрузка
	fpu 0 rep vlen [ar0++] = vreg2;

	gr0 = gr0 - gr5; // len - 64
	if > goto loop_sub;

	##################################
	##Деление
	##################################

Divide_f:
/*

	ar1  Divided vector
    gr2  Divisor
    ar0  Output vector
	gr1  Lenght

*/
	ar0 = ar6;
	ar1 = ar6;
	call nmppsDivC_32f_body;

exit:
	ar7 = ar7 - 68;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;




    /**
	nmppsStatus = nmppsNormalize_32fc(const nmpps32fc*  pSrc, nmpps32fc* pDst,     int len,  nmpps32fc  vSub, nmpps32f vDiv)

	 pDst[n] = (pSrc[n] - vSub) / vDiv;

*/

_nmppsNormalize_32fc:


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
	gr2 = [--ar5]; //vDiv

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


	##################################
	##Вычитание
	##################################
	ar6 = ar0;
	gr0 = gr1;//Копируем длину
	gr5 = 32;
	gr0 - gr5;
	if <= goto loop_subfc;
		//Подготовка вектора
		gr3 = 31;
		vlen = gr3;
		fpu 0 rep vlen vreg1 = [ar3];//Загрузка vSub

loop_subfc:
	gr0 -gr5;
	if > goto after_correctfc;
		gr3 = gr0 - 1;
		vlen = gr3;
		fpu 0 rep vlen vreg1 = [ar3];//Загрузка vSub

after_correctfc:
	fpu 0 rep vlen vreg2 = [ar2++];//Загрузка Src
	fpu 0 .float vreg2 = vreg2 - vreg1;
	fpu 0 rep vlen [ar0++] = vreg2;//Выгрузка

	gr0 = gr0 - gr5; //len - 32
	if > goto loop_subfc;

	##################################
	##Деление
	##################################
/*
	ar1  Divided vector
    gr2  Divisor
    ar0  Output vector
	gr1  Lenght

*/
	gr1 = gr1 << 1; //Длина в 2 раза больше, т.к. это комплексные числа
	ar0 = ar6;
	ar1 = ar6;
	call nmppsDivC_32f_body;

exitfc:
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;
