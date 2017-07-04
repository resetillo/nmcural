.global _nmppsSqrt_32f
.global _square_root32f


.global _half_flt
.global _two_flt
.global _nan_flt

.global SBx2
.global NBx2
.global WB2x2
.global SIGN_BIT_flt
.global DpCode_const_flt

.data

  .align 8

SBx2:
	  .quad 0x200000002 // 2 строки
NBx2:
      .quad 0x80000000 // 2 столбца
WB2x2:
      .quad 0x0000000000000001
      .quad 0x0000000100000000
BIAS:
	  .quad 0x3f8000003f800000
SIGN_BIT_flt:
      .quad 0x7fffffff7fffffff
DpCode_const_flt:
	  .quad 0x8100000081000000

.text


#include <nmpps_asm_defs.h>

_nmppsSqrt_32f:

    ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;

    ar0 = [--ar5]; // Входящий вектор
    ar1 = [--ar5]; // Результирующий вектор
	gr0 = [--ar5]; // Размер

	call _square_root32f;

	pop ar1, gr1;
	pop ar0, gr0;

	return;


/*
	ar0 input adr
	ar1 output adr
	gr0 lenght
*/

_square_root32f:
    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;


	ar6 = ar7 + 2;
	#define mass1  ar6
	#define mass2  ar6 + 64
	ar7 = ar7 + 130;

	gr5 = ar0;
	gr5;
	if =0 delayed goto exit;
	gr7 = nmppsStsNullPtrErr;
	gr5 = ar1;

	gr5;
	if =0 delayed goto exit;
	gr0;
	nul;

	if <= delayed goto exit;
	gr7 = nmppsStsSizeErr;
	nul;

	gr7 = nmppsStsNoErr; //0 по умолчанию


	//Выделение старших 63 бит
    sir = [NBx2];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar5 = WB2x2;
    rep 2 wfifo = [ar5++], ftw, wtw; // Загрузка матрицы  весов

	//Разовая загрузка
	gr4 = 64;
	gr4 - gr0;
	if > goto main_loop;
		gr5 = 31;
		vlen = gr5;
		ar5 = _two_flt;
		fpu 0 rep vlen vreg6 = [ar5];//2
		ar5 = _half_flt;
		fpu 0 rep vlen vreg5 = [ar5];//0.5
		ar5 = _nan_flt;
	    fpu 0 rep vlen vreg4 = [ar5];

main_loop:
	gr4 - gr0;
	if < goto after_correct;
		//Размер меньше 64
		gr6 = gr0 >> 1;
		gr5 = 1;
		gr0 and gr5;
		if =0 delayed goto M1;
		gr6 = gr6 - 1;
		vlen = gr6;
			//Размер нечетный, надо убедиться, что в лишнем загружаемом слове не было мусора
			//Для этого копируем через буфер
			gr0 - gr5; //len ? 1
			if =0 delayed goto L1_last_word;
			ar5 = mass2;
			nul;
				rep vlen vreg0 = [ar0++];
				rep vlen [ar5++] = vreg0;
			L1_last_word:
				gr5 = [ar0];
				[ar5++] = gr5;
				gr5 = false;
				[ar5] = gr5; //Зануляем лишнее слово
				ar0 = mass2; //Подмена адреса
				//Обновлеям размер
				gr6 = gr0 >> 1;
				vlen = gr6;
		M1:
		ar5 = _two_flt;
		fpu 0 rep vlen vreg6 = [ar5];//2
		ar5 = _half_flt;
		fpu 0 rep vlen vreg5 = [ar5];//0.5
		ar5 = _nan_flt;
	    fpu 0 rep vlen vreg4 = [ar5];//nan

	    gr5 = 0;
	    sir = gr5;
	    fp0_lmask = sir;
	    fp0_hmask = sir;


