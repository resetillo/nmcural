.global _nmppsArctan_64f

.global _tanTable
.global _angTable

.global _one_dbl
.global _zero_dbl
.global _half_pi_dbl
.global _nan_dbl

.global __macro_change_infinity



.text

_nmppsArctan_64f:
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar5, gr5;
    gr7 = 0;//�� ��������� ���������� 0
    ar0 = [--ar5];//pSrc
    ar1 = [--ar5];//pDst
    gr0 = [--ar5];//len

    gr0;
    if <= goto err_size;
    gr1 = ar0;
    gr1;
    if =0 goto err_ptr;
    gr1 = ar1;
    gr1;
    if =0 goto err_ptr;

main_loop:
    gr1 = 32;
    gr2 = gr0;
    gr0 - gr1;
    if <= goto after_correct;
    gr2 = 32;
after_correct:
    gr1 = true;
    gr1 = gr1 + gr2; //gr2 -1
    vlen = gr1;//�������� �����
    //0
    ar2 = _zero_dbl;
    fpu 0  rep  vlen  vreg0 = [ar2];
	//1
    ar2 = _one_dbl;
    fpu 0  rep  vlen  vreg1 = [ar2];

	//X = 1
	fpu 1  vreg1 = fpu 0 vreg1;
	//������� �������� Y
    ar2 = ar0;
    fpu 1  rep  vlen  vreg5 = [ar2++];//������������ Y ��� �������������� ����� ����������
    fpu 1  .double vreg2 = /vreg5/;//������ Y ��� ��������
    
    //sum_angle = 0
    fpu 0  vreg7 = vreg0;//�������� ������
    
    //����
    gr1 = 52;//52;
    ar2 = _tanTable;//������� ���������
    ar3 = _angTable;//������� �����
arctan_cycle:
    fpu 0  rep vlen vreg2 = [ar2];
    ar2+=2; //����� double
    fpu 0  rep vlen vreg3 = [ar3];
    ar3+=2; //����� double


    //s = copysign(1, y)
    fpu 0  vreg6 = fpu 1 vreg2;
    fpu 0  vreg4 = fpu 0 vreg1;
    fpu 0  .double vreg6 + vreg6, set mask if <;
    fpu 0  .double vreg4 = mask ? - vreg4 : vreg4;

    //Xnew = x + s*y*t;
    fpu 0  vreg5 = fpu 1 vreg1;//x

    #fpu 0  vreg6 = fpu 1 vreg2;//y
    fpu 0  .double vreg6 = vreg6 * vreg4;//y*s
    fpu 0  .double vreg6 = vreg6 * vreg2 + vreg5;//y*s*t + x
    fpu 1  vreg3 = fpu 0 vreg6;//Xnew

    //Ynew = y - s*x*t;
    #fpu 0  vreg5 = fpu 1 vreg1;//x
    fpu 0  vreg6 = fpu 1 vreg2;//y
    fpu 0  .double vreg5 = vreg5 * vreg4;//x*s
    fpu 0  .double vreg5 = -vreg5 * vreg2 + vreg6;//-x*s*t + y
    fpu 1  vreg4 = fpu 0 vreg5;//Ynew

     //sum_angle = sum_angle + s*a;
    fpu 0  .double vreg7 = vreg4 * vreg3 + vreg7;//s*a
    
    
	//x =  Xnew;
	fpu 1 vreg1 = fpu 1  vreg3;
	//y =  Ynew;
	fpu 1 vreg2 = fpu 1 vreg4;
	gr1 = gr1 - 1;
	if > goto arctan_cycle;

	//���������� NAN � INF
	fpu 0 vreg5 = fpu 1 vreg5;//������������ ������
    fpu 0 .double vreg5 - vreg5, set mask if <>0;
    fpu 0 .double vreg7 = mask ? vreg5 : vreg7; //��� nan & inf ����������� ����������� ��������

	//������������� ���������� ��������� ������� ������ �� ��������
	/*	ar0 - input vector
		ar1 - changing value
		gr0 - length of vector
		vreg7 - out vector*/
    push ar0, gr0;
    push ar1, gr1;
	ar0 = ar1;
    fpu 0 rep vlen [ar0++] = vreg7;
    ar0 = ar1;
    ar1 = _half_pi_dbl; //arctan(inf) = pi/2
    gr0 = gr2;
	call __macro_change_infinity;
    pop ar1, gr1;
    pop ar0, gr0;

    //����������� �������� ����
    fpu 0 vreg6 = fpu 1 vreg5;
    fpu 0 .double vreg6 + vreg6, set mask if <;
    fpu 0 .double vreg7 = mask ? -vreg7 : vreg7;
    fpu 0 rep vlen [ar1++] = vreg7;


    push gr0;
    gr0 = gr2 << 1; //�������� � double
    ar0 = ar0 + gr0;
    pop gr0;
    gr1 = 32;
    gr0 = gr0 - gr1;
    if > goto main_loop;

    goto exit;
    
err_size:
    gr7 = -6;
    goto exit;
err_ptr:
    gr7 = -8;
    goto exit;
 
exit:
    pop ar5, gr5;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return;

