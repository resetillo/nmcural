#include <nmpps_asm_defs.h>


.global _bessel_I0_32f
.global bessel_I0_32f

.text


.align 8

A7dot75:
	.float 7.75
	.float 7.75

/*
	nmppsStatus bessel_I0_32f(const nmpps32f* pSrc, nmpps32f* pDst, int len)

	Алгоритм заимствован из библиотеки Boost(http://www.boost.org/doc/libs/1_65_0/libs/math/doc/html/math_toolkit/bessel/mbessel.html),
    первоисточник:
    https://www.advanpix.com/2015/11/11/rational-approximations-for-the-modified-bessel-function-of-the-first-kind-i0-computations-double-precision/

 		  |  ([x/2]^2)*P1([x/2]^2) + 1, при x<7.75
 	I0 =  |
 		  |  (exp(x)/sqrt(x))*P2(1/x), при x>=7.75

*/
_bessel_I0_32f:
    ar5 = ar7 - 2;

    push ar0, gr0;
    push ar1, gr1;
    push ar4, gr4;
    push ar5, gr5;

    ar0 = [--ar5];//pSrc
    ar1 = [--ar5];//pDst
    gr1 = [--ar5];//len

    ar4 = ar7 + 2;
    ar7 = ar7 +66;

    //Контроль параметров
    gr1;
    if <= delayed goto exit;
    gr7 = nmppsStsSizeErr;

    gr5 = ar0;
    gr5;
    if =0 delayed goto exit;
    gr7 = nmppsStsNullPtrErr;

    gr5 = ar1;
    gr5;
    if =0 goto exit;



	gr4 = 64;
main_loop:
    gr4 - gr1;

    if <= goto after_correct;
    gr4 = gr1;
after_correct:

	gr0 = gr4;
    call bessel_I0_32f;

    //save data
    gr5 = 1;
    gr5 and gr4;
    if =0 goto simple_save;
    	//Размер нечетный, копирование через буфер
    	ar5 = ar4;
    	fpu 0 rep vlen [ar5++] = vreg7;

		gr4 - gr5;
		if =0 goto last_word;
			gr5 = gr4 >> 1; // div 2
			gr5--;
			vlen = gr5;
    		fpu 0 rep vlen vreg7 = [ar4++];
    		fpu 0 rep vlen [ar1++] = vreg7;
    	last_word:
			gr5 = [ar4];
			[ar1] = gr5;
			goto pre_exit;
simple_save:
    fpu 0 rep vlen [ar1++] = vreg7;
    //correct input adress
	gr5 = ar0;
	gr5 = gr5 + gr4;
	ar0 = gr5 with \
	gr1 = gr1 - gr4;
    if > goto main_loop;

pre_exit:
    gr7 = nmppsStsNoErr;
exit:
    ar7 = ar7 - 66;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar1, gr1;
    pop ar0, gr0;
return;


/*
	ar0 - input
	vr7 - output
	gr0 - len [1-64]

	use vr0, vr1, vr2
*/
bessel_I0_32f:
	push ar1, gr1;
	push ar5, gr5;
	push ar6, gr6;

	gr1 = gr0 >> 1; // div 2
	gr5 = 1;
	gr0 and gr5;
	if > goto after_correct_size;
	gr1--;
after_correct_size:
	vlen = gr1;
	ar5 = ar0;
	fpu 0 rep vlen vreg0 = [ar5++]; //X
	ar5 = A7dot75;
	fpu 0 rep vlen vreg6 = [ar5]; //7.75


	//Обнуление маски
	gr5 = 0;
	sir = gr5;
	fp0_lmask = sir;
	fp0_hmask = sir;

	fpu 0 .float vreg0 - vreg6, set mask if <;
	sir = fp0_lmask;
	gr6 = sir;
	sir = fp0_hmask;
	gr7 = sir;

	gr6 or gr7;
	if =0 goto calc_part2;//Все члены вектора - больше 7.75

	ar5 = _one_flt;
	fpu 0 rep vlen vreg4 = [ar5]; //1.0
	fpu 0 .float  vreg3 = vreg4;  //1.0
	ar5 = _half_flt;
	fpu 0 rep vlen vreg5 = [ar5]; //0.5

	fpu 0 .float  vreg1 = vreg0*vreg5;  // x div 2
	fpu 0 .float  vreg1 = vreg1*vreg1;  // [x div 2]^2

	ar5 = _zero_flt;
	fpu 0 rep vlen vreg7 = [ar5]; //Обнуление результата

	gr5 = 9;
	ar5 = _BESSEL_I0_P1;
loop_part1:
	fpu 0 rep vlen vreg5 = [ar5]; //P1[k]
	fpu 0 .float  vreg2 = vreg3*vreg5;  // P1[k]*([x div 2]^2)^k
	fpu 0 .float  vreg7 = vreg7 + vreg2;
	fpu 0 .float  vreg3 = vreg3*vreg1;  // ([x div 2]^2)^(k+1) для след. итерации
	ar5 = ar5 + 2;
	gr5--;
	if > goto loop_part1;

	fpu 0 .float  vreg7 = vreg7 * vreg1; //([x div 2]^2) * P1[([x div 2]^2)
	fpu 0 .float  vreg7 = vreg7 + vreg4; // + 1.0

