#include <nmpps_asm_defs.h>

.global mulV32_r_fc



.text

/*
multiply vector with real values and vector with complex values

ar0 - vector with real values
ar1 - vector with complex values
ar2 - output vector
gr0 - len
*/

mulV32_r_fc:
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	ar3 = ar7 + 2;
	ar7 = ar7 + 66;

	gr4 = 32;
	gr3 = 31;
	gr2 = 15;

	gr5 = 0xFFFF;
	sir = gr5;
	fp0_lmask = sir;
	gr5 = 0;
	sir = gr5;
	fp0_hmask = sir;
multiply_loop:
		gr0 - gr4;
		if >= goto M1;
			//correct size
			gr2 = gr0 >> 1;//div2
			gr3 = 1;
			gr3 and gr0;
			if > goto M0;
			gr2--;
			M0:
			gr3 = gr0 - 1;
		M1:
		//duplicate real values
		vlen = gr2;
		fpu 0 rep vlen vreg1 = [ar0++];//input real data

		//duplicate low part
		fpu 0 .packer= vreg1 with .float .in_high <= .float .in_low;
		fpu 0 rep vlen vreg2 = .packer;

		fpu 0 .float vreg2 = mask ? vreg1 : vreg2;
		ar5 = ar3;
		gr5 = 4;
		fpu 0 rep vlen  [ar5++gr5] = vreg2;//with postincremen

		//duplicate high part
		fpu 0 .packer= vreg1 with .float .in_low <= .float .in_high;
		fpu 0 rep vlen vreg2 = .packer;
		fpu 0 .float vreg2 = not mask ? vreg1 : vreg2;
		ar5 = ar3+2;
		//gr5 = 2;
		fpu 0 rep vlen [ar5++gr5] = vreg2;//with preincremen

		//load duplicate values
		vlen = gr3;
		ar5 = ar3;
		fpu 0 rep vlen vreg0 = [ar5++];

		fpu 0 rep vlen vreg1 = [ar1++];//complex data
		fpu 0 .float vreg0 = vreg0*vreg1;

		fpu 0 rep vlen [ar2++] = vreg0;//save data

		gr0 = gr0 - gr4;
	if > goto multiply_loop;



	ar7 = ar7 - 66;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
return;


















