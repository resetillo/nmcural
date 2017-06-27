
.global _vec_handler32
.global __test_func_vh32

.data

  .align 8

SBx2:
	  .quad 0x200000002 // 2 ������
NB:
      .quad 0x8000000000000000 // 1 �������
WBhi:
      .quad 0x0000000100000000
      .quad 0x0000000000000000
WBlow:
      .quad 0x0000000000000000
      .quad 0x0000000000000001

.text


__test_func_vh32:
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	push ar6, gr6;
	gr3 = 1;
	gr2 and gr3;
	
	if =0 delayed goto test_even;
	gr3 = gr2;
	nul;
	
	gr3 = gr3 + 1;
test_even:
	gr3 = gr3 >> 1;
	gr3 = gr3 - 1;
	vlen = gr3;
	ar5 = ar4;
	fpu 0 rep vlen vreg7 = [ar5++]; 
	

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
	@func int vec_handler32(int* func, int* in, int* out, int lenght)

	����������� �������� �� �������� � ���������� ������� ��� �������� � ���������� ������������� 32 ����.
	���������� ����������� ����� � ���������� ���������� �� ����� 64 ��������, ������ ���������� �������,
	� ��� �� �������� �� ������������ ���������� ������� � ����� ��������
	
	@param ar0 ����� ����������� ������� ��� ����������
	@param ar1 ����� �������� �������
	@param ar2 ����� ��������� �������
	@param gr1 ����� ������� � 32��������� ������

*/
_vec_handler32:


    ar5 = ar7 - 2;
    
    // ���������� � ����� ���������, ����� ��������� �� �����������
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;
    
    ar0 = [--ar5]; // function
    ar1 = [--ar5]; // input vector
    ar2 = [--ar5]; // output vector
	gr1 = [--ar5]; // lenght


    ar3 = ar7 + 2;
    // ar3 - ������� ������ �� 66 ����
    // ar3 + 68 - 2�� ������� ������ �� 66 ����
    ar7 = ar7 + 134;
    
    
    gr7 = 0; //�������� �� ���������
	gr1;
    if <= goto err_size;
    gr0 = ar1;
    gr0;
    if =0 goto err_ptr;
    gr0 = ar2;
    gr0;
    if =0 goto err_ptr;
    
main_loop:    
    gr2 = 64;
    gr1 - gr2;
    if >= goto after_size_correction;
    //���������� ������ ������ 64
    gr2 = gr1;
after_size_correction:  
	gr3 = 1;
	gr0 = ar1;
	gr0 and gr3;
	if =0 delayed goto even_adr1_check;
	ar4 = ar1;
	nul;
	
	################################################
	##����������� ������� ���������� � ������ �����
	################################################
	//���� ����� ��������, ����� ���������� �������� 63
    gr5 = 63;
    gr2 - gr5;
    if < goto L1notover63;
    gr2 = 63;
L1notover63:
	//������ ����� ��������, ���������� �������� ����� ������
	ar5 = ar1 - 1; //������� ������ ����� � ������ ������� ������
	gr3 = gr2 + 1;

	gr5 = 1;
	gr5 and gr3;
	if =0 delayed goto L1evenGr3;
	gr3 = gr3 >> 1;
	nul;

	gr3 = gr3 + 1; //��������, ���� ��������� �� 1
L1evenGr3:
	gr3 = gr3 - 1; //vlen �� �� 1 ������
	vlen = gr3;

	fpu 0 rep vlen vreg0 = [ar5++];

    //�������� ������� ����� � ������� �����
    fpu 0 .packer = vreg0 with .float .in_high <= .float .in_low;
    ar5 = ar3;
    fpu rep vlen [ar5++] = .packer; // �������� ������ ��� ����������� �������� �� ������� � 2 �����

    //�������� ������� 2 �����
    ar5 = ar5 + 2;
    gr5 = false;
    [--ar5] = gr5;
    [--ar5] = gr5;
    //�������� �� ���������
    ar5 = ar3 + 2;
    fpu 0 rep vlen vreg2 = [ar5++];

    //�������� ������� ����� � ������� �����
    fpu 0 .packer = vreg0 with .float .in_low <= .float .in_high;
    fpu 0 rep vlen vreg1 = .packer;
    //��������
    fpu 0 .float vreg0 = vreg1 + vreg2;

    ar5 = ar3;//�������� ���������� ������
    fpu 0 rep vlen [ar5++] = vreg0;