calc_part2:
	//Проверка, нужно ли считать по второму способу
	fpu 0 .float vreg0 - vreg6, set mask if >=;
	sir = fp0_lmask;
	gr6 = sir;
	sir = fp0_hmask;
	gr7 = sir;
	gr6 or gr7;
	if =0 goto exit_macro;//Все члены вектора - меньше 7.75, т.е. уже подсчитаны

	push gr6;
	push gr7;

	ar2 = ar7 + 2;
	ar3 = ar7 + 66;
	ar7 = ar7 + 130;

	fpu 1 vreg0 = fpu 0 vreg7; //Сохраняем результат предыдущей части

	/*
	    ar0 Divisor vector
	    gr0 Divided value
	    ar1 Output vector
		gr1 Lenght
	*/
	push ar0, gr0;
	push ar1, gr1;
	gr1 = gr0;
	ar1 = ar2;
	ar5 = _one_flt;
	gr0 = [ar5];
	call DivCRev_32f;
	pop ar1, gr1;
	pop ar0, gr0;

	vlen = gr1;
	ar5 = ar2;
	fpu 0 rep vlen vreg1 = [ar5++]; // 1/x

	//k = 0
	ar5 = _BESSEL_I0_P2;
	fpu 0 rep vlen vreg4 = [ar5]; // P2[0]
	fpu 0 .float vreg6 = vreg4; // SUM = P2[0]*(1/x)^0
	//k = 1
	ar5 = ar5 + 2;
	fpu 0 rep vlen vreg4 = [ar5]; // P2[1]
	fpu 0 .float vreg5 = vreg1*vreg4; // P2[1]/x
	fpu 0 .float vreg6 = vreg5 + vreg6; // SUM += P2[1]/x
	//k = 2
	ar5 = ar5 + 2;
	fpu 0 rep vlen vreg4 = [ar5]; // P2[2]
	fpu 0 .float vreg2 = vreg1*vreg1;//  1/(x^2)
	fpu 0 .float vreg5 = vreg2*vreg4; // P2[2]/(x^2)
	fpu 0 .float vreg6 = vreg5 + vreg6; // SUM += P2[2]/(x^2)
	//k = 3
	ar5 = ar5 + 2;
	fpu 0 rep vlen vreg4 = [ar5]; // P2[3]
	fpu 0 .float vreg2 = vreg2*vreg1;//  1/(x^3)
	fpu 0 .float vreg5 = vreg2*vreg4; // P2[3]/(x^3)
	fpu 0 .float vreg6 = vreg5 + vreg6; // SUM += P2[3]/(x^3)
	//k = 4
	ar5 = ar5 + 2;
	fpu 0 rep vlen vreg4 = [ar5]; // P2[4]
	fpu 0 .float vreg2 = vreg2*vreg1;//  1/(x^4)
	fpu 0 .float vreg5 = vreg2*vreg4; // P2[4]/(x^4)
	fpu 0 .float vreg6 = vreg5 + vreg6; // SUM += P2[4]/(x^4)

	fpu 1 vreg1 = fpu 0 vreg6; //Сохраняем полином

	/*
		ar0 input adr
		ar1 output adr
		gr0 lenght
	*/

	push ar0, gr0;
	push ar1, gr1;
	ar1 = ar2;
	call _square_root32f;
	pop ar1, gr1;
	pop ar0, gr0;

	/*
	    ar0 Divisor vector
	    gr0 Divided value
	    ar1 Output vector
		gr1 Lenght
	*/
	push ar0, gr0;
	push ar1, gr1;
	ar0 = ar2; //sqrt(X)
	gr1 = gr0;
	ar1 = ar2;
	ar5 = _one_flt;
	gr0 = [ar5];
	call DivCRev_32f;
	pop ar1, gr1;
	pop ar0, gr0;

	/*
		ar0 - input
		gr0 - len [1-64]
		vreg7 - output

		use vr0, vr1, vr2, vr3

		exp(x) = SUM[k=0..inf](x^k / k!)
	*/
	//vr7 = exp(X)
	push ar0, gr0;
	call exp_32f;
	pop ar0, gr0;

	vlen = gr1;
	fpu 0 rep vlen vreg6 = [ar2++];// 1/sqrt(X)
	fpu 0 .float vreg7 = vreg6*vreg7;// exp(x)/sqrt(x)
	fpu 0 vreg6 = fpu 1 vreg1; //полином
	fpu 0 .float vreg7 = vreg6*vreg7;// P2(1/x)*exp(x)/sqrt(x)
	fpu 0 vreg6 = fpu 1 vreg0; //результат первой части



	ar7 = ar7 - 130;
	pop gr7;
	pop gr6;

	sir = gr6;
	fp0_lmask = sir;
	sir = gr7;
	fp0_hmask = sir;
	fpu 0 .float vreg7 = not mask ? vreg6 : vreg7;

exit_macro:
	pop ar6, gr6;
	pop ar5, gr5;
	pop ar1, gr1;
return;






















