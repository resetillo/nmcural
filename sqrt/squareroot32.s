.global _nmppsSqrt_32f
.global _square_root32f


.global _half_flt
.global _two_flt
.global _nan_flt

.global SBx2
.global NBx2
.global WB2x2
.global SIGN_BIT_flt
.global DpCode_const_flt

.data

  .align 8

SBx2:
	  .quad 0x200000002 // 2 ������
NBx2:
      .quad 0x80000000 // 2 �������
WB2x2:
      .quad 0x0000000000000001
      .quad 0x0000000100000000
BIAS:
	  .quad 0x3f8000003f800000
SIGN_BIT_flt:
      .quad 0x7fffffff7fffffff
DpCode_const_flt:
	  .quad 0x8100000081000000

.text


#include <nmpps_asm_defs.h>

_nmppsSqrt_32f:

    ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;

    ar0 = [--ar5]; // �������� ������
    ar1 = [--ar5]; // �������������� ������
	gr0 = [--ar5]; // ������

	call _square_root32f;

	pop ar1, gr1;
	pop ar0, gr0;

	return;


/*
	ar0 input adr
	ar1 output adr
	gr0 lenght
*/

_square_root32f:
    // ���������� � ����� ���������, ����� ��������� �� �����������
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;


	ar6 = ar7 + 2;
	#define mass1  ar6
	#define mass2  ar6 + 64
	ar7 = ar7 + 130;

	gr5 = ar0;
	gr5;
	if =0 delayed goto exit;
	gr7 = nmppsStsNullPtrErr;
	gr5 = ar1;

	gr5;
	if =0 delayed goto exit;
	gr0;
	nul;

	if <= delayed goto exit;
	gr7 = nmppsStsSizeErr;
	nul;

	gr7 = nmppsStsNoErr; //0 �� ���������


	//��������� ������� 63 ���
    sir = [NBx2];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar5 = WB2x2;
    rep 2 wfifo = [ar5++], ftw, wtw; // �������� �������  �����

	//������� ��������
	gr4 = 64;
	gr4 - gr0;
	if > goto main_loop;
		gr5 = 31;
		vlen = gr5;
		ar5 = _two_flt;
		fpu 0 rep vlen vreg6 = [ar5];//2
		ar5 = _half_flt;
		fpu 0 rep vlen vreg5 = [ar5];//0.5
		ar5 = _nan_flt;
	    fpu 0 rep vlen vreg4 = [ar5];

main_loop:
	gr4 - gr0;
	if < goto after_correct;
		//������ ������ 64
		gr6 = gr0 >> 1;
		gr5 = 1;
		gr0 and gr5;
		if =0 delayed goto M1;
		gr6 = gr6 - 1;
		vlen = gr6;
			//������ ��������, ���� ���������, ��� � ������ ����������� ����� �� ���� ������
			//��� ����� �������� ����� �����
			gr0 - gr5; //len ? 1
			if =0 delayed goto L1_last_word;
			ar5 = mass2;
			nul;
				rep vlen vreg0 = [ar0++];
				rep vlen [ar5++] = vreg0;
			L1_last_word:
				gr5 = [ar0];
				[ar5++] = gr5;
				gr5 = false;
				[ar5] = gr5; //�������� ������ �����
				ar0 = mass2; //������� ������
				//��������� ������
				gr6 = gr0 >> 1;
				vlen = gr6;
		M1:
		ar5 = _two_flt;
		fpu 0 rep vlen vreg6 = [ar5];//2
		ar5 = _half_flt;
		fpu 0 rep vlen vreg5 = [ar5];//0.5
		ar5 = _nan_flt;
	    fpu 0 rep vlen vreg4 = [ar5];//nan

	    gr5 = 0;
	    sir = gr5;
	    fp0_lmask = sir;
	    fp0_hmask = sir;


