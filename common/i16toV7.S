.global i16toV7

.text

mask_I16:
	.quad 0x0000FFFF0000FFFF

biggest_i16flt:
	.float 32767.0
	.float 32767.0
i65536:
	.float 65536.0
	.float 65536.0



/*
	ar0 = adr;
	gr0 = len;[1,64]
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


