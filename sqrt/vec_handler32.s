
.global _vec_handler32
.global __test_func_vh32

.data

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
	//������ ����� ��������, ���������� �������� �����
    sir = [NB];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar5 = WBhi;
    rep 2 wfifo = [ar5++], ftw, wtw; // �������� �������  �����
    

    //�������� ������� �����
	ar5 = ar1;
	ar5 = ar5 - 1;
	rep 32 ram = [ar5++];
	rep 32 with vsum, ram, 0;
    //rep 32 data = [ar5++] with vsum, data, 0;
    ar5 = ar3;
    rep 32 [ar5++] = afifo;

    //���� ����� ��������, ����� ���������� �������� 63
    gr5 = 63;
    gr2 - gr5;
    if < goto L1notnul;
    gr2 = 63;
    //+ � ����� ������ �������� ������� �����
    gr5 = 64;
    ar5 = ar3;
    ar5 = ar5 + gr5 with gr5 = false;
    ar5 = ar5 + 2;
    [--ar5] = gr5;
    [--ar5] = gr5;
L1notnul:
    //�������� ������� �����
	ar5 = WBlow;
    rep 2 wfifo = [ar5++], ftw, wtw; // �������� �������  �����
    ar5 = ar1;
	ar5 = ar5 - 1;
    //rep 32 data = [ar5++] with vsum, data, 0;
    rep 32 ram = [ar5++];
    rep 32 with vsum, ram, 0;
    ar5 = ar3 + 2;//�������� �� ��������� � 1 �����
    //rep 32 data = [ar5++] with data or afifo; //��������
    rep 32 ram = [ar5++];
    rep 32 with ram or afifo; //��������
    ar5 = ar3;//�������� ���������� ������
    rep 32 [ar5++] = afifo;
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
    //ar0 = __test_func;
    call ar0; //����� �������
    //��������� � fpu 0 vreg7
    //�������������� ������� ����� ��� ��������� ��������
    gr5 = ar1;
    gr5 = gr5 + gr2;
    ar1 = gr5;

	gr0 = ar2;
	gr3 = 1;
	gr3 and gr0;
	if =0 goto even_adr2;

	######################################################
	##����������� �������� ���������� �� ��������� ������
	######################################################
	gr3 and gr2;
    if =0 delayed goto L2even_output_size;
	gr3 = gr2 >> 1;
	nul;
	gr3 = gr3 + 1;
L2even_output_size:
    gr3 = gr3 - 1;
    vlen = gr3;
    ar5 = ar3;
    fpu 0 rep vlen [ar5++] = vreg7;
    //�������� ������ ����� �� ��������� ������
    gr0 = [ar3];
    [ar2] = gr0;
    ar2 = ar2 + 1; // ������ ����� ������

	gr5 = 1;
	gr1 - gr5;
	if =0 goto exit;//����������� ��������� �����

    gr3;
    if =0 delayed goto L2_last_word_copy;//�������� 2 ����� �� ��������� ������, �������� �� �����
	gr3 = gr2 - 1;
	nul;


    //���������� ������� ���� � ��������� ������

    //�.�. ����� �����
    sir = [NB];
    nb1l = sir;
    nb1h = sir;
    sir = [SBx2];
    sbl = sir;
    sbh = sir;
	ar5 = WBhi;
    rep 2 wfifo = [ar5++], ftw, wtw; // �������� �������  �����

    //�������� ������� �����
	ar5 = ar3;
	rep 32 ram = [ar5++];
	rep 32 with vsum, ram, 0;
    //rep 32 data = [ar5++] with vsum, data, 0;
    ar5 = ar3+68;
    rep 32 [ar5++] = afifo;
    //�������� ��������� ����� � �������
    ar5 = ar3 + 134;//68 + 66
         with gr5 = false;
    [--ar5] = gr5;
    [--ar5] = gr5;
    //�������� ������� �����
	ar5 = WBlow;
    rep 2 wfifo = [ar5++], ftw, wtw; // �������� �������  �����
	ar5 = ar3;
	rep 32 ram = [ar5++];
	rep 32 with vsum, ram, 0;
    //rep 32 data = [ar5++] with vsum, data, 0;
 /*   ####################
    gr5 = 10;
    gr1 - gr5;
    if > goto Continue_debug;
    rep 32 [ar2++] = afifo;
    goto exit;
    Continue_debug:

    ####################*/



    ar5 = ar3 + 70;//�������� �� ��������� � 1 �����
	rep 32 ram = [ar5++];
    rep 32 with ram or afifo; //��������
    //rep 32 data = [ar5++] with data or afifo; //��������
    ar5 = ar3;//�������� ���������� ������
    rep 32 [ar5++] = afifo;

	gr3 = gr2 - 1; //�� 1 ������, �.�. ������ ����� ��� �����������
    gr3 = gr3 >> 1; //��������� ����� ��� ��������� �������� ����� �����
    gr3 = gr3 - 1;
    vlen = gr3;
    ar5 = ar3;
    fpu 0 rep vlen vreg7 = [ar5++] ;
    fpu 0 rep vlen [ar2++] = vreg7;
    //�������� ���� ����������� ��� ���� �����
	gr3 = gr2 - 1;
	gr0 = 1;
	gr3 and gr0;
	if =0 goto next_iteration;//����������� �� �����
	gr3 = gr3 - 1;
L2_last_word_copy:
	gr5 = [ar3 + gr3];
	[ar2] = gr5;
	ar2 = ar2 + 1; //�� ��������� �������� ����� ����� �������� �����, ��� ��������

	goto next_iteration;


even_adr2:
	gr2 and gr3;
	if =0 delayed goto simple_save;
    gr3 = gr2 >> 1;
    nul;

	gr1 - gr2;
	if > delayed goto simple_save;
	gr3 = gr2 + 1;
    gr3 = gr3 >> 1;
	######################################################
	##����������� �������� ���������� ����� �����
	##���� ������ ��������, �� ���������� ���� ����� �����, ����
	##�� �������� ������, ������������� ����� ���������� ����� ��������� �������
	######################################################
    gr3 = gr2 >> 1;
    gr3;
    if =0 delayed  goto save_last_word;//����������� 1 ����� - �������������� ��������
    ar5 = ar3;
    nul;

    //gr3 = gr3 - 1;
    vlen = gr3;
    fpu 0 rep vlen [ar5++] = vreg7;

	gr3 = gr3 - 1;
    vlen = gr3;
    ar5 = ar3;
    fpu 0 rep vlen vreg7 = [ar5++];
    fpu 0 rep vlen [ar2++] = vreg7;
    //��������� ��������� �����
save_last_word:
    gr5 = [ar5];
    [ar2] = gr5;
    ar2 = ar2 + 1;
	goto next_iteration;

simple_save:
    gr3 = gr3 - 1;
    vlen = gr3;
    fpu 0 rep vlen [ar2++] = vreg7;
    gr3 = 1;
    gr2 and gr3;
    if =0 goto next_iteration;
    ar2 = ar2 - 1;

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
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
    return; 