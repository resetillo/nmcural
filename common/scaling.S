.global scale_f64


.global SIGN_BIT_dbl
.global _one_dbl

.text

max_int32_valueF:
	.double 2147483647
min_int32_valueF:
	.double -2147483648

/*
	ar0 - input adr (double);
	gr0 - scalefactor (signed int);
	ar1 - output adr (signed int);

*/
scale_f64:
	push ar4, gr4;
	push ar5, gr5;

	ar4 = ar7 + 2;
	ar7 = ar7 + 4;

    //Ограничение диапазона
	gr5 = 511;
	gr0 - gr5;
	if >= goto scaling;

	gr5 = -512;
	gr0 - gr5;
	if <= goto scaling;
	gr5 = gr0;
scaling:

		gr5 = gr5 << 20; //Размер сдвига, вычитаемый из экспоненты
		ar5 = _one_dbl;
		gr4 = [ar5 + 1]; // 1.0f
		gr4 = gr4 - gr5;
		ar5 = SIGN_BIT_dbl;
		gr5 = [ar5 + 1]; //Маска для обнуления знака
		gr4 = gr4 and gr5; //Весовой коэффициент
		[ar4 + 1] = gr4; // Сохраняем в старшую часть
		gr5 = false;
		[ar4] = gr5; // обнуляем младшую часть, она нулевая ибо за базу брали 1

		fpu 0 rep 1 vreg1 = [ar4]; //Весовой коэффициент
		fpu 0 rep 1 vreg0 = [ar0]; //Входные данные
		fpu 0 .double vreg0 = vreg0*vreg1;

		//Проверка на выход за диапазон
		ar5 = max_int32_valueF;
		fpu 0 rep 1 vreg1 = [ar5];
		fpu 0 .double vreg0 - vreg1, set mask if >;
		fpu 0 .double vreg0 = mask ? vreg1 : vreg0;

		ar5 = min_int32_valueF;
		fpu 0 rep 1 vreg1 = [ar5];
		fpu 0 .double vreg1 - vreg0, set mask if >;
		fpu 0 .double vreg0 = mask ? vreg1 : vreg0;

		//Приведение к целому
		sir = 0;
		fp_pack_exp = sir;
		fpu 0 .packer = vreg0 with .fixed_32 <= .double;
		fpu rep 1 [ar4] = .packer;
		gr5 = [ar4];
		[ar1] = gr5;

	ar7 = ar7 - 4;
	pop ar5, gr5;
	pop ar4, gr4;
	return;



