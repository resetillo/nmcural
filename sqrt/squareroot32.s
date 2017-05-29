.global _square_root32f
.global _half_flt
.global _two_flt
.global _nan_flt

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
SIGN_BIT:
      .quad 0x7fffffff7fffffff
DpCode_const:
	  .quad 0x8100000081000000

.text

_square_root32f:
    //ar4  input data
	//gr2  lenght
    
    // Сохранение в стеке регистров, чтобы исключить их повреждение
    push ar2, gr2;
    push ar3, gr3;
    push ar5, gr5;
    push ar4, gr4;
    push ar6, gr6;


	ar5 = ar7 + 2;
	ar6 = ar5 + 64;
	ar7 = ar7 + 130;

	//Выделение старших 63 бит
    sir = [NBx2];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar2 = WB2x2;
    rep 2 wfifo = [ar2++], ftw, wtw; // Загрузка матрицы  весов

	gr3 = 1;
	gr3 and gr2;
	if =0 delayed goto after_correct;
	gr3 = gr2 >> 1;//В двойные слова
	nul;

	gr3 = gr3 + 1; //Если размер нечетный, увеличим на 1

after_correct:
	gr3 = gr3 - 1;
	vlen = gr3;

    //Вычисление приближенного значения X = ~sqrt(x)
	ar3 = BIAS;
	rep 32 ram = [ar3];
	ar3 = ar4; //Входной адрес
    rep 32 data = [ar3++] with data - ram; //Вычитаем BIAS

    rep 32 with vsum, shift afifo, 0; //Сдвигаем вправо на 1
    rep 32 with afifo + ram; //Прибавляем BIAS
    ar3 = SIGN_BIT;
    rep 32 data = [ar3] with afifo and data;//Приводим к положительному

    //Сохранение результата X = ~sqrt(x)
	ar3 = ar5;
    rep 32 [ar3++] = afifo;


    //Вычисление приближенного значения Y = 1/~sqrt(x)
    ar3 = ar5;
	rep 32 data = [ar3++] with not data;
    ar3 = DpCode_const;
    rep 32 data = [ar3] with afifo - data; // 1/x ~ допкоду экспоненты x
    //Сохранение результата Y = 1/~sqrt(x)
	ar3 = ar6;
	rep 32 [ar3++] = afifo;

	#########################################
	ar3 = ar4;
	fpu 0 rep vlen vreg0 = [ar3++];//A
	fpu 0 rep vlen vreg1 = [ar5++];//X0

	fpu 0 rep vlen vreg2 = [ar6++];//Y

	ar3 = _two_flt;
	fpu 0 rep vlen vreg6 = [ar3];//2


	ar3 = _half_flt;
	fpu 0 rep vlen vreg5 = [ar3];//0.5
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
	ar3 = _nan_flt;
    fpu 0 rep vlen vreg6 = [ar3];
    fpu 0 rep vlen vreg5 = [ar4++];//Входной вектор

    //проверка на nan & inf
    fpu 0 .float vreg5 - vreg5, set mask if <>0;
    fpu 0 .float vreg7 = mask ? /vreg5/ : vreg7;

	//проверка на 0
    fpu 0 .float vreg5 + vreg5, set mask if =0;
    fpu 0 .float vreg7 = mask ? vreg5 : vreg7;

	//проверка на отрицательные
    fpu 0 .float vreg5 + vreg5, set mask if <;
    sir = fp0_lmask;
    gr4 = sir;
    sir = fp0_hmask;
    gr3 = sir;
    fpu 0 .float vreg7 = mask ? vreg6 : vreg7;
    gr4 or gr3;
    if =0 goto save_result;
	gr7 = 3;
save_result:
	//fpu 0 rep vlen [ar2++] = vreg7;
	//Результат в vreg7
	
exit:
	ar7 = ar7 - 130;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    return; 
