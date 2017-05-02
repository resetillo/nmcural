

.global _change_infinity
.global _change_nan
.global __macro_change_infinity
.global __macro_change_nan


.global _zero_dbl

.data

mantis_dbl: .quad 0x000FFFFFFFFFFFFF
exp_dbl:    .quad 0x7ff0000000000000

.text


__macro_change_infinity:
	/*
		ar0 - input vector
		ar1 - changing value
		gr0 - length of vector
		vreg7 - out vector
		@note: change also vreg5

		gr1 = mask1
		gr2 = mask2
		gr3 = mask3
		ar2 = mass[64]
	*/
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	ar2 = ar7 + 2;
	ar7 = ar7 + 66;


	gr1 = gr0 - 1;
	vlen = gr1;

	//Выделим мантиссу
	ar3 = mantis_dbl;
	##FIX_ME
	rep 32 ram = [ar3];
	ar3 = ar0;
	rep 32 data = [ar3++] with data and ram;
	ar3 = ar2;
	rep 32 [ar3++] = afifo;

	ar3 = ar2;
	fpu 0 rep vlen vreg7 = [ar3++];
	fpu 0 .double vreg7 + vreg7, set mask if =0;
	sir = fp0_dmask;
	gr1 = sir;

	//Выделим экспоненту
	ar3 = exp_dbl;
	rep 32 ram = [ar3];
	ar3 = ar0;
	rep 32 data = [ar3++] with data and ram;
	//ar3 = mantis_dbl;
	//rep 32 data = [ar3] with data or afifo;
	ar3 = ar2;
	rep 32 [ar3++] = afifo;

	ar3 = ar2;
	fpu 0 rep vlen vreg7 = [ar3++];
	/*########################
	goto exit_macro;
	#########################*/
	fpu 0 .double vreg7 - vreg7, set mask if <>0;
	sir = fp0_dmask;
	gr2 = sir;

	gr3 = gr1 and gr2;


	ar3 = ar0;
	fpu 0 rep vlen vreg7 = [ar3++];//input value
	fpu 0 rep vlen vreg5 = [ar1];//changing value



	sir = gr3;
	fp0_dmask = sir;

	fpu 0 .double vreg7 = mask ? vreg5 : vreg7;
exit_macro:
	ar7 = ar7 - 66;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
return;



//void change_infinity(double *pSrc, double *pDst, double INFchange,  int len)
_change_infinity:

	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	ar1 = ar7 + 2;//INFchange
	ar7 = ar7 + 4;

	//Load params
	ar0 = [--ar5];//pSrc
	ar2 = [--ar5];//pDst

	gr0 = [--ar5];//double INFchange
	ar3 = ar1+2;
	[--ar3] = gr0;
	gr0 = [--ar5];
	[--ar3] = gr0;

	gr0 = [--ar5];// int len

		/*
		ar0 - input vector
		ar1 - changing value
		gr0 - length of vector
		vreg7 - out vector
		*/
	call __macro_change_infinity;

	fpu 0 rep vlen [ar2++] = vreg7;//DST

	ar7 = ar7 - 4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
return;


__macro_change_nan:
	/*
		ar0 - input vector
		ar1 - changing value
		gr0 - length of vector
		vreg7 - out vector
		@note: change also vreg5

		gr1 = mask1
		gr2 = mask2
		gr3 = mask3
		ar2 = mass[64]
	*/
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	ar2 = ar7 + 2;
	ar7 = ar7 + 66;


	gr1 = gr0 - 1;
	vlen = gr1;

	//Выделим мантиссу
	ar3 = mantis_dbl;
	##FIX_ME
	rep 32 ram = [ar3];
	ar3 = ar0;
	rep 32 data = [ar3++] with data and ram;
	ar3 = ar2;
	rep 32 [ar3++] = afifo;

	ar3 = ar2;
	fpu 0 rep vlen vreg7 = [ar3++];
	fpu 0 .double vreg7 + vreg7, set mask if <>0;
	sir = fp0_dmask;
	gr1 = sir;

	//Выделим экспоненту
	ar3 = exp_dbl;
	rep 32 ram = [ar3];
	ar3 = ar0;
	rep 32 data = [ar3++] with data and ram;
	//ar3 = mantis_dbl;
	//rep 32 data = [ar3] with data or afifo;
	ar3 = ar2;
	rep 32 [ar3++] = afifo;

	ar3 = ar2;
	fpu 0 rep vlen vreg7 = [ar3++];
	/*########################
	goto exit_macro;
	#########################*/
	fpu 0 .double vreg7 - vreg7, set mask if <>0;
	sir = fp0_dmask;
	gr2 = sir;

	gr3 = gr1 and gr2;


	ar3 = ar0;
	fpu 0 rep vlen vreg7 = [ar3++];//input value
	fpu 0 rep vlen vreg5 = [ar1];//changing value



	sir = gr3;
	fp0_dmask = sir;

	fpu 0 .double vreg7 = mask ? vreg5 : vreg7;

	ar7 = ar7 - 66;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
return;



//void change_nan(double *pSrc, double *pDst, double NANchange,  int len)
_change_nan:

	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	ar1 = ar7 + 2;//NANchange
	ar7 = ar7 + 4;

	//Load params
	ar0 = [--ar5];//pSrc
	ar2 = [--ar5];//pDst

	gr0 = [--ar5];//double NANchange
	ar3 = ar1+2;
	[--ar3] = gr0;
	gr0 = [--ar5];
	[--ar3] = gr0;

	gr0 = [--ar5];// int len

		/*
		ar0 - input vector
		ar1 - changing value
		gr0 - length of vector
		vreg7 - out vector
		*/
	call __macro_change_nan;

	fpu 0 rep vlen [ar2++] = vreg7;//DST

	ar7 = ar7 - 4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
return;



