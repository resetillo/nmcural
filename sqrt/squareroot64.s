.global _nmppsSqrt_64f
.global _square_root64f
.global _half_dbl
.global _two_dbl
.global _nan_dbl


.global SB_default
.global NB_default
.global WB_default
.global DpCode_const_dbl
.global SIGN_BIT_dbl

.data

  .align 8
SB_default:
	  .quad 0x00000001 // 1 stroka
NB_default:
      .quad 0x8000000000000000 // 1 stolbets
WB_default:
      .quad 0x00000001
BIAS:
	  .quad 0x3ff0000000000000
SIGN_BIT_dbl:
      .quad 0x7fffffffffffffff
DpCode_const_dbl:
	  .quad 0x8020000000000000

.text
/**
@function nmppsSqrt_64f
*/
_nmppsSqrt_64f:
    ar5 = ar7 - 2;

    push ar0, gr0;
    push ar1, gr1;

    ar0 = [--ar5]; // Входящий вектор
    ar1 = [--ar5]; // Результирующий вектор
	gr0 = [--ar5]; // Размер

	call _square_root64f;

    pop ar1, gr1;
    pop ar0, gr0;
	return;


/*
    ar0  Входящий вектор
    ar1  Результирующий вектор
	gr0  Размер
*/
_square_root64f:
    
    // Сохранение в стеке регистров, чтобы исключить их повреждение

    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

				
	ar5 = ar7 + 2;
	ar6 = ar5 + 64;
	ar7 = ar7 + 130;

	gr7 = 0; //Значение по умолчанию
	gr0;
    if <= goto err_size;
    gr1 = ar1;
    gr1;
    if =0 goto err_ptr;
    gr1 = ar0;
    gr1;
    if =0 goto err_ptr;

	//Выделение старших 63 бит
    sir = [NB_default];
    nb1 = sir;	
    sir = [SB_default];
    sb = sir;	
	ar2 = WB_default;
    rep 1 wfifo = [ar2], ftw, wtw; // Загрузка матрицы  весов

main_loop:
	gr3 = gr0;
	gr2 = 32;
	gr3 - gr2;
    if <= goto after_correct;
    gr3 = 32;

after_correct:
	gr2 = true;
	gr3 = gr2 + gr3;
	vlen = gr3;

    //Вычисление приближенного значения X = ~sqrt(x)
	ar2 = BIAS;
	rep 32 ram = [ar2];
	ar2 = ar0;
    rep 32 data = [ar2++] with data - ram; //Вычитаем BIAS
    rep 32 with vsum, shift afifo, 0; //Сдвигаем вправо на 1
    rep 32 with afifo + ram; //Прибавляем BIAS
    ar2 = SIGN_BIT_dbl;
    rep 32 data = [ar2] with afifo and data;//Приводим к целому

    //Сохранение результата X = ~sqrt(x)
	ar2 = ar5;
    rep 32 [ar2++] = afifo;


    //Вычисление приближенного значения Y = 1/~sqrt(x)
    ar2 = ar5;
	rep 32 data = [ar2++] with not data;
    ar2 = DpCode_const_dbl;
    rep 32 data = [ar2] with afifo - data; // 1/x ~ допкоду экспоненты x
    //Сохранение результата Y = 1/~sqrt(x)
	ar2 = ar6;
	rep 32 [ar2++] = afifo;
/*    goto continue;

    nul;
    nul;
    nul;
    nul;
    nul;
    nul;

continue:*/
	#########################################
	ar2 = ar0;
	fpu 0 rep vlen vreg0 = [ar2++];//A
	fpu 0 rep vlen vreg1 = [ar5++];//X0
	fpu 0 rep vlen vreg2 = [ar6++];//Y

	ar2 = _two_dbl;
	fpu 0 rep vlen vreg6 = [ar2];//2


	ar2 = _half_dbl;
	fpu 0 rep vlen vreg5 = [ar2];//0.5
	//Уточним значение
	//Y0 = (2.0 - X0*Y)*Y
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;
	
	//Первая итерация
	//X1 = 0.5*(X0 + A*Y0)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;
	//Уточним значение Y1 = 1/X1
	//Y1_ = (2.0 - X1*Y0)*Y0
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;
	//Y1 = (2.0 - X1*Y1_)*Y1_
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;


	//Вторая итерация
	//X2 = 0.5*(X1 + A*Y1)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;
	//Уточним значение Y2 = 1/X2
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	//3я итерация
	//X3 = 0.5*(X2 + A*Y2)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;
	//Уточним значение Y3 = 1/X3
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	//4я итерация
	//RESULT = 0.5*(X3 + A*Y3)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;

	//Анализ входного вектора
	ar2 = _nan_dbl;
    fpu 0 rep vlen vreg6 = [ar2];
	//ar2 = ar0;
    fpu 0 rep vlen vreg5 = [ar0++];//Входной вектор

    //проверка на nan & inf
    fpu 0 .double vreg5 - vreg5, set mask if <>0;
    fpu 0 .double vreg1 = mask ? /vreg5/ : vreg1;

	//проверка на 0
    fpu 0 .double vreg5 + vreg5, set mask if =0;
    fpu 0 .double vreg1 = mask ? vreg5 : vreg1;

	//проверка на отрицательные
    fpu 0 .double vreg5 + vreg5, set mask if <;
    sir = fp0_dmask;
    fpu 0 .double vreg1 = mask ? vreg6 : vreg1;
    gr1 = sir;
    gr1;
    if =0 goto save_result;
	gr7 = 3;
save_result:
	fpu 0 rep vlen [ar1++] = vreg1;

    gr2 = 32;
	gr0 = gr0 - gr2;
    if > goto main_loop;


    //nb1 = [NB];	
    //sb = [SB];	
	//ar5 = WB; 
	goto exit;
err_size:
    gr7 = -6;
    goto exit;
err_ptr:
    gr7 = -8;
    goto exit;
	
exit:
	ar7 = ar7 - 130;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    return; 
