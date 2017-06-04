.global _nmppsRandUniform8u
.global _nmppsRandUniform16s

.data

	A8u:	.quad 137
	C8u: 	.quad 187
	X08u: 	.quad 121

	A16s: 	.quad 1664525
	C16s: 	.quad 1013904223
	X016s: 	.quad 12345


.text

//X = X08u*A8u+C8u;
_nmppsRandUniform8u:

	gr7 = false;
	nb1 = gr7;
	sb  = gr7;
	ar5 = A8u;

	rep 1 wfifo=[ar5],ftw;

	ar5 = ar7 - 2;
	push ar2,gr2;
    push ar6,gr6;
	
    ar6 = [--ar5];			// pSrc
    gr7 = [--ar5];			// len

	gr6 = ar6;
	gr6;
	if =0 goto ptr_err_rand8u;

	gr7;
	if <= goto err_len_rand8u;

	ar5 = X08u;
	vr  = [C8u];
	wtw;

	rep 1 data=[ar5] with vsum ,data,vr;

next_rand8u:
	rep 1 [ar5]=afifo with afifo;

	gr6 = 255;
	gr2 = [ar5];
	gr2 = gr2 and gr6;
	[ar6++] = gr2;
	[ar5] = gr2;
	//[ar5+1] = 0;

	gr7=gr7-1;

	if > delayed goto next_rand8u;
	with vsum ,afifo,vr;
	nul;

	gr7=0; //nmppsStsNoErr
	goto exit_rand8u;
ptr_err_rand8u:
	gr7=-8;
	goto exit_rand8u;
err_len_rand8u:
	gr7=-6;
	//goto exit_rand8u;
exit_rand8u:
	pop ar6,gr6;
	pop ar2,gr2;

	return;

	
//X = X016s*A16s+C16s;
_nmppsRandUniform16s:
	gr7 = false;
	nb1 = gr7;
	sb  = gr7;
	ar5 = A16s;

	rep 1 wfifo=[ar5],ftw;

	ar5 = ar7 - 2;
	push ar2,gr2;
    push ar6,gr6;
	
    ar6 = [--ar5];			// pSrc
    gr7 = [--ar5];			// len

	gr6 = ar6;
	gr6;
	if =0 goto ptr_err_rand16s;

	gr7;
	if <= goto err_len_rand16s;

	ar5 = X016s;
	vr  = [C16s];
	wtw;

next_rand16s:
	rep 1 data=[ar5] with vsum ,data,vr;
	rep 1 [ar5]=afifo;


	gr2 = [ar5];
	gr6 = 0x0000FFFF;
	gr6 = gr2 and gr6;
	gr6 = gr6 >> 15;
	gr6 = gr6 - 1;
	if =0 goto otr_rand16s;

	gr6 = 0x7FFF;
	gr2 = gr2 and gr6;
	goto save_rand16s;

otr_rand16s:
	gr6 = 0xFFFF8000;
	gr2 = gr2 or gr6;

save_rand16s:
	[ar6++] = gr2;
	[X016s] = gr2;
	gr6=0;
	[X016s+1] = gr6;

	gr7=gr7-1;

	if > goto next_rand16s;

	gr7=0;
	goto exit_rand16s;
ptr_err_rand16s:
	gr7=-8;
	goto exit_rand16s;
err_len_rand16s:
	gr7=-6;
	//goto exit_rand16s;
exit_rand16s:
	pop ar6,gr6;
	pop ar2,gr2;

	return;

