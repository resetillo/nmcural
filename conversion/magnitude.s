.global _nmppsMagnitude_64f
.global _nmppsMagnitude_64fc

.text

//nmppsStatus nmppsMagnitude_64f(const nmpps64f*  pSrcRe, const nmpps64f* pSrcIm, nmpps64f* pDst, int len);
_nmppsMagnitude_64f:
	ar5 = ar7 - 2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;

	ar0=[--ar5]; //srcre
	ar1=[--ar5]; //srcim
	ar2=[--ar5]; //dst
	gr0=[--ar5]; //len
	ar3=ar2;

	gr7=ar0;
	gr7;
	if =0 goto _mag64f_null_ptr;
	gr7=ar1;
	gr7;
	if =0 goto _mag64f_null_ptr;
	gr7=ar2;
	gr7;
	if =0 goto _mag64f_null_ptr;
	gr0;
	if <= goto _mag64f_err_size;

	gr7 = gr0>>5 ;
	if =0 goto _mag64f_end_cicl;

_mag64f_start_cicl:
	fpu 0 rep 32 vreg0=[ar0++];
	fpu 0 rep 32 vreg1=[ar1++];

	fpu 0 .double vreg0=vreg0*vreg0;
	fpu 0 .double vreg1=vreg1*vreg1;

	fpu 0 .double vreg0 = vreg0+vreg1;
	fpu 0 rep 32 [ar2++]=vreg0;
	gr7 = gr7-1;
	if > goto _mag64f_start_cicl;

_mag64f_end_cicl:
	gr2=0x001F;
	gr1 = gr0 and gr2;

	if =0 delayed goto  _mag64f_exit;
	gr7=0;
	nul;
	gr1=gr1-1;
	vlen=gr1;

	fpu 0 rep vlen vreg0=[ar0++];
	fpu 0 rep vlen vreg1=[ar1++];

	fpu 0 .double vreg0=vreg0*vreg0;
	fpu 0 .double vreg1=vreg1*vreg1;

	fpu 0 .double vreg0 = vreg0+vreg1;

	fpu 0 rep vlen [ar2++]=vreg0;

	push gr0; //len
	push ar3; //dst
	push ar3; //src
	call _nmppsSqrt_64f;
	ar7 = ar7 - 3;

	gr7=0;
	goto _mag64f_exit;

_mag64f_null_ptr:
	gr7=-8;
	goto _mag64f_exit;
_mag64f_err_size:
	gr7=-6;
	//goto _mag64f_exit
_mag64f_exit:
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;


//nmppsStatus nmppsMagnitude_64fc(const nmpps64fc*  pSrc, nmpps64f* pDst, int len);
_nmppsMagnitude_64fc:
	ar5 = ar7 - 2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;

	ar0=[--ar5]; //src
	ar2=[--ar5]; //dst
	gr2=[--ar5]; //len
	ar1= ar0 + 2;
	ar3=ar2;

	gr7=ar0;
	gr7;
	if =0 goto _mag64fc_null_ptr;
	gr7=ar2;
	gr7;
	if =0 goto _mag64fc_null_ptr;
	gr2;
	if <= goto _mag64fc_err_size;

	gr0=4;
	gr1=gr0;
	gr7 = gr2>>5 ;
	if =0 goto _mag64fc_end_cicl;

_mag64fc_start_cicl:
	fpu 0 rep 32 vreg0=[ar0++gr0];
	fpu 0 rep 32 vreg1=[ar1++gr1];

	fpu 0 .double vreg0=vreg0*vreg0;
	fpu 0 .double vreg1=vreg1*vreg1;

	fpu 0 .double vreg0 = vreg0+vreg1;
	fpu 0 rep 32 [ar2++]=vreg0;
	gr7 = gr7-1;
	if > goto _mag64fc_start_cicl;

_mag64fc_end_cicl:
	gr7=0x001F;
	gr1 = gr2 and gr7;

	if =0 delayed goto  _mag64fc_exit;
	gr7=0;
	nul;

	gr1=gr1-1;
	vlen=gr1;

	gr1=gr0;

	fpu 0 rep vlen vreg0=[ar0++gr0];
	fpu 0 rep vlen vreg1=[ar1++gr1];

	fpu 0 .double vreg0=vreg0*vreg0;
	fpu 0 .double vreg1=vreg1*vreg1;

	fpu 0 .double vreg0 = vreg0+vreg1;

	fpu 0 rep vlen [ar2++]=vreg0;

	push gr2; //len
	push ar3; //dst
	push ar3; //src
	call _nmppsSqrt_64f;
	ar7 = ar7 - 3;

	gr7=0;
	goto _mag64fc_exit;

_mag64fc_null_ptr:
	gr7=-8;
	goto _mag64fc_exit;
_mag64fc_err_size:
	gr7=-6;
	//goto _mag64fc_exit
_mag64fc_exit:
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
