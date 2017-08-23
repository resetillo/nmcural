.global _nmppsWinBartlett_32fc
.global _c2dlen
.global _len_1
.global _c2_0
.global _tmp_

.data

.align
arr: .float 0.0,0.0,1.0,1.0,2.0,2.0,3.0,3.0,4.0,4.0,5.0,5.0,6.0,6.0,7.0,7.0
	 .float 8.0,8.0,9.0,9.0,10.0,10.0,11.0,11.0,12.0,12.0,13.0,13.0,14.0,14.0,15.0,15.0
	 .float 16.0,16.0,17.0,17.0,18.0,18.0,19.0,19.0,20.0,20.0,21.0,21.0,22.0,22.0,23.0,23.0
	 .float 24.0,24.0,25.0,25.0,26.0,26.0,27.0,27.0,28.0,28.0,29.0,29.0,30.0,30.0,31.0,31.0

.align
arr_add: .float 32.0, 32.0

.align
_c2dlen: .float 0.0, 0.0

.align
_c2_0: .float 2.0,2.0

.align
_len_1: .float 0.0, 0.0

.align
_tmp_: .float 0.0, 0.0


.text

//nmppsStatus nmppsWinBartlett_32fc(const nmpps32fc*  pSrc, nmpps32fc* pDst, int len)
//dst[i] = src[i]+i*2.0/(len-1) ,i=0,..,(len-1)/2
//dst[i] = src[i]+2-i*2.0/(len-1) ,i=(len-1)/2+1,....,len-1
_nmppsWinBartlett_32fc:
	ar5 = ar7 - 2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0=[--ar5]; //src
	ar2=[--ar5]; //dst
	gr0=[--ar5]; //len
	ar6=ar2;
	gr7=ar0;
	gr7;
	if =0 goto winbart32fc_null_ptr;
	gr7=ar2;
	gr7;
	if =0 goto winbart32fc_null_ptr;
	gr7=3;
	gr0 - gr7;
	if < goto winbart32fc_err_size;

	gr7=gr0-1; //len-1
	gr1=gr7>>1; //(len-1)/2
	gr1=gr1+1;	//(len-1)/2 + 1 , т.к. n меняется от 0 до (len-1)/2 включительно
	ar1=_len_1;

	//(len-1) : int => float
	[ar1] = gr7;
	fpu rep 1 .packer=[ar1] with .float <= .fixed_32 .in_low;
	fpu rep 1 [ar1] = .packer;

//делим 2.0 на len-1, результат в c2dlen
	ar1 = 1;
	push ar1; //len
	ar1 = _c2dlen;
	push ar1; //dst
	ar1 = _len_1;
	push ar1;
	ar1 = _c2_0;
	push ar1;
	call _nmppsDiv_32f;
	ar7 = ar7 - 4;

	ar1=_c2dlen;
	gr2=[ar1++];
	[ar1]=gr2;

	gr2 = gr1>>5;
	if <= goto _l2;

	ar1=arr;
	ar3=_c2dlen;
	ar4=arr_add;
	fpu 0 rep 32 vreg0 = [ar1++];

_l1:
	fpu 0 rep 1 vreg1 = [ar3];
	fpu 0 .float vreg2 = vreg0*.retrive(vreg1);
	fpu 0 rep 32 vreg3 = [ar0++];
	fpu 0 .float vreg3 = vreg3*vreg2;
	fpu 0 rep 32 [ar2++]=vreg3;
	gr2=gr2-1;
	if >  delayed goto _l1;
	fpu 0 rep 1 vreg4 = [ar4];
	fpu 0 .float vreg0=vreg0+.retrive(vreg4);

_l2:
	gr3=0x1F;
	gr3=gr1 and gr3;
	if =0 goto _l3;

	gr2=gr1>>5;
	gr2=gr2<<5;
	//преобразовать g2 из int в float
	ar1=_tmp_;
	[ar1]=gr2;
	[ar1+1]=gr2;
	fpu rep 1 .packer=[ar1] with .float <= .fixed_32;

	fpu 0 rep 1 vreg4 = .packer;

	ar1 = arr;
	gr3=gr3-1;
	vlen = gr3;
	fpu 0 rep vlen vreg0 = [ar1++];

	fpu 0 .float vreg0 = vreg0+.retrive(vreg4);

	ar1 = _c2dlen;
	fpu 0 rep 1 vreg1 = [ar1];
	fpu 0 .float vreg2 = vreg0*.retrive(vreg1);
	fpu 0 rep vlen vreg3 = [ar0++];
	fpu 0 .float vreg3 = vreg3*vreg2;
	fpu 0 rep vlen [ar2++]=vreg3;

_l3:
	gr2=gr0-gr1;

	gr7=gr2>>5;
	if =0 goto _l5;

	//преобразование int->float
	ar1=_tmp_;
	gr3=gr1>>1;
	gr3=gr3<<1;
	[ar1]=gr3;
	[ar1+1]=gr3;
	fpu rep 1 .packer=[ar1] with .float <= .fixed_32;

	fpu 0 rep 1 vreg4 = .packer;


	ar1=arr;
	ar3=_c2dlen;
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 .float vreg0 = vreg0+.retrive(vreg4);
	ar1=arr_add;
	ar5=_c2_0;
_l4:
	fpu 0 rep 1 vreg1 = [ar3];
	fpu 0 .float vreg2 = vreg0*.retrive(vreg1);
	fpu 0 rep 32 vreg3 = [ar0++];
	fpu 0 .float vreg3 = vreg3*vreg2;
	fpu 0 rep 1 vreg5 = [ar5];
	fpu 0 .float vreg3 = -vreg3+.retrive(vreg5);
	fpu 0 rep 32 [ar2++]=vreg3;
	fpu 0 rep 1 vreg4 = [ar1];
	fpu 0 .float vreg0=vreg0+.retrive(vreg4);
	gr7=gr7-1;
	if >  goto _l4;

_l5:
	gr7=0x1F;
	gr7=gr2 and gr7;
	if =0 goto _l6;

	gr3=gr0-gr7;
	gr7=gr7-1;
	vlen=gr7;

	ar1=_tmp_;
	[ar1]=gr3;
	[ar1+1]=gr3;
	fpu rep 1 .packer=[ar1] with .float <= .fixed_32;

	fpu 0 rep 1 vreg4 = .packer;
	ar1=arr;
	fpu 0 rep vlen vreg0 = [ar1++];

	fpu 0 .float vreg0 = vreg0+.retrive(vreg4);

	ar1 = _c2dlen;
	ar5=_c2_0;
	fpu 0 rep 1 vreg1 = [ar1];
	fpu 0 .float vreg2 = vreg0*.retrive(vreg1);
	fpu 0 rep vlen vreg3 = [ar0++];
	fpu 0 .float vreg3 = vreg3*vreg2;
	fpu 0 rep 1 vreg5 = [ar5];
	fpu 0 .float vreg3 = -vreg3+.retrive(vreg5);
	fpu 0 rep vlen [ar2++]=vreg3;

_l6:
	gr7=0;
	goto winbart32fc_exit;
winbart32fc_null_ptr:
	gr7=-8;
	goto winbart32fc_exit;
winbart32fc_err_size:
	gr7=-6;
	//goto winbart32fc_exit;
winbart32fc_exit:
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
