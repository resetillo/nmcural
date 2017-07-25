//
.global _nmppsDivC_64f
.global nmppsDivC_64f_body

.global _zero_dbl
.global _two_dbl
.global _bigest_dbl
.global _nan_dbl
.global _inf_dbl
.global SIGN_BIT_dbl
.global DpCode_const_dbl

.global NB_default
.global SB_default
.global WB_default


.text
/**
@function nmppsDiv_64f
*/
_nmppsDivC_64f:

    ar5 = ar7 - 2;

    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;

    ar1 = [--ar5]; // Divided vector
    ar5 = ar5 - 1;
    gr3 = [--ar5]; // Divisor
    gr2 = [--ar5];
    ar0 = [--ar5]; // Output vector
	gr1 = [--ar5]; // Lenght

	gr1;
    if <= delayed goto exit;
    gr7 = -6;

    gr0 = ar0;
    gr0;
    if =0 delayed goto exit;
    gr7 = -8;

    gr0 = ar1;
    gr0;
    if =0 goto exit;

	gr7 = 0; //Значение по умолчанию

	call nmppsDivC_64f_body;

exit:
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;


/*
	Метка для использования из других функций
	ar1 Divided vector
    gr2,gr3 Divisor (low, hi)
    ar0 Output vector
	gr1 Lenght

*/
nmppsDivC_64f_body:
	push ar0, gr0;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

	ar3 = ar7 + 2; //Технологический массив на 64 слова
	ar2 = ar7 + 66; //DivisorAdr
	ar4 = ar7 + 68; //ObrDivisorAdr
	ar7 = ar7 + 70;

	[ar2] = gr2;
	[ar2+1] = gr3;

	//Настройка векторника
    sir = [NB_default];
    nb1 = sir;
    sir = [SB_default];
    sb = sir;
	ar5 = WB_default;
    rep 1 wfifo = [ar5], ftw, wtw; // Загрузка матрицы  весов

	gr0 = 0;// Здесь будут аккумулироваться признаки делений на 0


calc_obr:
	ar5 = _two_dbl;
	fpu 0 rep 1 vreg2 = [ar5]; //2.0

	//Рассчет приближенного значения ~1/divisor
	rep 1 data = [ar2] with not data;
    ar5 = DpCode_const_dbl;
    rep 1 data = [ar5] with afifo - data; // ~1/divisor ~ допкоду экспоненты divisor
    //Сохранение результата ~1/divisor
	rep 1 [ar4] = afifo;


	fpu 0 rep 1 vreg1 = [ar2]; //divisor
	fpu 0 rep 1 vreg7 = [ar4]; //~1/divisor

	//Уточняем значение
	//~1/divisor = (2.0 - (~1/divisor)*divisor)*(~1/divisor);
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//2
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//3
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//4
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//5
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//6
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;

	fpu 0 rep 1 [ar4] = vreg7; //~1/divisor


	gr3 = 32;
	gr3 - gr1;
	if > goto main_loop;
	/*
		vreg0 tmp / divided
		vreg1 divisor
		vreg2 2.0 / (~1/divisor)
		vreg3 bigest
		vreg4 zero
		vreg5 nan
		vreg6 infinity
		vreg7 result
	*/
	//Загружаем данные, используемые каждую итерацию
	ar5 = _bigest_dbl;
	fpu 0 rep 32 vreg3 = [ar5]; //bigest double
	ar5 = _zero_dbl;
	fpu 0 rep 32 vreg4 = [ar5]; //zero double
	ar5 = _nan_dbl;
	fpu 0 rep 32 vreg5 = [ar5]; //nan double
	ar5 = _inf_dbl;
	fpu 0 rep 32 vreg6 = [ar5]; //infinity double

	fpu 0 rep 32 vreg1 = [ar2]; // divisor
	fpu 0 rep 32 vreg2 = [ar4]; //~(1/divisor)
	gr3 = 31;
	vlen = gr3;


