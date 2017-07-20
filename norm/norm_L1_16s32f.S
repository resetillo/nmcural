#include <nmpps_asm_defs.h>

.global _nmppsNorm_L1_16s32f
.global _zero_flt

.global norm_L1_16s32f


mask_I16:
	.quad 0x0000FFFF0000FFFF

biggest_i16flt:
	.float 32767.0
	.float 32767.0
i65536:
	.float 65536.0
	.float 65536.0

.text


/*
	ar0 = adr;
	gr0 = len;[1,32]
	fpu 0 vreg7 = out;
*/
i16toV7:
	//int16 использует младшие 16 разрядов в слове,
	//старшие могут быть любые, данная процедура
	//обрезает старшие 16 разрядов, загружает в vreg7
	//и переводит числа из допкода
	push ar5, gr5;
	push ar6, gr6;

	ar6 = ar7 + 2;
	ar7 = ar7 + 66;
	ar5 = ar0;
	rep 32 ram = [ar5++];
	ar5 = mask_I16;
	rep 32 data = [ar5] with data and ram;
	ar5 = ar6;
	rep 32 [ar5++] = afifo;

	gr5 = gr0 >> 1;
	gr6 = 1;
	gr0 and gr6;
	if <>0 goto M1;
	gr5 = gr5 - 1;
M1:
	sir = 0;
	fp_pack_exp = sir;
	vlen = gr5;
	fpu rep vlen .packer= [ar6++] with .float <= .fixed_32;
	fpu 0 rep vlen vreg7 = .packer;

	ar5 = biggest_i16flt;
	fpu 0 rep vlen vreg0 = [ar5];//32767
	ar5 = i65536;
	fpu 0 rep vlen vreg1 = [ar5];//65536

	fpu 0 .float vreg7 - vreg0, set mask if >;
	fpu 0 .float vreg7 = mask ? vreg7 - vreg1 : vreg7;

	ar7 = ar7 - 66;
	pop ar6, gr6;
	pop ar5, gr5;

return;

/*
	ar0 - input adr
	ar1 - output adr
	gr0 - len
*/
norm_L1_16s32f:
summator_abs16s32f:
	push ar4, gr4;
	push ar5, gr5;

	ar4 = ar7 + 2;
	ar7 = ar7 + 4;

	gr0;
    if <= delayed goto exit;
    gr7 = nmppsStsSizeErr;

    gr5 = ar0;
    gr5;
    if =0 delayed goto exit;
    gr7 = nmppsStsNullPtrErr;

    gr5 = ar1;
    gr5;
    if =0 goto exit;

    gr7 = nmppsStsNoErr;//По умолчанию возвращаем 0

	ar5 = _zero_flt;
	fpu 0 rep 1 vreg6 = [ar5]; //Обнуляем результат
	gr4 = 32;


main_loop:
	gr0 -gr4;
	if >= goto M2;
	gr4 = gr0;
M2:

	push ar0, gr0;
	gr0 = gr4;
	call i16toV7;
	pop ar0, gr0;

	fpu 0 .float vreg0 = /vreg7/;
	fpu 0 .packer= vreg0 with .float .in_low <= .float;
	gr5 = VL;
	gr5 = gr5 + 1;
	gr5 = gr5 << 1;
	gr5 = gr5 - 1;
	vlen = gr5;
	fpu 0 rep vlen vreg0 = .packer;

	gr5 = gr4;
	sub_loop:
		fpu 0 .float vreg6 = vreg6 + .retrive(vreg0);
	gr5 = gr5 - 1;
	if > goto sub_loop;

	gr5 = ar0;
	gr0 = gr0 - gr4;
	if > delayed goto main_loop;
	gr5 = gr5 + gr4;
	ar0 = gr5;

save:
	fpu 0 rep 1  [ar4] = vreg6;
	gr5 = [ar4];
	[ar1] = gr5;
exit:
	ar7 = ar7 - 4;
	pop ar5, gr5;
	pop ar4, gr4;
	return;

/*
nmppsStatus nmppsNorm_L1_16s32f(const nmpps16s*  pSrc, int len, nmpps32f* pNorm)

*/
_nmppsNorm_L1_16s32f:
	ar5 = ar7 - 2;

	push ar0, gr0;
	push ar1, gr1;

    ar0 = [--ar5];//pSrc
    gr0 = [--ar5];//len
    ar1 = [--ar5];//pDst

	call summator_abs16s32f;

	pop ar1, gr1;
	pop ar0, gr0;

	return;