L1end_lastcopy:

	//C�������� �� ��������� - �������, ���� � ������� �� ����� ����� �� �����
	ar5 = ar3;
    gr5 = gr2;
    gr4 = false;
    [ar5 + gr5] = gr4;

    ar4 = ar3;
    
    gr3 = 1;
    gr2 and gr3;
    if =0 goto call_func;
    //���� ������ ��������, ������� ��������� �����
    gr3 = gr2;
    gr5 = false;
    [ar3+gr3] = gr5;
    
    goto call_func;

even_adr1_check:
    //������ ����� ������� ������
    //�� ��������� ���������� ������ ����� �� �������� ������
    gr3 = 1;
    gr2 and gr3;
    if =0 goto call_func;
    //�� ���� ������ ��������, ������������ � ������� ��������� �����
    //����� � ���������� ������� �� ����� ����� �� �����
    ar5 = ar1;
    rep 32 data = [ar5++] with data + 0;
    ar5 = ar3;
    rep 32 [ar5++] = afifo;
    
    gr3 = gr2;
    gr5 = false;
    [ar3+gr3] = gr5;
    ar4 = ar3;
	
call_func:
	
	//FIXME ���������� ����������
    call ar0; //����� �������
    //��������� � fpu 0 vreg7
    //�������������� ������� ����� ��� ��������� ��������
    gr5 = ar1;
    gr5 = gr5 + gr2;
    ar1 = gr5;


	gr3 = 1;
	gr2 and gr3;
	if <>0 goto L2_buf_copy;

	gr4 = ar2;
	gr3 and gr4;
	if <>0 goto L2_buf_copy;

simple_output:
    //������� ����������� �� ������ ����� ������� ���-�� ���������
	fpu 0 rep vlen [ar2++] = vreg7;
	goto next_iteration;

L2_buf_copy:
	//����������� ����� �����
	ar5 = ar3;
	fpu 0 rep vlen [ar5++] = vreg7; //���������� ���������� � �����

	gr4 = ar2;
	gr3 and gr4;
	if <>0 goto L2_shift_output;

	gr2 - 1;
	if =0 goto L2_lastword_copy;
	gr3 = gr2 >> 1;
	gr3 = gr3 - 1;
	vlen = gr3;
	ar5 = ar3;
	fpu 0 rep vlen vreg7 = [ar5++];
	fpu 0 rep vlen [ar2++] = vreg7;

L2_lastword_copy:
    //����������� ���������� �����
    gr3 = gr2 -1;
	gr5 = [ar3 + gr3];
	[ar2] = gr5;
	ar2 = ar2 + 1;
	goto next_iteration;


L2_shift_output:
	//����������� ����� �����
	//�� �������� �����

    //��� ������ ��������� ������ �����
    gr5 = [ar3];
    [ar2] = gr5;
    ar2 = ar2 + 1; //����� ������ ������

    gr2 - 1;
    if =0 goto next_iteration; //������ ����� �������� ���������

	gr3 = 2;
    gr2 - gr3;
	if =0 goto L2_lastword_copy; //������ ����� �����������, �������� ��������� (������)

	//�������� ������ �� vreg7
    //�������� ������� ����� � ������� �����
    fpu 0 .packer = vreg7 with .float .in_high <= .float .in_low;
    ar5 = ar3 + 68;
    fpu rep vlen [ar5++] = .packer; // �������� ������ ��� ����������� �������� �� ������� � 2 �����

    //�������� ������� 2 �����
    ar5 = ar5 + 2;
    gr5 = false;
    [--ar5] = gr5;
    [--ar5] = gr5;
    //�������� �� ���������
    ar5 = ar3 + 70;
    fpu 0 rep vlen vreg2 = [ar5++];

    //�������� ������� ����� � ������� �����
    fpu 0 .packer = vreg7 with .float .in_low <= .float .in_high;
    fpu 0 rep vlen vreg1 = .packer;
    //��������
    fpu 0 .float vreg0 = vreg1 + vreg2;

    ar5 = ar3 + 68;//�������� ���������� ������
    fpu 0 rep vlen [ar5++] = vreg0;

	//����������� ����� ����� ���� ������ ����� ��������� �������
    gr3 = gr2 - 1;
    gr3 = gr3 >> 1;
    gr3 = gr3 - 1;
    vlen = gr3;

    ar5 = ar3 + 68;
    fpu 0 rep vlen vreg0 = [ar5++];
    fpu 0 rep vlen [ar2++] = vreg0 ;

	gr3 = 1;
	gr2 and gr3;
	if =0 goto L2_lastword_copy;//���������� ����������� ��������� �����

next_iteration:
    gr1 = gr1 - gr2;
    if > goto main_loop;
	goto exit;
	
err_size:
    gr7 = -6;
    goto exit;
err_ptr:
    gr7 = -8;
    goto exit;
exit:
    ar7 = ar7 - 134;
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return; 