after_correct:

    //���������� ������������� �������� X = ~sqrt(x)
	ar5 = BIAS;
	rep 32 ram = [ar5];
	ar5 = ar0; //������� �����
    rep 32 data = [ar5++] with data - ram; //�������� BIAS

    rep 32 with vsum, shift afifo, 0; //�������� ������ �� 1
    rep 32 with afifo + ram; //���������� BIAS
    ar5 = SIGN_BIT_flt;
    rep 32 data = [ar5] with afifo and data;//�������� � ��������������

    //���������� ���������� X = ~sqrt(x), �� ��� ����������� ������
	ar5 = mass1;
    rep 32 [ar5++] = afifo;
	ar5 = mass1;
	########################################
	fpu 0 rep vlen vreg1 = [ar5++];//X0
	########################################


    //���������� ������������� �������� Y = 1/~sqrt(x)
	ar5 = mass1;
	rep 32 data = [ar5++] with not data;
    ar5 = DpCode_const_flt;
    rep 32 data = [ar5] with afifo - data; // 1/x ~ ������� ���������� x
    //���������� ���������� Y = 1/~sqrt(x)
	ar5 = mass1;
	rep 32 [ar5++] = afifo;

	########################################
	ar5 = mass1;
	fpu 0 rep vlen vreg2 = [ar5++];//Y

	fpu 0 rep vlen vreg0 = [ar0++];//A


	//������� ��������
	//Y0 = (2.0 - X0*Y)*Y
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;
	
	//������ ��������
	//X1 = 0.5*(X0 + A*Y0)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg1 = vreg5*vreg3;
	//������� �������� Y1 = 1/X1
	//Y1_ = (2.0 - X1*Y0)*Y0
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;
	//Y1 = (2.0 - X1*Y1_)*Y1_
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;


	//������ ��������
	//X2 = 0.5*(X1 + A*Y1)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg1 = vreg5*vreg3;
	//������� �������� Y2 = 1/X2
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	//3� ��������
	//X3 = 0.5*(X2 + A*Y2)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg1 = vreg5*vreg3;
	//������� �������� Y3 = 1/X3
	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	fpu 0 .float vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .float vreg2 = vreg3*vreg2;

	//4� ��������
	//RESULT = 0.5*(X3 + A*Y3)
	fpu 0 .float vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .float vreg7 = vreg5*vreg3;

	//������ �������� �������

    //�������� �� nan & inf
    fpu 0 .float vreg0 - vreg0, set mask if <>0;
    fpu 0 .float vreg7 = mask ? /vreg0/ : vreg7;

	//�������� �� 0
    fpu 0 .float vreg0 + vreg0, set mask if =0;
    fpu 0 .float vreg7 = mask ? vreg0 : vreg7;

	//�������� �� �������������
    fpu 0 .float vreg0 + vreg0, set mask if <;
    sir = fp0_lmask;
    gr5 = sir;
    sir = fp0_hmask;
    gr6 = sir;
    fpu 0 .float vreg7 = mask ? vreg4 : vreg7;
    gr5 or gr6;
    if =0 goto save_result;
	gr7 = nmppsStsSqrtNegArg; //������������� �����
save_result:
	//��������� � vreg7
	gr0 - gr4;
	if > delayed goto save_result_normal;
		ar5 = mass1;
		fpu 0 rep vlen [ar5++] = vreg7;

		gr5 = 1;
		gr0 and gr5;
		if =0 goto save_result_normal;
		//������ ��������, ���� �����������, ���� �� �������� ������ ����� � �������� ������
		gr0 - gr5;
		if =0 delayed goto save_last_word;
			ar5 = mass1;
			nul;
			//�������� ����� �����
			gr6 = gr0 >> 1;
			gr6 = gr6 - 1;
			vlen = gr6;
			fpu 0 rep vlen vreg7 = [ar5++];
			fpu 0 rep vlen [ar1++] = vreg7;

		save_last_word:
			gr5 = [ar5];
			[ar1] = gr5;
			goto exit; //����������� ���������� ����� ����������, ����� ��������


save_result_normal:
	fpu 0 rep vlen [ar1++] = vreg7;
	gr0 = gr0 - gr4;
	if > goto main_loop;
	
exit:
	ar7 = ar7 - 130;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    return; 
