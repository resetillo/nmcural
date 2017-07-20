#include <nmpps_asm_defs.h>

.global _nmppsNorm_L1_16s32s_Sfs

.global norm_L1_16s32s_Sfs
.global norm_L1_16s32f


.global SIGN_BIT_flt

.text

scale_table_m16:
	//2^16
	.float 65536.0
	.float 65536.0
	//2^15
	.float 32768.0
	.float 32768.0
	//2^14
	.float 16384.0
	.float 16384.0
	//2^13
	.float 8192.0
	.float 8192.0
	//2^12
	.float 4096.0
	.float 4096.0
	//2^11
	.float 2048.0
	.float 2048.0
	//2^10
	.float 1024.0
	.float 1024.0
	//2^9
	.float 512.0
	.float 512.0
	//2^8
	.float 256.0
	.float 256.0
	//2^7
	.float 128.0
	.float 128.0
	//2^6
	.float 64.0
	.float 64.0
	//2^5
	.float 32.0
	.float 32.0
	//2^4
	.float 16.0
	.float 16.0
	//2^3
	.float 8.0
	.float 8.0
	//2^2
	.float 4.0
	.float 4.0
	//2^1
	.float 2.0
	.float 2.0
scale_table:
	//2^0
	.float 1.0
	.float 1.0
	//2^-1
	.float 0.5
	.float 0.5
	//2^-2
	.float 0.25
	.float 0.25
	//2^-3
	.float 0.125
	.float 0.125
	//2^-4
	.float 0.0625
	.float 0.0625
	//2^-5
	.float 0.03125
	.float 0.03125
	//2^-6
	.float 0.015625
	.float 0.015625
	//2^-7
	.float 0.0078125
	.float 0.0078125
	//2^-8
	.float 0.00390625
	.float 0.00390625
	//2^-9
	.float 0.001953125
	.float 0.001953125
	//2^-10
	.float 0.0009765625
	.float 0.0009765625
	//2^-11
	.float 0.00048828125
	.float 0.00048828125
	//2^-12
	.float 0.000244140625
	.float 0.000244140625
	//2^-13
	.float 0.0001220703125
	.float 0.0001220703125
	//2^-14
	.float 0.00006103515625
	.float 0.00006103515625
	//2^-15
	.float 0.000030517578125
	.float 0.000030517578125
	//2^-16
	.float 0.0000152587890625
	.float 0.0000152587890625

/*
	ar0 - input adr;
	gr0 - scalefactor;
	ar1 - output adr;

*/
scale_f32:
	push ar5, gr5;

    //Ограничение диапазона
	gr5 = 16;
	gr0 - gr5;
	if >= goto scaling;

	gr5 = -16;
	gr0 - gr5;
	if <= goto scaling;
	gr5 = gr0;
scaling:

		ar5 =  scale_table;
		gr5 = gr5 << 1; // *2
		fpu 0 rep 1 vreg1 = [ar5+gr5]; //Весовой коэффициент
		fpu 0 rep 1 vreg0 = [ar0]; //Входные данные формата float
		fpu 0 .float vreg0 = vreg0*vreg1;
		//Приведение к целому
		sir = 0;
		fp_pack_exp = sir;
		fpu 0 .packer = vreg0 with .fixed_32 <= .float;
		fpu rep 1 [ar1] = .packer;
		//fpu 0 rep 1 [ar1] = vreg0;

	pop ar5, gr5;
	return;



/*
	ar0 - input adr
	ar1 - output adr
	gr0 - len
	gr1 - scaleFactor
*/
norm_L1_16s32s_Sfs:
	push ar0, gr0;

	//Сложение
	call norm_L1_16s32f;

	//Растяжение результата
	ar0 = ar1;
	gr0 = gr1;
	call scale_f32;

	pop ar0, gr0;
	return;

/*
nmppsStatus nmppsNorm_Inf_16s32s_Sfs,  (const nmpps16s*  pSrc, int len, nmpps32s* pNorm, int scaleFactor)

*/
_nmppsNorm_L1_16s32s_Sfs:
	ar5 = ar7 - 2;

	push ar0, gr0;
	push ar1, gr1;

    ar0 = [--ar5];//pSrc
    gr0 = [--ar5];//len
    ar1 = [--ar5];//pDst
    gr1 = [--ar5];//scaleFactor

	call norm_L1_16s32s_Sfs;

	pop ar1, gr1;
	pop ar0, gr0;

	return;

