
.global _vec_handler32
.global __test_func_vh32

.data

  .align 8

SBx2:
	  .quad 0x200000002 // 2 строки
NB:
      .quad 0x8000000000000000 // 1 столбец
WBhi:
      .quad 0x0000000100000000
      .quad 0x0000000000000000
WBlow:
      .quad 0x0000000000000000
      .quad 0x0000000000000001

.text


__test_func_vh32:
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	push ar6, gr6;
	gr3 = 1;
	gr2 and gr3;
	
	if =0 delayed goto test_even;
	gr3 = gr2;
	nul;
	
	gr3 = gr3 + 1;
test_even:
	gr3 = gr3 >> 1;
	gr3 = gr3 - 1;
	vlen = gr3;
	ar5 = ar4;
	fpu 0 rep vlen vreg7 = [ar5++]; 
	

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
	@func int vec_handler32(int* func, int* in, int* out, int lenght)

	Циклическая проверка на четность и нечетность адресов для векторов с элементами размероностью 32 бита.
	Происходит организация цикла с выделением подвектора не более 64 элемента, запуск переданной функции,
	а так же проверка на корректность переданных адресов и длины векторов
	
	@param ar0 Адрес запускаемой функции для подвектора
	@param ar1 Адрес входного вектора
	@param ar2 Адрес выходного вектора
	@param gr1 Длина вектора в 32разрядных словах

*/
_vec_handler32:


    ar5 = ar7 - 2;
    
    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar6, gr6;
    
    ar0 = [--ar5]; // function
    ar1 = [--ar5]; // input vector
    ar2 = [--ar5]; // output vector
	gr1 = [--ar5]; // lenght


    ar3 = ar7 + 2;
    // ar3 - рабочий массив на 66 слов
    // ar3 + 68 - 2ой рабочий массив на 66 слов
    ar7 = ar7 + 134;
    
    
    gr7 = 0; //Значение по умолчанию
	gr1;
    if <= goto err_size;
    gr0 = ar1;
    gr0;
    if =0 goto err_ptr;
    gr0 = ar2;
    gr0;
    if =0 goto err_ptr;
    
main_loop:    
    gr2 = 64;
    gr1 - gr2;
    if >= goto after_size_correction;
    //Оставшийся размер меньше 64
    gr2 = gr1;
after_size_correction:  
	gr3 = 1;
	gr0 = ar1;
	gr0 and gr3;
	if =0 delayed goto even_adr1_check;
	ar4 = ar1;
	nul;
	
	################################################
	##Копирование входной информации в четный буфер
	################################################
	//Первый адрес нечетный, необходимо провести сдвиг
    sir = [NB];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar5 = WBhi;
    rep 2 wfifo = [ar5++], ftw, wtw; // Загрузка матрицы  весов
    

    //Выделяем старшие слова
	ar5 = ar1;
	ar5 = ar5 - 1;
	rep 32 ram = [ar5++];
	rep 32 with vsum, ram, 0;
    //rep 32 data = [ar5++] with vsum, data, 0;
    ar5 = ar3;
    rep 32 [ar5++] = afifo;

    //Если адрес нечетный, можем обработать максимум 63
    gr5 = 63;
    gr2 - gr5;
    if < goto L1notnul;
    gr2 = 63;
    //+ в таком случае обнуляем старшее слово
    gr5 = 64;
    ar5 = ar3;
    ar5 = ar5 + gr5 with gr5 = false;
    ar5 = ar5 + 2;
    [--ar5] = gr5;
    [--ar5] = gr5;
L1notnul:
    //Выделяем младшие слова
	ar5 = WBlow;
    rep 2 wfifo = [ar5++], ftw, wtw; // Загрузка матрицы  весов
    ar5 = ar1;
	ar5 = ar5 - 1;
    //rep 32 data = [ar5++] with vsum, data, 0;
    rep 32 ram = [ar5++];
    rep 32 with vsum, ram, 0;
    ar5 = ar3 + 2;//Загрузка со смещением в 1 слово
    //rep 32 data = [ar5++] with data or afifo; //Сложение
    rep 32 ram = [ar5++];
    rep 32 with ram or afifo; //Сложение
    ar5 = ar3;//Выгрузка полученных данных
    rep 32 [ar5++] = afifo;
    ar4 = ar3;
    
    gr3 = 1;
    gr2 and gr3;
    if =0 goto call_func;
    //Если размер нечетный, занулим последнее слово
    gr3 = gr2;
    gr5 = false;
    [ar3+gr3] = gr5;
    
    goto call_func;

even_adr1_check:
    //Четный адрес входных данных
    //по умолчанию используем данные прямо со входного адреса
    gr3 = 1;
    gr2 and gr3;
    if =0 goto call_func;
    //Но если размер нечетный, перекопируем и занулим последнее слово
    //чтобы в исполняему функцию не попал мусор из стека
    ar5 = ar1;
    rep 32 data = [ar5++] with data + 0;
    ar5 = ar3;
    rep 32 [ar5++] = afifo;
    
    gr3 = gr2;
    gr5 = false;
    [ar3+gr3] = gr5;
    ar4 = ar3;
	