main_loop:
	gr3 = 32; //Остаток
	gr3 - gr1;
    if <= goto after_correct;
    //Остаток меньше 32, ограничиваем обрабатываемый размер
    //Размер вектора меньше 32
	gr3 = gr1 - 1;
	vlen = gr3;
	//Обновляем данные в соответствии с размером вектора
	ar5 = _bigest_dbl;
	fpu 0 rep vlen vreg3 = [ar5]; //bigest double
	ar5 = _zero_dbl;
	fpu 0 rep vlen vreg4 = [ar5]; //zero double
	ar5 = _nan_dbl;
	fpu 0 rep vlen vreg5 = [ar5]; //nan double
	ar5 = _inf_dbl;
	fpu 0 rep vlen vreg6 = [ar5]; //infinity double

	fpu 0 rep vlen vreg1 = [ar2]; // divisor
	fpu 0 rep vlen vreg2 = [ar4]; //~(1/divisor)

after_correct:

	//Output = divided*(~1/divisor)
	ar5 = ar1;
	fpu 0 rep vlen vreg0 = [ar5++]; //divided
	fpu 0 .double vreg7 = vreg0*vreg2;

	######################################
	##   Проверки аргументов
	######################################
	//Проверки на бесконечность
	fpu 0 .double vreg0 = /vreg0/; //О знаке позаботимся в конце
	fpu 0 .double vreg3 - vreg0, set mask if <;
    sir = fp0_dmask;
    gr3 = sir; //маска с divided = infinity

	fpu 0 .double vreg1 = /vreg1/;//О знаке позаботимся в конце
	fpu 0 .double vreg3 - vreg1, set mask if <;
    sir = fp0_dmask;
    gr4 = sir; //маска с divisor = infinity


	sir = gr3;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg6 : vreg7; //divided = infinity => out = infinity

	sir = gr4;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg4 : vreg7; //divisor = infinity => out = 0

	gr5 = gr3 and gr4;
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided = divisor = infinity => out = NAN


	//Проверка деления на 0
    fpu 0 .double vreg0 + vreg0, set mask if =0;
    sir = fp0_dmask;
    gr5 = sir;//маска с divided = 0

    fpu 0 .double vreg1 + vreg1, set mask if =0;
    sir = fp0_dmask;
    gr6 = sir;//маска с divisor = 0
    gr0 = gr0 or gr6; //Для определения результата

	//sir = gr6;
	//fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg6 : vreg7; //divisor = 0 => out = infinity

	gr6 = gr5 and gr6;
	sir = gr6;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided = divisor = 0 => out = NAN

	//0 div infinity
	gr6 = gr5 and gr4;
	sir = gr6;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided =0, divisor = infinity => out = NAN


	//Проверка на NAN
    fpu 0 .double vreg0 - vreg0, set mask if <>0;
    sir = fp0_dmask;
    gr5 = sir;//маска с divided = NAN
    gr5 = gr5 and not gr3; //Исключим бесконечности

    fpu 0 .double vreg1 - vreg1, set mask if <>0;
    sir = fp0_dmask;
    gr6 = sir;//маска с divisor = NAN
    gr6 = gr6 and not gr4; //Исключим бесконечности

    gr5 = gr5 or gr6; //Объединим множества
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided = NAN || divisor = NAN => out = NAN



	//divided*divisor для определения знака результата
	ar5 = ar1;
	rep 32 data = [ar5++] with data;
	rep 32 data = [ar2] with data xor afifo; //ксорим биты

	ar5 = SIGN_BIT_dbl;
	rep 32 data = [ar5] with not data and afifo; //Выделяем старший бит

	ar5 = ar3;
	fpu 0 rep vlen [ar5++] = vreg7;
	ar5 = ar3;
	rep 32 data = [ar5++] with data or afifo; //Установка нужных знаков
	//Выгрузка конечных значений
	ar5 = ar3;
	rep 32 [ar5++] = afifo;
	ar5 = ar3;
	fpu 0 rep vlen vreg7 = [ar5++];

	//Увеличиваем адреса для следующей итерации
	gr5 = VL;
	gr5 = gr5 + 1;
	gr5 = gr5 << 1;
	ar5 = ar1;
	ar1 = ar5 + gr5;



save_result:
	fpu 0 rep vlen [ar0++] = vreg7;

    gr2 = 32;
	gr1 = gr1 - gr2;
    if > goto main_loop;

    gr0;
    if =0 goto exit_macro;

    gr7 = -10; //Было деление на 0

exit_macro:
	ar7 = ar7 - 70;


    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar0, gr0;
	return;














