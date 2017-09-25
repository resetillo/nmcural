#include <nmpps_asm_defs.h>

.global _exp_32f
.global exp_32f



.text

/*
	nmppsStatus exp_32f(const nmpps32f* pSrc, nmpps32f* pDst, int len)

*/
_exp_32f:
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

    gr7 = nmppsStsNoErr;


	gr4 = 64;
main_loop:
    gr4 - gr1;

    if <= goto after_correct;
    gr4 = gr1;
after_correct:

	gr0 = gr4;
    call exp_32f;

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
			goto exit;
simple_save:
    fpu 0 rep vlen [ar1++] = vreg7;

    gr1 = gr1 - gr4;
    if > goto main_loop;


exit:
    ar7 = ar7 - 66;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar1, gr1;
    pop ar0, gr0;
return;


return;


/*
	ar0 - input
	gr0 - len [1-64]
	vreg7 - output

	use vr0, vr1, vr2, vr3

	exp(x) = SUM[k=0..inf](x^k / k!)
*/
exp_32f:
	push ar5, gr5;
	push ar6, gr6;

	ar6 = ar7 + 2;
	ar7 = ar7 + 66;

	ar5 = _inf_flt;
	rep 32 ram = [ar5];
	ar5 = ar0;
	rep 32 data = [ar5++] with data and not ram; //обнуление экспоненты
	ar5 = _one_flt;
	rep 32 data = [ar5] with data or afifo;
	ar5 = ar6;
	rep 32 [ar5++] = afifo; // [ar6] = x[1..2]

	gr5 = gr0 >> 1;//div 2
	gr6 = 1;
	gr0 and gr6;
	if > goto after_correct_size;
	gr5--;
after_correct_size:
	vlen = gr5;
	ar5 = _one_flt;


	fpu 0 rep vlen vreg0 = [ar0++]; // X

	fpu 0 .float vreg4 = /vreg0/; // abs(X);
	fpu 0 rep vlen vreg5 = [ar5]; // 1;

	fpu 0 rep vlen vreg6 = [ar6++]; // x[1..2];
    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x| > 1
    fpu 0  .float vreg0 = mask ? vreg6 : vreg0;         //  x= ? x[1..2] : x

	//k = 0
	fpu 0 .float vreg7 = vreg5; // RES = 1;

	//k = 1
	fpu 0 .float vreg7 = vreg7 + vreg0; // RES = 1 + X

	//k = 2
	fpu 0 .float vreg1 = vreg0 * vreg0; // X^k
	ar5 = _divx_koeff32;
	ar5 = ar5 + 2;
	fpu 0 rep vlen vreg2 = [ar5]; // 1/k
	ar5 = ar5 + 2;//k++
	fpu 0 .float vreg3 = vreg1 * vreg2; // X^k / k
	fpu 0 .float vreg7 = vreg7 + vreg3; // RES = RES + X^k / k



	//k = 3..20
	gr5 = 19;
loop:
	fpu 0 rep vlen vreg2 = [ar5]; // 1/k
	fpu 0 .float vreg1 = vreg0 * vreg2;// X/k
	fpu 0 .float vreg3 = vreg1 * vreg3; // X^k / k
	fpu 0 .float vreg7 = vreg7 + vreg3; // RES = RES + X^k / k

	gr5--;
	if > delayed goto loop;
	ar5 = ar5 + 2;//k++
	nul;

	//RES = (e^mantis)^(2^exp)
	ar5 = _half_flt;
	fpu 0 rep vlen vreg1 = [ar5]; // 0.5;
    fpu 0  .float vreg4= vreg4 *  vreg1;                   //  |x| /2

    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 2 > 1
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    fpu 0  .float vreg4= vreg4 *  vreg1;


    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 4 > 1
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    fpu 0  .float vreg4= vreg4 *  vreg1;

    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 8 > 1
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    fpu 0  .float vreg4= vreg4 *  vreg1;

    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 16 > 1
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    fpu 0  .float vreg4= vreg4 *  vreg1;

    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 32 > 1
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    fpu 0  .float vreg4= vreg4 *  vreg1;

    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 64 > 1
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    fpu 0  .float vreg4= vreg4 *  vreg1;

    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 128 > 1
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    fpu 0  .float vreg4= vreg4 *  vreg1;

    fpu 0  .float vreg4 -vreg5, set mask if >=;            //  |x|/ 256 > 1, e^(2^256) = inf, last iteration
    fpu 0  .float vreg7= mask ? vreg7 * vreg7 : vreg7;
    //fpu 0  .float vreg4= vreg4 *  vreg1;

	ar7 = ar7 - 66;
	pop ar6, gr6;
	pop ar5, gr5;
return;