call_func:
	
	//FIXME Подготовка аргументов
    //ar0 = __test_func;
    call ar0; //Вызов функции
    //Результат в fpu 0 vreg7
    //Откорректируем входной адрес для следующей итерации
    gr5 = ar1;
    gr5 = gr5 + gr2;
    ar1 = gr5;

	gr0 = ar2;
	gr3 = 1;
	gr3 and gr0;
	if =0 goto even_adr2;

	######################################################
	##Копирование выходной информации по нечетному адресу
	######################################################
	gr3 and gr2;
    if =0 delayed goto L2even_output_size;
	gr3 = gr2 >> 1;
	nul;
	gr3 = gr3 + 1;
L2even_output_size:
    gr3 = gr3 - 1;
    vlen = gr3;
    ar5 = ar3;
    fpu 0 rep vlen [ar5++] = vreg7;
    //Сохраним первое слово по нечетному адресу
    gr0 = [ar3];
    [ar2] = gr0;
    ar2 = ar2 + 1; // Теперь адрес четный

	gr5 = 1;
	gr1 - gr5;
	if =0 goto exit;//Скопировано последнее слово

    gr3;
    if =0 delayed goto L2_last_word_copy;//Копируем 2 слова по нечетному адресу, сдвигать не нужно
	gr3 = gr2 - 1;
	nul;


    //Копировать остаток надо с нечетного адреса

    //Т.е. через сдвиг
    sir = [NB];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar5 = WBhi;
    rep 2 wfifo = [ar5++], ftw, wtw; // Загрузка матрицы  весов

    //Выделяем старшие слова
	ar5 = ar3;
	rep 32 ram = [ar5++];
	rep 32 with vsum, ram, 0;
    //rep 32 data = [ar5++] with vsum, data, 0;
    ar5 = ar3+68;
    rep 32 [ar5++] = afifo;
    //Обнуляем последнее слово в массиве
    ar5 = ar3 + 134;//68 + 66
         with gr5 = false;
    [--ar5] = gr5;
    [--ar5] = gr5;
    //Выделяем младшие слова
	ar5 = WBlow;
    rep 2 wfifo = [ar5++], ftw, wtw; // Загрузка матрицы  весов
	ar5 = ar3;
	rep 32 ram = [ar5++];
	rep 32 with vsum, ram, 0;
    //rep 32 data = [ar5++] with vsum, data, 0;
 /*   ####################
    gr5 = 10;
    gr1 - gr5;
    if > goto Continue_debug;
    rep 32 [ar2++] = afifo;
    goto exit;
    Continue_debug:

    ####################*/



    ar5 = ar3 + 70;//Загрузка со смещением в 1 слово
	rep 32 ram = [ar5++];
    rep 32 with ram or afifo; //Сложение
    //rep 32 data = [ar5++] with data or afifo; //Сложение
    ar5 = ar3;//Выгрузка полученных данных
    rep 32 [ar5++] = afifo;

	gr3 = gr2 - 1; //На 1 меньше, т.к. первое слово уже скопировано
    gr3 = gr3 >> 1; //Последнее слово для нечетного значения учтем позже
    gr3 = gr3 - 1;
    vlen = gr3;
    ar5 = ar3;
    fpu 0 rep vlen vreg7 = [ar5++] ;
    fpu 0 rep vlen [ar2++] = vreg7;
    //Возможно надо скопировать еще одно слово
	gr3 = gr2 - 1;
	gr0 = 1;
	gr3 and gr0;
	if =0 goto next_iteration;//Копирование не нужно
	gr3 = gr3 - 1;
L2_last_word_copy:
	gr5 = [ar3 + gr3];
	[ar2] = gr5;
	ar2 = ar2 + 1; //На следующей итерации снова будет нечетный адрес, что печально

	goto next_iteration;


even_adr2:
	gr2 and gr3;
	if =0 delayed goto simple_save;
    gr3 = gr2 >> 1;
    nul;

	gr1 - gr2;
	if > delayed goto simple_save;
	gr3 = gr2 + 1;
    gr3 = gr3 >> 1;
	######################################################
	##Копирование выходной информации через буфер
	##Если размер нечетный, то копировать надо через буфер, дабы
	##не затереть данные, расположенные после последнего слова выходного вектора
	######################################################
    gr3 = gr2 >> 1;
    gr3;
    if =0 delayed  goto save_last_word;//Копирование 1 слова - исключительная ситуация
    ar5 = ar3;
    nul;

    //gr3 = gr3 - 1;
    vlen = gr3;
    fpu 0 rep vlen [ar5++] = vreg7;

	gr3 = gr3 - 1;
    vlen = gr3;
    ar5 = ar3;
    fpu 0 rep vlen vreg7 = [ar5++];
    fpu 0 rep vlen [ar2++] = vreg7;
    //Сохраняем последнее слово
save_last_word:
    gr5 = [ar5];
    [ar2] = gr5;
    ar2 = ar2 + 1;
	goto next_iteration;

simple_save:
    gr3 = gr3 - 1;
    vlen = gr3;
    fpu 0 rep vlen [ar2++] = vreg7;
    gr3 = 1;
    gr2 and gr3;
    if =0 goto next_iteration;
    ar2 = ar2 - 1;

next_iteration:
    gr1 = gr1 - gr2;
    if > goto main_loop;
	goto exit;
	
err_size:
    gr7 = -6;
    goto exit;
err_ptr:
    gr7 = -8;
    goto exit;
exit:
    ar7 = ar7 - 134;
    pop ar6, gr6;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return; 
