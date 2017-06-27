.global _nmppsDivC_32f
.global nmppsDivC_32f_body

.global _zero_flt
.global _two_flt
.global _bigest_flt
.global _nan_flt
.global _inf_flt
.global SIGN_BIT_flt
.global DpCode_const_flt

.global NB_default
.global SB_default
.global WB_default

.global NBx2
.global SBx2
.global WB2x2



.text
/**
@function nmppsDivC_32f
*/
_nmppsDivC_32f:

    ar5 = ar7 - 2;

    // ���������� � ����� ���������, ����� ��������� �� �����������
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;

    ar1 = [--ar5]; // Divided vector
    gr2 = [--ar5]; // Divisor
    ar0 = [--ar5]; // Output vector
	gr1 = [--ar5]; // Lenght



	gr1;
    if <= delayed goto exit;
    gr7 = -6;

    gr0 = ar0;
    gr0;
    if =0 delayed goto exit;
    gr7 = -8;

    gr0 = ar1;
    gr0;
    if =0 delayed goto exit;
    gr0 = ar2;
    gr0;
    if =0 goto exit;


	call nmppsDivC_32f_body;

exit:
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;

/*
    ar1  Divided vector
    gr2  Divisor
    ar0  Output vector
	gr1  Lenght
*/
nmppsDivC_32f_body:
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

	ar3 = ar7 + 2; //��������������� ������ �� 64 �����
	ar4 = ar7 + 66; //��������������� ������ �� 64 �����
	ar2 = ar7 + 130;
	ar7 = ar7 + 132;

	gr7 = 0; //�������� �� ���������
	[ar2] = gr2; //�������� divisor
	[ar2+1] = gr2; //�������� divisor

	//��������� ����������
    sir = [NBx2];
    nb1 = sir;
    sir = [SBx2];
    sb = sir;
	ar5 = WB2x2;
    rep 2 wfifo = [ar5], ftw, wtw; // �������� �������  �����

	gr0 = 0;// ����� ����� ���������������� �������� ������� �� 0

calc_obr:
	ar5 = _two_flt;
	fpu 0 rep 1 vreg2 = [ar5]; //2.0

	//������� ������������� �������� ~1/divisor
	rep 1 data = [ar2] with not data;
    ar5 = DpCode_const_flt;
    rep 1 data = [ar5] with afifo - data; // ~1/divisor ~ ������� ���������� divisor
    //���������� ���������� ~1/divisor
	rep 1 [ar4] = afifo;


	fpu 0 rep 1 vreg1 = [ar2]; //divisor
	fpu 0 rep 1 vreg7 = [ar4]; //~1/divisor

	//�������� ��������
	//~1/divisor = (2.0 - (~1/divisor)*divisor)*(~1/divisor);
	fpu 0 .float vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .float vreg7 = vreg0*vreg7;
	//2
	fpu 0 .float vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .float vreg7 = vreg0*vreg7;
	//3
	fpu 0 .float vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .float vreg7 = vreg0*vreg7;
	//4
	fpu 0 .float vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .float vreg7 = vreg0*vreg7;
	//5
	/*fpu 0 .float vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .float vreg7 = vreg0*vreg7;
	//6
	fpu 0 .float vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .float vreg7 = vreg0*vreg7;*/

	fpu 0 rep 1 [ar4] = vreg7; //~1/divisor

	gr3 = 64;
	gr3 - gr1;
	if > goto main_loop;
	/*
		vreg0 tmp / divided
		vreg1 divisor
		vreg2 2.0
		vreg3 bigest
		vreg4 zero
		vreg5 nan
		vreg6 infinity
		vreg7 result
	*/
	//��������� ������, ������������ ������ ��������
	ar5 = _bigest_flt;
	fpu 0 rep 32 vreg3 = [ar5]; //bigest float
	ar5 = _zero_flt;
	fpu 0 rep 32 vreg4 = [ar5]; //zero float
	ar5 = _nan_flt;
	fpu 0 rep 32 vreg5 = [ar5]; //nan float
	ar5 = _inf_flt;
	fpu 0 rep 32 vreg6 = [ar5]; //infinity float

	fpu 0 rep 32 vreg1 = [ar2]; // divisor
	fpu 0 rep 32 vreg2 = [ar4]; //~(1/divisor)

	gr3 = 31;
	vlen = gr3;