after_correct:

    //Вычисление приближенного значения X = ~sqrt(x)
	ar5 = BIAS;
	rep 32 ram = [ar5];
	ar5 = ar0; //Входной адрес
    rep 32 data = [ar5++] with data - ram; //Вычитаем BIAS

    rep 32 with vsum, shift afifo, 0; //Сдвигаем вправо на 1
    rep 32 with afifo + ram; //Прибавляем BIAS
    ar5 = SIGN_BIT_flt;
    rep 32 data = [ar5] with afifo and data;//Приводим к положительному

    //Сохранение результата X = ~sqrt(x), он нам понадобится дальше
	ar5 = mass1;
    rep 32 [ar5++] = afifo;
	ar5 = mass1;
	########################################
	fpu 0 rep vlen vreg1 = [ar5++];//X0
	########################################


    //Вычисление приближенного значения Y = 1/~sqrt(x)
	ar5 = mass1;
	rep 32 data = [ar5++] with not data;
    ar5 = DpCode_const_flt;
    rep 32 data = [ar5] with afifo - data; // 1/x ~ допкоду экспоненты x
    //Сохранение результата Y = 1/~sqrt(x)
	ar5 = mass1;
	rep 32 [ar5++] = afifo;

	########################################
	ar5 = mass1;
	fpu 0 rep vlen vreg2 = [ar5++];//Y

	fpu 0 rep vlen vreg0 = [ar0++];//A


	//Уточним значение
	//Y0 = (2.0 - X0*Y)*Y
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;
	
	//Первая итерация
	//X1 = 0.5*(X0 + A*Y0)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg1 = vreg5*vreg3;
	//Уточним значение Y1 = 1/X1
	//Y1_ = (2.0 - X1*Y0)*Y0
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;
	//Y1 = (2.0 - X1*Y1_)*Y1_
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;


	//Вторая итерация
	//X2 = 0.5*(X1 + A*Y1)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg1 = vreg5*vreg3;
	//Уточним значение Y2 = 1/X2
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	//3я итерация
	//X3 = 0.5*(X2 + A*Y2)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg1 = vreg5*vreg3;
	//Уточним значение Y3 = 1/X3
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	//4я итерация
	//RESULT = 0.5*(X3 + A*Y3)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg7 = vreg5*vreg3;

	//Анализ входного вектора

    //проверка на nan & inf
    fpu 0 .float vreg0 - vreg0, set mask if <>0;
    fpu 0 .float vreg7 = mask ? /vreg0/ : vreg7;

	//проверка на 0
    fpu 0 .float vreg0 + vreg0, set mask if =0;
    fpu 0 .float vreg7 = mask ? vreg0 : vreg7;

	//проверка на отрицательные
    fpu 0 .float vreg0 + vreg0, set mask if <;
    sir = fp0_lmask;
    gr5 = sir;
    sir = fp0_hmask;
    gr6 = sir;
    fpu 0 .float vreg7 = mask ? vreg4 : vreg7;
    gr5 or gr6;
    if =0 goto save_result;
	gr7 = nmppsStsSqrtNegArg; //Отрицательное число
save_result:
	//Результат в vreg7
	gr0 - gr4;
	if > delayed goto save_result_normal;
		ar5 = mass1;
		fpu 0 rep vlen [ar5++] = vreg7;

		gr5 = 1;
		gr0 and gr5;
		if =0 goto save_result_normal;
		//Размер нечетный, надо извращаться, дабы не потереть лишнее слово в выходном буфере
		gr0 - gr5;
		if =0 delayed goto save_last_word;
			ar5 = mass1;
			nul;
			//Копируем через буфер
			gr6 = gr0 >> 1;
			gr6 = gr6 - 1;
			vlen = gr6;
			fpu 0 rep vlen vreg7 = [ar5++];
			fpu 0 rep vlen [ar1++] = vreg7;

		save_last_word:
			gr5 = [ar5];
			[ar1] = gr5;
			goto exit; //Копирование последнего куска информации, можно выходить


save_result_normal:
	fpu 0 rep vlen [ar1++] = vreg7;
	gr0 = gr0 - gr4;
	if > goto main_loop;
	
exit:
	ar7 = ar7 - 130;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    return; 
