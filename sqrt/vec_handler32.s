
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
    push ar5, gr5;
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
	//Если адрес нечетный, можем обработать максимум 63
    gr5 = 63;
    gr2 - gr5;
    if < goto L1notover63;
    gr2 = 63;
L1notover63:
	//Первый адрес нечетный, необходимо провести сдвиг вправо
	ar5 = ar1 - 1; //Входные данные будут с лишним младшим словом
	gr3 = gr2 + 1;

	gr5 = 1;
	gr5 and gr3;
	if =0 delayed goto L1evenGr3;
	gr3 = gr3 >> 1;
	nul;

	gr3 = gr3 + 1; //Нечетный, надо увеличить на 1
L1evenGr3:
	gr3 = gr3 - 1; //vlen дб на 1 меньше
	vlen = gr3;

	fpu 0 rep vlen vreg0 = [ar5++];

    //Сдвигаем младшие слова в старшую часть
    fpu 0 .packer = vreg0 with .float .in_high <= .float .in_low;
    ar5 = ar3;
    fpu rep vlen [ar5++] = .packer; // выгрузка данных для последующей загрузки со сдвигом в 2 слова

    //обнуляем старшие 2 слова
    ar5 = ar5 + 2;
    gr5 = false;
    [--ar5] = gr5;
    [--ar5] = gr5;
    //Загрузка со смещением
    ar5 = ar3 + 2;
    fpu 0 rep vlen vreg2 = [ar5++];

    //Сдвигаем старшие слова в младшую часть
    fpu 0 .packer = vreg0 with .float .in_low <= .float .in_high;
    fpu 0 rep vlen vreg1 = .packer;
    //Сложение
    fpu 0 .float vreg0 = vreg1 + vreg2;

    ar5 = ar3;//Выгрузка полученных данных
    fpu 0 rep vlen [ar5++] = vreg0;


L1end_lastcopy:

	//Cледующее за последним - обнулим, дабы в функцию не попал мусор из стэка
	ar5 = ar3;
    gr5 = gr2;
    gr4 = false;
    [ar5 + gr5] = gr4;

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
    call ar0; //Вызов функции
    //Результат в fpu 0 vreg7
    //Откорректируем входной адрес для следующей итерации
    gr5 = ar1;
    gr5 = gr5 + gr2;
    ar1 = gr5;


	gr3 = 1;
	gr2 and gr3;
	if <>0 goto L2_buf_copy;

	gr4 = ar2;
	gr3 and gr4;
	if <>0 goto L2_buf_copy;

simple_output:
    //Простое копирование на четный адрес четного кол-ва элементов
	fpu 0 rep vlen [ar2++] = vreg7;
	goto next_iteration;

L2_buf_copy:
	//Копирование через буфер
	ar5 = ar3;
	fpu 0 rep vlen [ar5++] = vreg7; //Сохранение результата в буфер

	gr4 = ar2;
	gr3 and gr4;
	if <>0 goto L2_shift_output;

	gr2 - 1;
	if =0 goto L2_lastword_copy;
	gr3 = gr2 >> 1;
	gr3 = gr3 - 1;
	vlen = gr3;
	ar5 = ar3;
	fpu 0 rep vlen vreg7 = [ar5++];
	fpu 0 rep vlen [ar2++] = vreg7;

L2_lastword_copy:
    //Копирование последнего слова
    gr3 = gr2 -1;
	gr5 = [ar3 + gr3];
	[ar2] = gr5;
	ar2 = ar2 + 1;
	goto next_iteration;


L2_shift_output:
	//Копирование через сдвиг
	//на нечетный адрес

    //Для начала скопируем первое слово
    gr5 = [ar3];
    [ar2] = gr5;
    ar2 = ar2 + 1; //Адрес теперь четный

    gr2 - 1;
    if =0 goto next_iteration; //Первое слово является последним

	gr3 = 2;
    gr2 - gr3;
	if =0 goto L2_lastword_copy; //Первое слово скопировали, осталось последнее (второе)

	//Выходные данные во vreg7
    //Сдвигаем младшие слова в старшую часть
    fpu 0 .packer = vreg7 with .float .in_high <= .float .in_low;
    ar5 = ar3 + 68;
    fpu rep vlen [ar5++] = .packer; // выгрузка данных для последующей загрузки со сдвигом в 2 слова

    //обнуляем старшие 2 слова
    ar5 = ar5 + 2;
    gr5 = false;
    [--ar5] = gr5;
    [--ar5] = gr5;
    //Загрузка со смещением
    ar5 = ar3 + 70;
    fpu 0 rep vlen vreg2 = [ar5++];

    //Сдвигаем старшие слова в младшую часть
    fpu 0 .packer = vreg7 with .float .in_low <= .float .in_high;
    fpu 0 rep vlen vreg1 = .packer;
    //Сложение
    fpu 0 .float vreg0 = vreg1 + vreg2;

    ar5 = ar3 + 68;//Выгрузка полученных данных
    fpu 0 rep vlen [ar5++] = vreg0;

	//Сохраняемая длина может быть меньше длины выходного вектора
    gr3 = gr2 - 1;
    gr3 = gr3 >> 1;
    gr3 = gr3 - 1;
    vlen = gr3;

    ar5 = ar3 + 68;
    fpu 0 rep vlen vreg0 = [ar5++];
    fpu 0 rep vlen [ar2++] = vreg0 ;

	gr3 = 1;
	gr2 and gr3;
	if =0 goto L2_lastword_copy;//Необходимо скопировать последнее слово

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
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return; 