main_loop:
	gr3 = 64; //�������
	gr3 - gr1;
    if <= goto after_correct;
	    //������� ������ 64, ������������ �������������� ������
		gr3 = gr1 >> 1;
		gr5 = 1;
		gr1 and gr5;
		if <>0 goto ML1;
		gr3 = gr3 - 1; //���� ������ �������� �� 1, ��� �������� ��� ��������� ��� ������
		ML1:
		vlen = gr3;
		//��������� ������ � ������������ � �������� �������
		ar5 = _bigest_flt;
		fpu 0 rep vlen vreg3 = [ar5]; //bigest float
		ar5 = _zero_flt;
		fpu 0 rep vlen vreg4 = [ar5]; //zero float
		ar5 = _nan_flt;
		fpu 0 rep vlen vreg5 = [ar5]; //nan float
		ar5 = _inf_flt;
		fpu 0 rep vlen vreg6 = [ar5]; //infinity float

		fpu 0 rep vlen vreg1 = [ar2]; // divisor
		fpu 0 rep vlen vreg2 = [ar4]; //~(1/divisor)

after_correct:

	//Output = divided*(~1/divisor)
	ar5 = ar1;
	fpu 0 rep vlen vreg0 = [ar5++]; //divided
	fpu 0 .float vreg7 = vreg0*vreg2;

	######################################
	##   �������� ����������
	######################################
	//�������� �� �������������
	fpu 0 .float vreg0 = /vreg0/; //� ����� ����������� � �����
	fpu 0 .float vreg3 - vreg0, set mask if <;
    sir = fp0_lmask;
    gr3 = sir;
    sir = fp0_hmask;
    gr4 = sir; //gr3, gr4 - ����� � divided = infinity

	//divided = infinity => out = infinity
	fpu 0 .float vreg7 = mask ? vreg6 : vreg7;


	fpu 0 .float vreg1 = /vreg1/;//� ����� ����������� � �����
	fpu 0 .float vreg3 - vreg1, set mask if <;
    sir = fp0_lmask;
    gr5 = sir;
    sir = fp0_hmask;
    gr6 = sir; //gr5, gr6 - ����� � divisor = infinity

	//divisor = infinity => out = 0
	fpu 0 .float vreg7 = mask ? vreg4 : vreg7;

	//divided = divisor = infinity => out = NAN
	gr2 = gr3 and gr5;
	sir = gr2;
	fp0_lmask = sir;
	gr2 = gr4 and gr6;
	sir = gr2;
	fp0_hmask = sir;
	fpu 0 .float vreg7 = mask ? vreg5 : vreg7;

	//�������� � �����
    push gr6;
    push gr5;
    push gr4;
    push gr3;


	//�������� ������� �� 0
    fpu 0 .float vreg0 + vreg0, set mask if =0;
    sir = fp0_lmask;
    gr3 = sir;
    sir = fp0_hmask;
    gr4 = sir;//����� � divided = 0

    //0 div infinity
	gr2 = gr3 and gr5;
	sir = gr2;
	fp0_lmask = sir;
	gr2 = gr4 and gr6;
	sir = gr2;
	fp0_hmask = sir;
	fpu 0 .float vreg7 = mask ? vreg5 : vreg7; //divided =0, divisor = infinity => out = NAN


	//��������� �����
	//����������, ��� ��� ��������� ����� �������� ������ �� ����, ������� ������������� ������ � ��������� ��������
	//�.�. ���� ������ �������������� ������� ������ 64 �����, �� ��� ������������� �������� ������� �����
	//� ������ ����� �������� �����, ��� ��� ����� ���������� �������� ����� �������������� ������ �� ���
	//� ��������� ��������� (� ������ ������ ��� ������������ ��� ����������� ����� ������� �� 0)
	sir = gr0; //������ 0 ����� ������������ ������������� �������, �.�. ��� �������� ��� �������������
	fp0_lmask = sir;
	fp0_hmask = sir;

    fpu 0 .float vreg1 + vreg1, set mask if =0;
    sir = fp0_lmask;
    gr5 = sir;
    sir = fp0_hmask;
    gr6 = sir;//����� � divisor = 0

    //��� ������������ �������� ������� �� 0
    gr0 = gr0 or gr5;
    gr0 = gr0 or gr6;

	//divisor = 0 => out = infinity
	fpu 0 .float vreg7 = mask ? vreg6 : vreg7;

	//divided = divisor = 0 => out = NAN
	gr2 = gr3 and gr5;
	sir = gr2;
	fp0_lmask = sir;
	gr2 = gr4 and gr6;
	sir = gr2;
	fp0_hmask = sir;
	fpu 0 .float vreg7 = mask ? vreg5 : vreg7;




	//�������� �� NAN
	//����� � divided = NAN
    fpu 0 .float vreg0 - vreg0, set mask if <>0;
    sir = fp0_lmask;
    gr3 = sir;
    sir = fp0_hmask;
    gr4 = sir;

	//�������� �������������
	pop gr2;
    gr3 = gr3 and not gr2;
	pop gr2;
    gr4 = gr4 and not gr2;


	//����� � divisor = NAN
    fpu 0 .float vreg1 - vreg1, set mask if <>0;
    sir = fp0_lmask;
    gr5 = sir;
    sir = fp0_hmask;
    gr6 = sir;

	//�������� �������������
	pop gr2;
    gr5 = gr5 and not gr2;
	pop gr2;
    gr6 = gr6 and not gr2;

	//��������� ���������
    gr3 = gr3 or gr5;
	sir = gr3;
	fp0_lmask = sir;
    gr4 = gr4 or gr6;
	sir = gr4;
	fp0_hmask = sir;
	fpu 0 .float vreg7 = mask ? vreg5 : vreg7; //divided = NAN || divisor = NAN => out = NAN



	//divided*divisor ��� ����������� ����� ����������
	ar5 = ar1;
	rep 32 data = [ar5++] with data;
	rep 32 data = [ar2] with data xor afifo; //������ ����

	ar5 = SIGN_BIT_flt;
	rep 32 data = [ar5] with not data and afifo; //�������� ������� ���

	ar5 = ar3;

	fpu 0 rep vlen [ar5++] = vreg7;
	ar5 = ar3;
	rep 32 data = [ar5++] with data or afifo; //��������� ������ ������
	//�������� �������� ��������
	ar5 = ar3;
	rep 32 [ar5++] = afifo;

	gr5 = 64;
	gr1 -gr5;
	if >= goto common_out;
		//���������� ���������� ����� ������
		gr3 = gr1 >> 1;
		if =0 goto last_out;
		gr3 = gr3 - 1;
		vlen = gr3;
		ar5 = ar3;
		fpu 0 rep vlen vreg7 = [ar5++];
		fpu 0 rep vlen [ar0++] = vreg7;
		gr5 = 1;
		gr1 and gr5;
		if =0 goto check_zero_div;
		gr3 = gr1 - 1;
		ar3 = ar3 + gr3;
		last_out:
			//�������� ������, �������� ��������� ��� 1 �����
			gr5 = [ar3];
			[ar0] = gr5;
			goto check_zero_div;


common_out:
	ar5 = ar3;
	fpu 0 rep vlen vreg7 = [ar5++];

	//����������� ������ ��� ��������� ��������
	gr5 = VL;
	gr5 = gr5 + 1;
	gr5 = gr5 << 1;
	ar5 = ar1;
	ar1 = ar5 + gr5;



save_result:
	fpu 0 rep vlen [ar0++] = vreg7;

    gr2 = 64;
	gr1 = gr1 - gr2;
    if > goto main_loop;

check_zero_div:
    gr0;
    if =0 goto exit_body;

    gr7 = -10; //���� ������� �� 0

exit_body:
	ar7 = ar7 - 132;

    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
	return;
