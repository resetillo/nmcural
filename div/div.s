#.global _nmppsDivC_8u_Sfs
#.global _half_dbl
#.global _two_dbl
#.global _nan_dbl

.data
//nb63: .long 0xC000000000000000L // nb 1-63
SB:
	  .long 0x00000001 // 1 stroka
	  .long 0x00000000
NB:
	  .long 0x00000000 // 1 stolbets
      .long 0x80000000
WB:
      .long 0x00000001
      .long 0x00000000
BIAS:
      .long 0x00000000
	  .long 0x3ff00000
SIGN_BIT:
	  .long 0xffffffff
      .long 0x7fffffff
DpCode_const:
	  .long 0
	  .long 0x80200000

.text
/**
@function nmppsSqrt_64f
*/
_nmppsDivC_8u_Sfs:
    ar5 = ar7 - 2;
    
    // ���������� � ����� ���������, ����� ��������� �� �����������
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
    //sir = [nb63]
    sir = [NB];
    nb1 = sir;	
    sir = [SB];
    sb = sir;	
	ar2 = WB;
    rep 1 wfifo = [ar2], ftw, wtw; // �������� �������  �����
	
	gr2 = true;
	gr2 = gr2 + gr1;
	vlen = gr2;

    //���������� ������������� �������� X = ~sqrt(x)
	ar2 = BIAS;
	rep 32 ram = [ar2];
	ar2 = ar1;
    rep 32 data = [ar2++] with data - ram; //�������� BIAS
    rep 32 with vsum, shift afifo, 0; //�������� ������ �� 1
    rep 32 with afifo + ram; //���������� BIAS
    ar2 = SIGN_BIT;
    rep 32 data = [ar2] with afifo and data;//�������� � ������

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
	fpu 0 rep vlen vreg2 = [ar6++];//Y

	ar2 = _two_dbl;
	fpu 0 rep vlen vreg6 = [ar2];//2


	ar2 = _half_dbl;
	fpu 0 rep vlen vreg5 = [ar2];//0.5
	//������� ��������
	//Y0 = (2.0 - X0*Y)*Y
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;
	
	//������ ��������
	//X1 = 0.5*(X0 + A*Y0)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;
	//������� �������� Y1 = 1/X1
	//Y1_ = (2.0 - X1*Y0)*Y0
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;
	//Y1 = (2.0 - X1*Y1_)*Y1_
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;


	//������ ��������
	//X2 = 0.5*(X1 + A*Y1)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;
	//������� �������� Y2 = 1/X2
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	//3� ��������
	//X3 = 0.5*(X2 + A*Y2)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;
	//������� �������� Y3 = 1/X3
	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	fpu 0 .double vreg3 = -vreg1*vreg2 + vreg6;
	fpu 0 .double vreg2 = vreg3*vreg2;

	//4� ��������
	//RESULT = 0.5*(X3 + A*Y3)
	fpu 0 .double vreg3 = vreg0*vreg2 + vreg1;
	fpu 0 .double vreg1 = vreg5*vreg3;

	//������ �������� �������
	ar2 = _nan_dbl;
    fpu 0 rep vlen vreg6 = [ar2];
	ar2 = ar1;
    fpu 0 rep vlen vreg5 = [ar1++];

    //�������� �� nan & inf
    fpu 0 .double vreg5 - vreg5, set mask if <>0;
    fpu 0 .double vreg1 = mask ? /vreg5/ : vreg1;

	//�������� �� 0
    fpu 0 .double vreg5 + vreg5, set mask if =0;
    fpu 0 .double vreg1 = mask ? vreg5 : vreg1;

	//�������� �� �������������
    fpu 0 .double vreg5 + vreg5, set mask if <;
    sir = fp0_dmask;
    fpu 0 .double vreg1 = mask ? vreg6 : vreg1;
    gr0 = sir;
    gr0;
    if =0 goto save_result;
	gr7 = 3;
save_result:
	fpu 0 rep vlen [ar0++] = vreg1;
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
    return; 
