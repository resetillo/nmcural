.global _nmppsDiv_64f

.global _zero_dbl
.global _two_dbl
.global _bigest_dbl
.global _nan_dbl
.global _inf_dbl
.global SIGN_BIT_dbl
.global DpCode_const_dbl

.global NB_default
.global SB_default
.global WB_default


.text
/**
@function nmppsDiv_64f
*/
_nmppsDiv_64f:

    ar5 = ar7 - 2;

    // ���������� � ����� ���������, ����� ��������� �� �����������
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;

    ar1 = [--ar5]; // Divided vector
    ar2 = [--ar5]; // Divisor vector
    ar0 = [--ar5]; // Output vector
	gr1 = [--ar5]; // Lenght

	ar3 = ar7 + 2; //��������������� ������ �� 64 �����
	ar7 = ar7 + 66;

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

	gr7 = 0; //�������� �� ���������

	//��������� ����������
    sir = [NB_default];
    nb1 = sir;
    sir = [SB_default];
    sb = sir;
	ar5 = WB_default;
    rep 1 wfifo = [ar5], ftw, wtw; // �������� �������  �����

	gr0 = 0;// ����� ����� ���������������� �������� ������� �� 0

	gr3 = 32;
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
	ar5 = _two_dbl;
	fpu 0 rep 32 vreg2 = [ar5]; //2.0
	ar5 = _bigest_dbl;
	fpu 0 rep 32 vreg3 = [ar5]; //bigest double
	ar5 = _zero_dbl;
	fpu 0 rep 32 vreg4 = [ar5]; //zero double
	ar5 = _nan_dbl;
	fpu 0 rep 32 vreg5 = [ar5]; //nan double
	ar5 = _inf_dbl;
	fpu 0 rep 32 vreg6 = [ar5]; //infinity double
	gr3 = 31;
	vlen = gr3;


main_loop:
	gr3 = 32; //�������
	gr3 - gr1;
    if <= goto after_correct;
    //������� ������ 32, ������������ �������������� ������
    //������ ������� ������ 32
	gr3 = gr1 - 1;
	vlen = gr3;
	//��������� ������ � ������������ � �������� �������
	ar5 = _two_dbl;
	fpu 0 rep vlen vreg2 = [ar5]; //2.0
	ar5 = _bigest_dbl;
	fpu 0 rep vlen vreg3 = [ar5]; //bigest double
	ar5 = _zero_dbl;
	fpu 0 rep vlen vreg4 = [ar5]; //zero double
	ar5 = _nan_dbl;
	fpu 0 rep vlen vreg5 = [ar5]; //nan double
	ar5 = _inf_dbl;
	fpu 0 rep vlen vreg6 = [ar5]; //infinity double

after_correct:

	//������� ������������� �������� ~1/divisor
	ar5 = ar2;
	rep 32 data = [ar5++] with not data;
    ar5 = DpCode_const_dbl;
    rep 32 data = [ar5] with afifo - data; // ~1/divisor ~ ������� ���������� divisor
    //���������� ���������� ~1/divisor
	ar5 = ar3;
	rep 32 [ar5++] = afifo;


	ar5 = ar2;
	fpu 0 rep vlen vreg1 = [ar5++]; //divisor
	ar5 = ar3;
	fpu 0 rep vlen vreg7 = [ar5++]; //~1/divisor

	//�������� ��������
	//~1/divisor = (2.0 - (~1/divisor)*divisor)*(~1/divisor);
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//2
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//3
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//4
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//5
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;
	//6
	fpu 0 .double vreg0 = -vreg7*vreg1 + vreg2;
	fpu 0 .double vreg7 = vreg0*vreg7;

	//Output = divided*(~1/divisor)
	ar5 = ar1;
	fpu 0 rep vlen vreg0 = [ar5++]; //divided
	fpu 0 .double vreg7 = vreg0*vreg7;

	######################################
	##   �������� ����������
	######################################
	//�������� �� �������������
	fpu 0 .double vreg0 = /vreg0/; //� ����� ����������� � �����
	fpu 0 .double vreg3 - vreg0, set mask if <;
    sir = fp0_dmask;
    gr3 = sir; //����� � divided = infinity

	fpu 0 .double vreg1 = /vreg1/;//� ����� ����������� � �����
	fpu 0 .double vreg3 - vreg1, set mask if <;
    sir = fp0_dmask;
    gr4 = sir; //����� � divisor = infinity


	sir = gr3;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg6 : vreg7; //divided = infinity => out = infinity

	sir = gr4;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg4 : vreg7; //divisor = infinity => out = 0

	gr5 = gr3 and gr4;
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided = divisor = infinity => out = NAN


	//�������� ������� �� 0
    fpu 0 .double vreg0 + vreg0, set mask if =0;
    sir = fp0_dmask;
    gr5 = sir;//����� � divided = 0

    fpu 0 .double vreg1 + vreg1, set mask if =0;
    sir = fp0_dmask;
    gr6 = sir;//����� � divisor = 0
    gr0 = gr0 or gr6; //��� ����������� ����������

	//sir = gr6;
	//fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg6 : vreg7; //divisor = 0 => out = infinity

	gr6 = gr5 and gr6;
	sir = gr6;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided = divisor = 0 => out = NAN

	//0 div infinity
	gr6 = gr5 and gr4;
	sir = gr6;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided =0, divisor = infinity => out = NAN


	//�������� �� NAN
    fpu 0 .double vreg0 - vreg0, set mask if <>0;
    sir = fp0_dmask;
    gr5 = sir;//����� � divided = NAN
    gr5 = gr5 and not gr3; //�������� �������������

    fpu 0 .double vreg1 - vreg1, set mask if <>0;
    sir = fp0_dmask;
    gr6 = sir;//����� � divisor = NAN
    gr6 = gr6 and not gr4; //�������� �������������

    gr5 = gr5 or gr6; //��������� ���������
	sir = gr5;
	fp0_dmask = sir;
	fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //divided = NAN || divisor = NAN => out = NAN



	//divided*divisor ��� ����������� ����� ����������
	ar5 = ar1;
	rep 32 data = [ar5++] with data;
	ar5 = ar2;
	rep 32 data = [ar5++] with data xor afifo; //������ ����

	ar5 = SIGN_BIT_dbl;
	rep 32 data = [ar5] with not data and afifo; //�������� ������� ���

	ar5 = ar3;
	fpu 0 rep vlen [ar5++] = vreg7;
	ar5 = ar3;
	rep 32 data = [ar5++] with data or afifo; //��������� ������ ������
	//�������� �������� ��������
	ar5 = ar3;
	rep 32 [ar5++] = afifo;
	ar5 = ar3;
	fpu 0 rep vlen vreg7 = [ar5++];

	//����������� ������ ��� ��������� ��������
	gr5 = VL;
	gr5 = gr5 + 1;
	gr5 = gr5 << 1;
	ar5 = ar1;
	ar1 = ar5 + gr5;
	ar5 = ar2;
	ar2 = ar5 + gr5;



save_result:
	fpu 0 rep vlen [ar0++] = vreg7;

    gr2 = 32;
	gr1 = gr1 - gr2;
    if > goto main_loop;

    gr0;
    if =0 goto exit;

    gr7 = -10; //���� ������� �� 0


exit:
	ar7 = ar7 - 66;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;



















