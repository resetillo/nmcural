.global _nmppsSqrt_32f
.global _half_flt
.global _two_flt
.global _nan_flt

.data

SBx2:
	  .quad 0x200000002 // 2 ������
NBx2:
      .quad 0x80000000 // 2 �������
WB2x2:
      .quad 0x0000000000000001
      .quad 0x0000000100000000
BIAS:
	  .quad 0x3f8000003f800000
SIGN_BIT:
      .quad 0x7fffffff7fffffff
DpCode_const:
	  .quad 0x8100000081000000

.text
/**
@function nmppsSqrt_32f
*/
_nmppsSqrt_32f:
    ar5 = ar7 - 2;
    
    // ���������� � ����� ���������, ����� ��������� �� �����������
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar6, gr6;

    
    ar1 = [--ar5]; // �������� ������
    ar0 = [--ar5]; // �������������� ������
	gr1 = [--ar5]; // ������ 
				
	ar5 = ar7 + 2;
	ar6 = ar5 + 64;
	ar7 = ar7 + 130;

	gr7 = 0; //�������� �� ���������
	gr1;
    if <= goto err_size;
    gr0 = ar0;
    gr0;
    if =0 goto err_ptr;
    gr0 = ar1;
    gr0;
    if =0 goto err_ptr;

	//��������� ������� 63 ���
    sir = [NBx2];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar2 = WB2x2;
    rep 2 wfifo = [ar2++], ftw, wtw; // �������� �������  �����

	gr1 = gr1 >> 1;//� ������� �����

main_loop:
	gr3 = gr1;
	gr2 = 32;
	gr3 - gr2;
    if <= goto after_correct;
    gr3 = 32;

after_correct:
	gr2 = true;
	gr3 = gr2 + gr3;
	vlen = gr3;

    //���������� ������������� �������� X = ~sqrt(x)
	ar2 = BIAS;
	rep 32 ram = [ar2];
	ar2 = ar1;
    rep 32 data = [ar2++] with data - ram; //�������� BIAS
    ####################
    /*rep 16 [ar0++] = afifo;
    goto exit;*/
    ####################
    rep 32 with vsum, shift afifo, 0; //�������� ������ �� 1
    rep 32 with afifo + ram; //���������� BIAS
    ar2 = SIGN_BIT;
    rep 32 data = [ar2] with afifo and data;//�������� � ��������������

    //���������� ���������� X = ~sqrt(x)
	ar2 = ar5;
    rep 32 [ar2++] = afifo;


    //���������� ������������� �������� Y = 1/~sqrt(x)
    ar2 = ar5;
	rep 32 data = [ar2++] with not data;
    ar2 = DpCode_const;
    rep 32 data = [ar2] with afifo - data; // 1/x ~ ������� ���������� x
    //���������� ���������� Y = 1/~sqrt(x)
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
	ar2 = ar1;
	fpu 0 rep vlen vreg0 = [ar2++];//A
	fpu 0 rep vlen vreg1 = [ar5++];//X0
	/*####################
    fpu 0 rep 16 [ar0++] = vreg1;
    goto exit;
    ####################*/
	fpu 0 rep vlen vreg2 = [ar6++];//Y

	ar2 = _two_flt;
	fpu 0 rep vlen vreg6 = [ar2];//2


	ar2 = _half_flt;
	fpu 0 rep vlen vreg5 = [ar2];//0.5
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
	fpu 0 .float vreg1 = vreg5*vreg3;

	//������ �������� �������
	ar2 = _nan_flt;
    fpu 0 rep vlen vreg6 = [ar2];
	//ar2 = ar1;
    fpu 0 rep vlen vreg5 = [ar1++];//������� ������

    //�������� �� nan & inf
    fpu 0 .float vreg5 - vreg5, set mask if <>0;
    fpu 0 .float vreg1 = mask ? /vreg5/ : vreg1;

	//�������� �� 0
    fpu 0 .float vreg5 + vreg5, set mask if =0;
    fpu 0 .float vreg1 = mask ? vreg5 : vreg1;

	//�������� �� �������������
    fpu 0 .float vreg5 + vreg5, set mask if <;
    sir = fp0_lmask;
    gr0 = sir;
    sir = fp0_hmask;
    gr2 = sir;
    fpu 0 .float vreg1 = mask ? vreg6 : vreg1;
    gr0 or gr2;
    if =0 goto save_result;
	gr7 = 3;
save_result:
	fpu 0 rep vlen [ar0++] = vreg1;

    gr2 = 32;
	gr1 = gr1 - gr2;
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
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return; 
